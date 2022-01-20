#include "Laser.h"
#include"SpriteComponent.h"
#include"Assets.h"
#include"MoveComponent.h"
#include"Game.h"
#include"Astroid.h"

Laser::Laser() : Actor(), deathTimer(1.0f), collision(nullptr) {
	new SpriteComponent(this, Assets::GetTexture("Laser"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);
	collision = new CircleCollisionComponent(this);
	collision->SetRadius(11.0f);
}

void Laser::UpdateActor(float dt) {
	deathTimer -= dt;
	if (deathTimer <= 0.0f) {
		SetState(ActorState::Dead);
	}
	else {
		auto astroids = GetGame().GetAstroids();
		for (auto astroid : astroids) {
			if (IsIntersect(*collision, astroid->GetCollision())) {
				SetState(Actor::ActorState::Dead);
				astroid->SetState(ActorState::Dead);
				break;
			}
		}
	}
}
