// main.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include <cmath>

int main()
{	
	constexpr double d = std::numeric_limits<double>::quiet_NaN();
	bool isNan = std::isnan(d);

	std::cout << d << isNan << std::endl;
	return 0;
}
