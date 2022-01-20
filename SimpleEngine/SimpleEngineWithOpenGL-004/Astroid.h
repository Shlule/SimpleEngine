#pragma once
#include"Actor.h"
#include"CircleCollisionComponent.h"
class Astroid : public Actor
{
public:
	Astroid();
	~Astroid();

	CircleCollisionComponent& GetCollision() { return *collision; }

private: 
	CircleCollisionComponent* collision;
};

