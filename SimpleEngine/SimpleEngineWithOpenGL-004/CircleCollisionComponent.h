#pragma once
#include"Component.h"
#include"Vector2.h"

class CircleCollisionComponent :public Component
{
public:
	CircleCollisionComponent(Actor* owner);
	CircleCollisionComponent() = delete;
	CircleCollisionComponent(const CircleCollisionComponent&) = delete;
	CircleCollisionComponent& operator=(const CircleCollisionComponent&) = delete;

	float GetRadius() const;
	void SetRadius(float radiusP);
	const Vector2 GetCenter()const;

private:
	float radius;
};
bool IsIntersect(const CircleCollisionComponent& a, const CircleCollisionComponent& b);

