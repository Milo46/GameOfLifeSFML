#include "RandomGenerator.h"

thread_local std::mt19937 gen(std::random_device{}());

int randint(const int& min, const int& max)
{
	return std::uniform_int_distribution<int>{min, max}(gen);
}
