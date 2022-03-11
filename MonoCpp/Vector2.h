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

		static Vector2 Add(Vector2, Vector2 const&);
		static Vector2 Barycentric(Vector2, Vector2, Vector2, double, double);
		static Vector2 CatmullRom(Vector2, Vector2, Vector2, Vector2, double);
		static Vector2 Ceiling(Vector2);
		static Vector2 Clamp(Vector2, Vector2, Vector2);
		static Vector2 Distance(Vector2, Vector2);
		static Vector2 DistanceSquared(Vector2, Vector2);
		static Vector2 Divide(Vector2, Vector2);
		static Vector2 Divide(Vector2, double);
		static double Dot(Vector2, Vector2);
		static Vector2 Floor(Vector2);
		static Vector2 Hermite(Vector2, Vector2, Vector2, Vector2, double);
		static Vector2 Lerp(Vector2, Vector2, double);
		static Vector2 LerpPrecise(Vector2, Vector2, double);
		static Vector2 Max(Vector2, Vector2);
		static Vector2 Min(Vector2, Vector2);
		static Vector2 Multiply(Vector2, Vector2);
		static Vector2 Multiply(Vector2, double);
		static Vector2 Negate(Vector2);
		static Vector2 Normalize(Vector2);
		static Vector2 Reflect(Vector2, Vector2);
		static Vector2 Round(Vector2);
		static Vector2 SmoothStep(Vector2, Vector2, double amount);
		static Vector2 Subtract(Vector2, Vector2);
		static Vector2 Transform(Vector2, Matrix);
		static Vector2 Transform(Vector2, Quaternion);
		static Vector2 Transform(std::vector<Vector2>, int sourceIndex, Matrix&, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 Transform(std::vector<Vector2>, int sourceIndex, Quaternion&, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 Transform(std::vector<Vector2>, Matrix&, std::vector<Vector2> destinationArray);
		static Vector2 Transform(std::vector<Vector2>, Quaternion&, std::vector<Vector2> destinationArray);
		static Vector2 TransformNormal(Vector2, Matrix);
		static Vector2 TransformNormal(std::vector<Vector2>, int sourceIndex, Matrix&, std::vector<Vector2> destinationArray, long destinationIndex, long length);
		static Vector2 TransformNormal(std::vector<Vector2>, Matrix&, std::vector<Vector2> destinationArray);
		
		void Ceiling();
		void Floor();		
		double Length();
		double LengthSquared();
		void Normalize();
		void Round();
		Point ToPoint();
		void Deconstruct(double&, double&);

		bool Equals(Vector2 const& other);
	};
}

#endif