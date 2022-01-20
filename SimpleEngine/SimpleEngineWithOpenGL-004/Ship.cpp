#include "Ship.h"
#include"SpriteComponent.h"
#include"Assets.h"
#include"InputComponent.h"
#include"Maths.h"
#include"Laser.h"

Ship::Ship() : Actor() , laserCooldown(0.0f) {
	SpriteComponent* sc = new SpriteComponent(this, Assets::GetTexture("Ship01"));
	InputComponent* ic = new InputComponent(this);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Maths::twoPi);

}
void Ship::ActorInput(const Uint8* keyState) {
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f) {
		Laser* laser = new Laser();
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		laserCooldown = 0.2f;
	}
}
void Ship::UpdateActor(float dt) {
	laserCooldown -= dt;
}
