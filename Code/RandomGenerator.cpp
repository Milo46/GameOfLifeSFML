#include "RandomGenerator.h"

thread_local std::mt19937 gen(std::random_device{}());

int randint(int min, int max)
{
	return std::uniform_int_distribution<int>{min, max}(gen);
}
