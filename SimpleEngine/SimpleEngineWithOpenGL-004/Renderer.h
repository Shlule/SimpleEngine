#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"
#include"Vector2.h"
#include"Actor.h"

class Renderer
{
public:
	enum class Flip
	{
		None =SDL_FLIP_NONE,
		Horizontal= SDL_FLIP_HORIZONTAL,
		Vertical= SDL_FLIP_VERTICAL
	};

	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);

	void BeginDraw();
	void Draw();
	void EndDraw();

	void DisplaySprites();

	void DrawRect(const Rectangle& rect)const;
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void DrawSprites();
	void DrawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip)const;

	SDL_Renderer* toSDLRenderer()const { return SDLRenderer; }
	vector<SpriteComponent*> GetSprites()const { return sprites; }

	void close();


private:
	SDL_Renderer* SDLRenderer = nullptr;
	std::vector<SpriteComponent*>sprites;
};

