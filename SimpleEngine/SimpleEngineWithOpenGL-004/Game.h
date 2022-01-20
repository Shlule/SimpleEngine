#pragma once
#include<vector>
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
#include"Actor.h"
#include "Assets.h"
#include"SpriteComponent.h"
#include"Astroid.h"
using std::vector;

class Game
{
public:
	
	static Game& instance()
	{
		static Game inst;
		return inst;
	}
	// Game spêcifique
	vector<Astroid*>& GetAstroids();
	void AddAstroid(Astroid* astroid);
	void RemoveAstroid(Astroid* astroid);

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game(): 
		isRunning(true),
		isUpdatingActors(false)
	{}

public:
	Renderer& GetRenderer(){ return renderer; }
	bool Initialize();
	void Load();
	void Unload();
	void Loop();
	void Close();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

private:
	void ProcessInput();
	void Update(float dt);
	void Render();

	bool isRunning;
	Window window;
	Renderer renderer;

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*>pendingActors;
	vector<Astroid*>astroids;
};

