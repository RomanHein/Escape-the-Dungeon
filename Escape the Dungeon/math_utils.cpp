#include "math_utils.h"

#include <cstdlib>

// === Namespace Functions ===

namespace utils
{
	int math::randomInt(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}
}