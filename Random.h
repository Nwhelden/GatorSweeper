#pragma once
#include <random>

//members are static, so they can be accessed without needing to instantiate the class
class Random
{

	static std::mt19937 random;

public:

	//one function for generating random integers, the other for generating random floats
	static int Int(int min, int max);
	static float Float(float min, float max);

};