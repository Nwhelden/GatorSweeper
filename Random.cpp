#include "Random.h"
#include <ctime>

std::mt19937 Random::random(time(0));

//once something has been defined as static in the header file, don't need to redefine it as static
int Random::Int(int min, int max) {

	//uniform_int_distribution is a range of whole numbers
	//to actually generate the random number, we pass the random number generator mt19937 varaible into dist()
	//random needs to be static member in order to use it in a static function
	//call function to generate random integer number
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);

}

float Random::Float(float min, float max) {

	std::uniform_real_distribution<float> dist(min, max);
	return dist(random);

}