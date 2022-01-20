#include "MoveComponent.h"
#include"Maths.h"
#include"Actor.h"
#include"Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP) : Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f){}

void MoveComponent::SetForwardSpeed(float forwardSpeedP) {
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::SetAngularSpeed(float angularSpeedP) {
	angularSpeed = angularSpeedP;
}

void MoveComponent::Update(float dt) {
	if (!Maths::nearZero(angularSpeed)) {
		float newRotation = owner.GetRotation() + angularSpeed * dt;
		owner.SetRotation(newRotation);
	}
	if (!Maths::nearZero(forwardSpeed)) {
		Vector2 newPosition = owner.GetPosition() + owner.GetForward() * forwardSpeed * dt;

		//screen warpping( for asteroids)

		if (newPosition.x < 0) {
			newPosition.x = WINDOW_WIDTH;
		}
		else if (newPosition.x > WINDOW_WIDTH) {
			newPosition.x = 0;
		}
		else if (newPosition.y < 0) {
			newPosition.y = WINDOW_HEIGHT;
		}
		else if (newPosition.y > WINDOW_HEIGHT) {
			newPosition.y = 0;
		}
		owner.SetPosition(newPosition);
	}

}
