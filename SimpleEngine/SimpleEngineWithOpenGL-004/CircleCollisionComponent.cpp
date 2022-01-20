#include "CircleCollisionComponent.h"
#include"Actor.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) : Component{ owner }, radius{ 1.0f }{}

float CircleCollisionComponent::GetRadius()const {
	return owner.GetScale() * radius;
}
void CircleCollisionComponent::SetRadius(float radiusP) {
	radius = radiusP;
}
const Vector2 CircleCollisionComponent::GetCenter()const {
	return owner.GetPosition();
}
bool IsIntersect(const CircleCollisionComponent& a, const CircleCollisionComponent& b) {
	Vector2 aCenter = a.GetCenter();
	Vector2 bCenter = b.GetCenter();
	Vector2 ab = bCenter - aCenter;
	float distSq = ab.LenghtSq();
	float sumOfRadius = a.GetRadius() + b.GetRadius();
	return distSq <= sumOfRadius * sumOfRadius;
}
