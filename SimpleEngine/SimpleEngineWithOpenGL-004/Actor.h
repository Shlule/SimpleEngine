#pragma once
#include<vector>
#include"Vector2.h"
#include<SDL_stdinc.h>
using std::vector;

class Game;
class Component;

class Actor
{
public:
	enum class ActorState {
		Active,Paused,Dead,
	};
	// manage constructor and destructor
	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	void ProcessInput(const Uint8* keyState);
	virtual void ActorInput(const Uint8* keyState);

	// create Getter inline
	Game& GetGame()const { return game; }
	const ActorState GetState() const { return state; }
	const Vector2 GetPosition() const { return position; }
	const float GetScale() const { return scale; }
	const float GetRotation() const { return rotation; }
	Vector2 GetForward()const;

	// create Setter
	void SetPosition(Vector2 positionP);
	void SetScale(float scaleP);
	void SetRotation(float rotationP);
	void SetState(ActorState stateP);

	//utilitie
	void Update(float dt);
	void UpdateComponent(float dt);
	virtual void UpdateActor(float dt);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);


private:
	Game& game;
	ActorState state;
	Vector2 position;
	float scale;
	float rotation; // rotation in radians

	vector<Component*> components;


};

