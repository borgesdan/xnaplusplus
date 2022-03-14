#ifndef VECTOR3_H
#define VECTOR3_H

#include <vector>
#include "CSharp.h"

namespace Xna {

	struct Matrix;
	struct Vector2;
	struct Quaternion;

	// Describes a 3D-vector.
	// C#: struct Vector3.
	struct Vector3 {
		double X;
		double Y;
		double Z;

		Vector3();
		Vector3(double x, double y, double z);
		Vector3(double value);
		Vector3(Vector2 value, double z);

		Vector3 operator- () const;

		friend Vector3 operator- (Vector3 const&, Vector3 const&);
		friend Vector3 operator+ (Vector3 const&, Vector3 const&);
		friend Vector3 operator* (Vector3 const&, Vector3 const&);
		friend Vector3 operator* (Vector3 const&, double const&);
		friend Vector3 operator* (double const&, Vector3 const&);
		friend Vector3 operator/ (Vector3 const&, Vector3 const&);
		friend Vector3 operator/ (Vector3 const&, double const& divider);
		friend bool operator== (Vector3 const&, Vector3 const&);
		friend bool operator!= (Vector3 const&, Vector3 const&);

		// Returns a <see cref="Vector4"/> with components 0, 0, 0, 0.
		static Vector3 Zero();
		static Vector3 One();
		static Vector3 UnitX();
		static Vector3 UnitY();
		static Vector3 UnitZ();
		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Right();
		static Vector3 Left();
		static Vector3 Forward();
		static Vector3 Backward();

		static Vector3 Add(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Divide(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Divide(Vector3 const& value1, double divider);
		static Vector3 Subtract(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Multiply(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Multiply(Vector3 const& value1, double scaleFactor);
		static Vector3 Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, double amount1, double amount2);
		static Vector3 CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, Vector3 const& value4, double amount);
		static Vector3 Ceiling(Vector3 const& value);
		static Vector3 Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max);
		static Vector3 Cross(Vector3 const& value1, Vector3 const& value2);
		static double Dot(Vector3 const& value1, Vector3 const& value2);
		static double Distance(Vector3 const& value1, Vector3 const& value2);
		static double DistanceSquared(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Floor(Vector3 const& value);
		static Vector3 Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2, Vector3 const& tangent2, double amount);
		static Vector3 Normalize(Vector3 const& value);
		static Vector3 Lerp(Vector3 const& value1, Vector3 const& value2, double amount);
		static Vector3 LerpPrecise(Vector3 const& value1, Vector3 const& value2, double amount);
		static Vector3 Max(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Min(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Negate(Vector3 const& value);
		static Vector3 Reflect(Vector3 const& vector, Vector3 const& normal);
		static Vector3 Round(Vector3 const& value);
		static Vector3 SmoothStep(Vector3 const& value1, Vector3 const& value2, double amount);
		static Vector3 Transform(Vector3 const& position, Matrix const& matrix);
		static Vector3 Transform(Vector3 const& value, Quaternion const& rotation);
		static void Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix& matrix, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Quaternion& rotation, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector3> const& sourceArray, Matrix& matrix, std::vector<Vector3>& destinationArray);
		static void Transform(std::vector<Vector3> const& sourceArray, Quaternion& rotation, std::vector<Vector3>& destinationArray);
		static Vector3 TransformNormal(Vector3 const& normal, Matrix const& matrix);
		static void TransformNormal(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix& matrix, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void TransformNormal(std::vector<Vector3> const& sourceArray, Matrix& matrix, std::vector<Vector3>& destinationArray);

		void Round();
		void Ceiling();
		void Normalize();
		double Length() const;
		double LengthSquared() const;
		void Floor();
		void Deconstruct(double& x, double& y, double& z) const;
		bool Equals(Vector3 other) const;
	};
}
#endif