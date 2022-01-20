#include "Astroid.h"
#include"Random.h"
#include"Window.h"
#include"Maths.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Assets.h"
#include"Game.h"

Astroid::Astroid() : Actor(), collision{ nullptr } {

	Vector2 randPos = Random::GetVector2(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::GetTexture("Astroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	collision = new CircleCollisionComponent(this);
	collision->SetRadius(40.0f);

	GetGame().AddAstroid(this);
}
Astroid::~Astroid() {
	GetGame().RemoveAstroid(this);
}
