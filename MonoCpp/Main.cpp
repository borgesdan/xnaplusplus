// main.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include <cmath>
#include "Vector3.h"
#include <numeric>
#include "Color.h"

int main()
{	
	Xna::Color color(0);

	long i = 0xfffff8f0;
	long x = i;

	Xna::Vector3 vec;
	auto vec3 = -vec;

	constexpr double d = std::numeric_limits<double>::quiet_NaN();
	bool isNan = std::isnan(d);

	std::cout << d << isNan << std::endl;
	return 0;
}
