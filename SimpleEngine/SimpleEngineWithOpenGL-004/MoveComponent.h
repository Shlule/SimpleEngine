#pragma once
#include"Component.h"
class MoveComponent :public Component
{
public:
	MoveComponent(Actor* ownerP, int upadteOrder = 10);//by default, update before other components;
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;

	float GetForwardSpeed() const { return forwardSpeed; }
	float GetAngularSpeed() const { return angularSpeed; }

	void SetForwardSpeed(float forwardSpeedP);
	void SetAngularSpeed(float angularSpeedP);

	void Update(float dt)override;

private:
	float forwardSpeed;
	float angularSpeed;

};

