#include "InputComponent.h"
#include<SDL_scancode.h>

InputComponent::InputComponent(Actor* ownerP): 
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f),
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_W),
	backKey(SDL_SCANCODE_S),
	clockWiseKey(SDL_SCANCODE_D),
	counterClockWiseKey(SDL_SCANCODE_A)
{}

void InputComponent::ProcessInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey]) {
		forwardSpeed += maxForwardSpeed;
	}
	if (keyState[backKey]) {
		forwardSpeed -= maxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyState[clockWiseKey]) {
		angularSpeed -= maxAngularSpeed;
	}
	if (keyState[counterClockWiseKey]) {
		angularSpeed += maxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}

void InputComponent::SetMaxForwardSpeed(float maxForwardSpeedP) {
	maxForwardSpeed = maxForwardSpeedP;
}
void InputComponent::SetMaxAngularSpeed(float maxAngularSpeedP) {
	maxAngularSpeed = maxAngularSpeedP;
}
void InputComponent::SetForwardKey(int key){
	forwardKey = key;
}
void InputComponent::SetBackKey(int key){
	backKey = key;
}
void InputComponent::SetClockWiseKey(int key){
	clockWiseKey = key;
}
void InputComponent::SetCounterClockWiseKey(int key){
	counterClockWiseKey = key;
}