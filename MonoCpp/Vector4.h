#ifndef VECTOR4_H
#define VECTOR4_H

#include <vector>
#include "CSharp.h"

namespace Xna {

	struct Vector2;
	struct Vector3;
	struct Matrix;
	struct Quaternion;

	// Describes a 4D-vector.
	// C#: struct Vector4.
	struct Vector4 {

		// The x coordinate of this Vector4.
		double X;
		// The y coordinate of this Vector4.
		double Y;
		// The z coordinate of this Vector4.
		double Z;
		// The w coordinate of this Vector4.
		double W;

		// Constructs a 3d vector with X, Y, Z and W = 0.
		Vector4();
		// Constructs a 3d vector with X, Y, Z and W from four values.
		Vector4(double x, double y, double z, double w);
		// Constructs a 3d vector with X and Z from Vector2 and Z and W from the scalars.
		Vector4(Vector2 value, double z, double w);
		// Constructs a 3d vector with X, Y, Z from Vector3 and W from a scalar.
		Vector4(Vector3 value, double w);
		// Constructs a 4d vector with X, Y, Z and W set to the same value.
		Vector4(double value);

		Vector4 operator- () const;
		friend Vector4 operator- (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator+ (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator* (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator* (Vector4 const& value1, double scaleFactor);
		friend Vector4 operator/ (Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator/ (Vector4 const& value1, i32 divider);
		friend bool operator== (Vector4 const& value1, Vector4 const& value2);
		friend bool operator!= (Vector4 const& value1, Vector4 const& value2);

		// Returns a Vector4 with components 0, 0, 0, 0.
		static Vector4 Zero();
		// Returns a Vector4 with components 1, 0, 0, 0.
		static Vector4 One();
		// Returns a Vector4 with components 1, 0, 0, 0.
		static Vector4 UnitX();
		// Returns a Vector4 with components 0, 1, 0, 0.
		static Vector4 UnitY();
		// Returns a Vector4 with components 0, 0, 1, 0.
		static Vector4 UnitZ();
		// Returns a Vector4 with components 0, 0, 0, 1.
		static Vector4 UnitW();

		// Performs vector addition on <paramref name="value1 and <paramref name="value2.
		static Vector4 Add(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains the cartesian coordinates of a vector specified in barycentric coordinates and relative to 4d-triangle.
		Vector4 Barycentric(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, double amount1, double amount2);
		// Creates a new Vector4 that contains CatmullRom interpolation of the specified vectors.
		static Vector4 CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, Vector4 const& value4, double amount);
		// Round the members of this Vector4 towards positive infinity.
		static Vector4 Ceiling(Vector4 const& value);
		// Clamps the specified value within a range.
		static Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max);
		// Returns the distance between two vectors.
		static double Distance(Vector4 const& value1, Vector4 const& value2);
		// Returns the squared distance between two vectors.
		static double DistanceSquared(Vector4 const& value1, Vector4 const& value2);
		// Divides the components of a Vector4 by the components of another Vector4.
		static Vector4 Divide(Vector4 const& value1, Vector4 const& value2);
		// Divides the components of a Vector4 by a scalar.
		static Vector4 Divide(Vector4 const& value1, double divider);
		// Returns a dot product of two vectors.
		static double Dot(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains members from another vector rounded towards negative infinity.
		static Vector4 Floor(Vector4 const& value);
		// Creates a new Vector4 that contains hermite spline interpolation.
		static Vector4 Hermite(Vector4 const& value1, Vector4 const& tangent1, Vector4 const& value2, Vector4 const& tangent2, double amount);
		// Creates a new Vector4 that contains linear interpolation of the specified vectors.
		static Vector4 Lerp(Vector4 const& value1, Vector4 const& value2, double amount);
		// Creates a new Vector4 that contains linear interpolation of the specified vectors.		
		static Vector4 LerpPrecise(Vector4 const& value1, Vector4 const& value2, double amount);
		// Creates a new Vector4 that contains a maximal values from the two vectors.
		static Vector4 Max(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains a minimal values from the two vectors.
		static Vector4 Min(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains a multiplication of two vectors.
		static Vector4 Multiply(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains a multiplication of Vector4 and a scalar.
		static Vector4 Multiply(Vector4 const& value1, double scaleFactor);
		// Creates a new Vector4 that contains the specified vector inversion.
		static Vector4 Negate(Vector4 const& value);
		// Creates a new Vector4 that contains a normalized values from another vector.
		static Vector4 Normalize(Vector4 const& value);
		// Creates a new Vector4 that contains members from another vector rounded to the nearest integer value.
		static Vector4 Round(Vector4 const& value);
		// Creates a new Vector4 that contains cubic interpolation of the specified vectors.
		static Vector4 SmoothStep(Vector4 const& value1, Vector4 value2, double amount);
		// Creates a new Vector4 that contains subtraction of on Vector4 from a another.
		static Vector4 Subtract(Vector4 const& value1, Vector4 const& value2);
		// Creates a new Vector4 that contains a transformation of 2d-vector by the specified Matrix.
		static Vector4 Transform(Vector2 const& value, Matrix const& matrix);
		// Creates a new Vector4 that contains a transformation of 3d-vector by the specified Matrix.
		static Vector4 Transform(Vector3 const& value, Matrix const& matrix);
		// Creates a new Vector4 that contains a transformation of 4d-vector by the specified Matrix.
		static Vector4 Transform(Vector4 const& value, Matrix const& matrix);
		// Apply transformation on vectors within array of Vector4 by the specified Matrix and places the results in an another array.
		static void Transform(std::vector<Vector4> const& sourceArray, i32 sourceIndex,	Matrix& matrix, std::vector<Vector4>& destinationArray, i32 destinationIndex, i32 length);
		// Apply transformation on all vectors within array of Vector4 by the specified Matrix and places the results in an another array.
		static void Transform(std::vector<Vector4> const& sourceArray, Matrix& matrix, std::vector<Vector4>& destinationArray);		

		// Round the members of this Vector4 towards positive infinity.
		void Ceiling();
		// Round the members of this Vector4 towards negative infinity.
		void Floor();
		// Returns the length of this Vector4.
		double Length() const;
		// Returns the squared length of this Vector4.
		double LengthSquared() const;
		// Turns this Vector4 to a unit vector with the same direction.
		void Normalize();
		// Round the members of this Vector4 to the nearest integer value.
		void Round();
		void Deconstruct(double& x, double& y, double& z, double& w) const;
		// Compares whether current instance is equal to specified Vector4.
		bool Equals(Vector4 const& other) const;

		
		
		//----- C# code not implemented
		// static Vector4 Transform(Vector2 const& value, Quaternion const& rotation);
		// static Vector4 Transform(Vector3 const& value, Quaternion const& rotation);
		// static Vector4 Transform(Vector4 const& value, Quaternion const& rotation);
		
		// This methods call Transform(Vector4, Quaternion) in its implementation
		// static void Transform(std::vector<Vector4> const& sourceArray, i32 sourceIndex, Quaternion& rotation, std::vector<Vector4>& destinationArray, i32 destinationIndex, i32 length);
		// static void Transform(std::vector<Vector4> const& sourceArray, Quaternion& matrix, std::vector<Vector4>& destinationArray);	
	};
}

#endif