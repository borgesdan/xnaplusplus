#include <cmath>
#include "MathHelper.h"

namespace Xna {

	double MathHelper::Barycentric(double value1, double value2, double value3, double amount1, double amount2) {
		return value1 + (value2 - value1) 
			* amount1 + (value3 - value1) 
			* amount2;
	}

	double MathHelper::CatmullRom(double value1, double value2, double value3, double value4, double amount) {
		double amountSquared = amount * amount;
		double amountCubed = amountSquared * amount;

		return (0.5 * (2.0 * value2 +
			(value3 - value1) * amount +
			(2.0 * value1 - 5.0 * value2 + 4.0 * value3 - value4) * amountSquared +
			(3.0 * value2 - value1 - 3.0 * value3 + value4) * amountCubed));
	}

	double MathHelper::Clamp(double value, double min, double max) {
		value = (value > max) ? max : value;
		value = (value < min) ? min : value;
		return value;
	}

	long MathHelper::Clamp(long value, long min, long max) {
		value = (value > max) ? max : value;
		value = (value < min) ? min : value;
		return value;
	}

	double MathHelper::Distance(double value1, double value2) {
		return abs(value1 - value2);
	}

	double MathHelper::Hermite(double value1, double tangent1, double value2, double tangent2, double amount) {
		double v1 = value1;
		double v2 = value2;
		double t1 = tangent1;
		double t2 = tangent2;
		double s = amount;
		double result;

		double sCubed = s * s * s;
		double sSquared = s * s;

		if (amount == 0)
			result = value1;
		else if (amount == 1)
			result = value2;
		else
			result = (2 * v1 - 2 * v2 + t2 + t1) * sCubed +
			(3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared +
			t1 * s +
			v1;
		
		return result;
	}

	double MathHelper::Lerp(double value1, double value2, double amount) {
		return value1 + (value2 - value1) * amount;
	}

	double MathHelper::LerpPrecise(double value1, double value2, double amount) {
		return ((1 - amount) * value1) + (value2 * amount);
	}

	double MathHelper::Max(double value1, double value2) {
		return value1 > value2 ? value1 : value2;
	}

	long MathHelper::Max(long value1, long value2) {
		return value1 > value2 ? value1 : value2;
	}

	double MathHelper::Min(double value1, double value2) {
		return value1 < value2 ? value1 : value2;
	}

	long MathHelper::Min(long value1, long value2) {
		return value1 < value2 ? value1 : value2;
	}

	double MathHelper::SmoothStep(double value1, double value2, double amount) {
		double result = Clamp(amount, 0, 1.0);
		result = Hermite(value1, 0, value2, 0, result);

		return result;
	}

	double MathHelper::ToDegrees(double radians) {		
		return radians * RADIANS_TO_DEGREE;
	}

	double MathHelper::ToRadians(double degrees) {
		return degrees * DEGREE_TO_RADIANS;
	}
	
	double MathHelper::WrapAngle(double angle) {
		if ((angle > -Pi) && (angle <= Pi))
			return angle;

		// % is not defined for doubles
		//angle %= TwoPi;
		angle = fmod(angle, TwoPi);

		if (angle <= -Pi)
			return angle + TwoPi;

		if (angle > Pi)
			return angle - TwoPi;

		return angle;
	}

	bool MathHelper::IsPowerOfTwo(long value) {
		return (value > 0) && ((value & (value - 1)) == 0);
	}

	bool IsPositiveInfinity(double value) {
		return isinf(value) && value > 0;
	}
}