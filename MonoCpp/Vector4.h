#ifndef VECTOR4_H
#define VECTOR4_H

#include <vector>
#include <iostream>

namespace Xna {

	struct Vector2;
	struct Vector3;
	struct Matrix;
	struct Quaternion;

	// Describes a 4D-vector.
	// C#: struct Vector4 in Vector4.cs
	struct Vector4 {

		// The x coordinate of this <see cref="Vector4"/>.
		double X;
		// The y coordinate of this <see cref="Vector4"/>.
		double Y;
		// The z coordinate of this <see cref="Vector4"/>.
		double Z;
		// The w coordinate of this <see cref="Vector4"/>.
		double W;

		// Constructs a 3d vector with X, Y, Z and W = 0.
		Vector4();
		// Constructs a 3d vector with X, Y, Z and W from four values.
		Vector4(double x, double y, double z, double w);
		// Constructs a 3d vector with X and Z from <see cref="Vector2"/> and Z and W from the scalars.
		Vector4(Vector2 value, double z, double w);
		// Constructs a 3d vector with X, Y, Z from <see cref="Vector3"/> and W from a scalar.
		Vector4(Vector3 value, double w);
		// Constructs a 4d vector with X, Y, Z and W set to the same value.
		Vector4(double value);

		Vector4 operator- () const;
		friend std::ostream& operator<< (std::ostream& os, Vector4 const& obj);
		friend Vector4 operator- (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator+ (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator* (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator* (Vector4 const& value1, double scaleFactor);
		friend Vector4 operator/ (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator/ (Vector4 const& value1, long divider);
		friend bool operator== (Vector4 const& value1, Vector4 const& value2);
		friend bool operator!= (Vector4 const& value1, Vector4 const& value2);

		static Vector4 Zero();
		static Vector4 One();
		static Vector4 UnitX();
		static Vector4 UnitY();
		static Vector4 UnitZ();
		static Vector4 UnitW();

		static Vector4 Add(Vector4 const& value1, Vector4 const& value2);
		Vector4 Barycentric(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, double amount1, double amount2);
		static Vector4 CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, Vector4 const& value4, double amount);
		static Vector4 Ceiling(Vector4 const& value);
		static Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max);
		static double Distance(Vector4 const& value1, Vector4 const& value2);
		static double DistanceSquared(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Divide(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Divide(Vector4 const& value1, double divider);
		static double Dot(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Floor(Vector4 const& value);
		static Vector4 Hermite(Vector4 const& value1, Vector4 const& tangent1, Vector4 const& value2, Vector4 const& tangent2, double amount);
		static Vector4 Lerp(Vector4 const& value1, Vector4 const& value2, double amount);
		static Vector4 LerpPrecise(Vector4 const& value1, Vector4 const& value2, double amount);
		static Vector4 Max(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Min(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Multiply(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Multiply(Vector4 const& value1, double scaleFactor);
		static Vector4 Negate(Vector4 const& value);
		static Vector4 Normalize(Vector4 const& value);
		static Vector4 Round(Vector4 const& value);
		static Vector4 SmoothStep(Vector4 const& value1, Vector4 value2, double amount);
		static Vector4 Subtract(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Transform(Vector2 const& value, Matrix const& matrix);
		static Vector4 Transform(Vector3 const& value, Matrix const& matrix);
		static Vector4 Transform(Vector4 const& value, Matrix const& matrix);
		static void Transform(std::vector<Vector4> const& sourceArray, int sourceIndex,
			Matrix& matrix, std::vector<Vector4>& destinationArray, int destinationIndex, int length);
		static void Transform(std::vector<Vector4> const& sourceArray, Matrix& matrix, std::vector<Vector4>& destinationArray);		

		void Ceiling();
		void Floor();
		double Length() const;
		double LengthSquared() const;
		void Normalize();
		void Round();
		void Deconstruct(double& x, double& y, double& z, double& w) const;
		bool Equals(Vector4 const& other) const;

		//----- C# code not implemented
		// static Vector4 Transform(Vector2 const& value, Quaternion const& rotation);
		// static Vector4 Transform(Vector3 const& value, Quaternion const& rotation);
		// static Vector4 Transform(Vector4 const& value, Quaternion const& rotation);
		
		// This methods call Transform(Vector4, Quaternion) in its implementation
		// static void Transform(std::vector<Vector4> const& sourceArray, int sourceIndex, Quaternion& rotation, std::vector<Vector4>& destinationArray, int destinationIndex, int length);
		// static void Transform(std::vector<Vector4> const& sourceArray, Quaternion& matrix, std::vector<Vector4>& destinationArray);	
	};
}

#endif