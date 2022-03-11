#ifndef VECTOR2_H
#define VECTOR2_H

#include <vector>

namespace Xna {

	struct Point;
	struct Quaternion;
	struct Matrix;

	// Describes a 2D-vector.
	// C#: struct Vector2.
	struct Vector2 {
		double X;
		double Y;

		Vector2();
		Vector2(double x, double y);
		Vector2(double value);

		Vector2 operator- ();
		
		friend Vector2 operator+ (Vector2, Vector2);
		friend Vector2 operator- (Vector2, Vector2);
		friend Vector2 operator* (Vector2, Vector2);
		friend Vector2 operator* (Vector2, double);
		friend Vector2 operator* (double, Vector2);
		friend Vector2 operator/ (Vector2, Vector2);
		friend Vector2 operator/ (Vector2, double);
		friend Vector2 operator== (Vector2, Vector2);
		friend Vector2 operator!= (Vector2, Vector2);

		static Vector2 Zero();
		static Vector2 One();
		static Vector2 UnitX();
		static Vector2 UnitY();

		static Vector2 Add(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Barycentric(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3, double amount1, double amount2);
		static Vector2 CatmullRom(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3, Vector2 const& value4, double amount);
		static Vector2 Ceiling(Vector2 const& value);
		static Vector2 Clamp(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3);
		static double Distance(Vector2 const& value1, Vector2 const& value2);
		static double DistanceSquared(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Divide(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Divide(Vector2 const& value, double divider);
		static double Dot(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Floor(Vector2 const& value);
		static Vector2 Hermite(Vector2 const& value1, Vector2 const& tangent1, Vector2 const& value2, Vector2 const& tangent2, double amount);
		static Vector2 Lerp(Vector2 const& value1, Vector2 const& value2, double amount);
		static Vector2 LerpPrecise(Vector2 const& value1, Vector2 const& value2, double amount);
		static Vector2 Max(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Min(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Multiply(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Multiply(Vector2 const& value, double scaleFactor);
		static Vector2 Negate(Vector2 const& value);
		static Vector2 Normalize(Vector2 const& value);
		static Vector2 Reflect(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Round(Vector2 const& value);
		static Vector2 SmoothStep(Vector2 const& value1, Vector2 const& value2, double amount);
		static Vector2 Subtract(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Transform(Vector2 const& position, Matrix const& matrix);
		static Vector2 Transform(Vector2 const& value, Quaternion const& rotation);
		static Vector2 Transform(std::vector<Vector2> const& sourceArray, int sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 Transform(std::vector<Vector2> const& sourceArray, int sourceIndex, Quaternion const& rotation, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 Transform(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray);
		static Vector2 Transform(std::vector<Vector2> const& sourceArray, Quaternion const& rotation, std::vector<Vector2> destinationArray);
		static Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix);
		static Vector2 TransformNormal(std::vector<Vector2> const& sourceArray, int sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 TransformNormal(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray);
		
		void Ceiling();
		void Floor();		
		double Length() const;
		double LengthSquared() const;
		void Normalize();
		void Round();
		Point ToPoint() const;
		void Deconstruct(double&, double&) const;
		bool Equals(Vector2 const& other) const;
	};
}

#endif