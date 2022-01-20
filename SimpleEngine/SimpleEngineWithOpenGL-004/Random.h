#pragma once
#include<random>
#include"Vector2.h"
class Random
{
public:
	static void Init();
	//seed the generator with the specified int
	// Note: You Should generally not need to manualy use this

	static void Seed(unsigned int seed);

	// get a float between 0.0f and 1.0f
	static float GetFloat();

	// get float from a specified Range
	static float GetFloatRange(float min, float max);

	//get an int from th specified range
	static int GetIntRange(int min, int max);

	// get a random vetor given the min/max bounds
	static Vector2 GetVector2(const Vector2& min, const Vector2& max);

private:
	static std::mt19937 sGenerator;
};

