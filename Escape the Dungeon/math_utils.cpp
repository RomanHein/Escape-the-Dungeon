#include "math_utils.h"

#include <cstdlib>

//
// === Namespace Functions ===
//

namespace core
{
	namespace utils
	{
		int math::randomInt(int min, int max)
		{
			return min + std::rand() % (max - min + 1);
		}

		double math::randomUnit()
		{
			return std::rand() % 101 / 100.0;
		}
	}
}