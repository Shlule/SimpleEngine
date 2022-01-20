#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "Assets.h"
#include "BackgroundSpriteComponent.h"
#include "Astroid.h"
#include "Ship.h"

bool Game::Initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::Load()
{
	// Load textures
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Ship01.png", "Ship01");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Ship02.png", "Ship02");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Ship03.png", "Ship03");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Ship04.png", "Ship04");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Farback01.png", "Farback01");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Farback02.png", "Farback02");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Stars.png", "Stars");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Astroid.png", "Astroid");
	Assets::LoadTexture(renderer, "..\\Resources\\ShooterSprite\\Laser.png", "Laser");

	// Single sprite
	/*
	Actor* actor = new Actor();
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::getTexture("Ship01"));
	actor->setPosition(Vector2{ 100, 100 });
	*/

	// Animated sprite
	/*
	vector<Texture*> animTextures {
		&Assets::getTexture("Ship01"),
		&Assets::getTexture("Ship02"),
		&Assets::getTexture("Ship03"),
		&Assets::getTexture("Ship04"),
	};
	Actor* ship = new Actor();
	AnimSpriteComponent* animatedSprite = new AnimSpriteComponent(ship, animTextures);
	ship->setPosition(Vector2{ 100, 300 });
	*/

	// Controlled ship
	Ship* ship = new Ship();
	ship->SetPosition(Vector2{ 100, 300 });

	// Background
	// Create the "far back" background
	vector<Texture*> bgTexsFar{
		&Assets::GetTexture("Farback01"),
		&Assets::GetTexture("Farback02")
	};
	Actor* bgFar = new Actor();
	BackgroundSpriteComponent* bgSpritesFar = new BackgroundSpriteComponent(bgFar, bgTexsFar);
	bgSpritesFar->SetScrollSpeed(-100.0f);

	// Create the closer background
	Actor* bgClose = new Actor();
	std::vector<Texture*> bgTexsClose{
		&Assets::GetTexture("Stars"),
		&Assets::GetTexture("Stars")
	};
	BackgroundSpriteComponent* bgSpritesClose = new BackgroundSpriteComponent(bgClose, bgTexsClose, 50);
	bgSpritesClose->SetScrollSpeed(-200.0f);

	const int astroidNumber = 20;
	for (int i = 0; i < astroidNumber; ++i)
	{
		new Astroid();
	}
}

void Game::ProcessInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->ProcessInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::Update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->Update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->GetState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::Render()
{
	renderer.BeginDraw();
	renderer.Draw();
	renderer.EndDraw();
}

vector<Astroid*>& Game::GetAstroids()
{
	return astroids;
}

void Game::AddAstroid(Astroid* astroid)
{
	astroids.emplace_back(astroid);
}

void Game::RemoveAstroid(Astroid* astroid)
{
	auto iter = std::find(begin(astroids), end(astroids), astroid);
	if (iter != astroids.end())
	{
		astroids.erase(iter);
	}
}

void Game::Loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		ProcessInput();
		Update(dt);
		Render();
		timer.delayTime();
	}
}

void Game::Unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::Close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}