#ifndef _MATHHELPER_H_
#define _MATHHELPER_H_

namespace Xna {

	//Contains commonly used precalculated values and mathematical operations.
	struct MathHelper {

		// Represents the log base ten of e(0.434294481903251827651).
		static constexpr double Log10E = 0.434294481903251827651;
		// Represents the log base two of e(1.44269504088896340736).
		static constexpr double Log2E = 1.44269504088896340736;
		// Represents the value of pi(3.14159265358979323846) _M_PI.
		static constexpr double Pi = 3.14159265358979323846;
		// Represents the value of pi divided by two(1.57079632679489661923) _M_PI_2.
		static constexpr double PiOver2 = 1.57079632679489661923;
		// Represents the value of pi divided by four(0.785398163397448309616) _M_PI_4.
		static constexpr double PiOver4 = 0.785398163397448309616;
		// Represents the value of pi times two.
		static constexpr double TwoPi = Pi * 2.0;
		// Represents the value of pi times two.
		static constexpr double Tau = TwoPi;				

		//Returns the Cartesian coordinate for one axis of a point that is defined by a given triangle and two normalized barycentric (areal) coordinates.
		static double Barycentric(double, double, double, double, double);
		// Performs a Catmull-Rom interpolation using the specified positions.
		static double CatmullRom(double, double, double, double, double);
		// Restricts a value to be within a specified range.
		static double Clamp(double, double, double);
		// Restricts a value to be within a specified range.
		static long Clamp(long, long, long);
		// Calculates the absolute value of the difference of two values.
		static double Distance(double, double);
		// Performs a Hermite spline interpolation.
		static double Hermite(double, double, double, double, double);
		// Linearly interpolates between two values.
		static double Lerp(double, double, double);
		// Linearly interpolates between two values.
		// This method is a less efficient, more precise version of Lerp.
		static double LerpPrecise(double, double, double);
		// Returns the greater of two values.
		static double Max(double, double);
		// Returns the greater of two values.
		static long Max(long, long);
		// Returns the lesser of two values.
		static double Min(double, double);
		// Returns the lesser of two values.
		static long Min(long, long);
		// Interpolates between two values using a cubic equation.
		static double SmoothStep(double, double, double);
		// Converts radians to degrees.
		static double ToDegrees(double);
		// Converts degrees to radians.
		static double ToRadians(double);
		// Reduces a given angle to a value between pi and -pi.
		static double WrapAngle(double); 
		// Determines if value is powered by two.
		static bool IsPowerOfTwo(long);

		//----- C#: MathF.cs methods

		static double Sqrt(double value);
		static double Pow(double x, double y);
		static double Sin(double value);
		static double Cos(double value);
		static double Tan(double value);
		static double Asin(double value);
		static double Acos(double value);
		static double Atan(double value);
		static double Round(double value);
		static double Ceiling(double value);
		static double Floor(double value);
		
		//----- Others

		//Represents the constant to converts radians to degrees.
		static constexpr double RADIANS_TO_DEGREE = 57.295779513082320876798154814105;
		//Represents the constant to converts degress to radians.
		static constexpr double DEGREE_TO_RADIANS = 0.017453292519943295769236907684886;

		//Returns true if the value is infinity and greater then 0.
		bool IsPositiveInfinity(double);
	};	
}

#endif