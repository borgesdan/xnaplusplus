#ifndef VECTORS_H
#define VECTORS_H

#include <vector>
#include "CSharp.h"

namespace Xna {	

	struct Point;
	struct Quaternion;
	struct Matrix;
	struct Plane;
	
	//-------------------------------//
	//-----		$ VECTOR2		-----//	
	//-------------------------------//

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
		static void Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Quaternion const& rotation, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray);
		static void Transform(std::vector<Vector2> const& sourceArray, Quaternion const& rotation, std::vector<Vector2> destinationArray);
		static Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix);
		static void TransformNormal(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length);
		static void TransformNormal(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray);

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

	//-------------------------------//
	//-----		$ VECTOR3		-----//	
	//-------------------------------//

	struct Vector3 {
		double X;
		double Y;
		double Z;

		Vector3();
		Vector3(double x, double y, double z);
		Vector3(double value);
		Vector3(Vector2 value, double z);

		Vector3 operator- () const;

		friend Vector3 operator- (Vector3, Vector3);
		friend Vector3 operator+ (Vector3, Vector3);
		friend Vector3 operator* (Vector3, Vector3);
		friend Vector3 operator* (Vector3, double);
		friend Vector3 operator* (double, Vector3);
		friend Vector3 operator/ (Vector3, Vector3);
		friend Vector3 operator/ (Vector3, double);
		friend bool operator== (Vector3, Vector3);
		friend bool operator!= (Vector3, Vector3);

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
		bool Equals(Vector3 const& other) const;
	};

	//-------------------------------//
	//-----		$ VECTOR4		-----//	
	//-------------------------------//

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
		friend Vector4 operator- (Vector4, Vector4);
		friend Vector4 operator+ (Vector4, Vector4);
		friend Vector4 operator* (Vector4, Vector4);
		friend Vector4 operator* (Vector4, double);
		friend Vector4 operator* (double, Vector4);
		friend Vector4 operator/ (Vector4, Vector4);
		friend Vector4 operator/ (Vector4, i32);
		friend bool operator== (Vector4, Vector4);
		friend bool operator!= (Vector4, Vector4);

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
		static void Transform(std::vector<Vector4> const& sourceArray, i32 sourceIndex, Matrix& matrix, std::vector<Vector4>& destinationArray, i32 destinationIndex, i32 length);
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

	//-------------------------------//
	//-----		$ POINT			-----//	
	//-------------------------------//

	struct Point {
		i32 X;
		i32 Y;

		Point(i32 x, i32 y);
		Point(i32 value);

		friend Point operator+ (Point value1, Point value2);
		friend Point operator- (Point value1, Point value2);
		friend Point operator* (Point value1, Point value2);
		friend Point operator/ (Point value1, Point value2);
		friend Point operator== (Point value1, Point value2);
		friend Point operator!= (Point value1, Point value2);

		//Returns a point with coordinates 0, 0.
		static Point Zero();

		//Gets a vector2 representation for this object.		
		Vector2 ToVector2() const;

		//Deconstruction method for point.
		void Deconstruct(i32& x, i32& y) const;
		//Compares whether current instance is equal to specified point.
		bool Equals(Point const& other) const;
	};

	//-------------------------------//
	//-----		$ RECTANGLE		-----//	
	//-------------------------------//

	struct Rectangle {

		i32 X;
		i32 Y;
		i32 Width;
		i32 Height;

		Rectangle();
		Rectangle(i32 x, i32 y, i32 width, i32 height);
		Rectangle(Point location, Point size);

		friend bool operator== (Rectangle, Rectangle);
		friend bool operator!= (Rectangle, Rectangle);

		// Returns a rectangle with X=0, Y=0, Width=0, Height=0.
		static Rectangle Empty();

		//Creates a new rectangle that contains overlapping region of two other rectangles.
		static Rectangle Intersects(Rectangle const&, Rectangle const&);

		//Creates a new rectangle that completely contains two other rectangles.
		static Rectangle Union(Rectangle const&, Rectangle const&);

		//Returns the x coordinate of the left edge.
		i32 Left() const;
		//Returns the x coordinate of the right edge.
		i32 Right() const;
		//Returns the y coordinate of the top edge.
		i32 Top() const;
		//Returns the y coordinate of the bottom edge.
		i32 Bottom() const;
		//If this rectangle is with X=0, Y=0, Width=0, Height=0.
		bool IsEmpty() const;

		//The top-left coordinate.
		Point Location() const;
		void Location(Point const& value);

		//The width-height coordinates.
		Point Size() const;
		void Size(Point const& value);

		//A point located in the center of this rectangle.
		Point Center() const;

		//Gets whether or not the provided coordinates lie within the bounds.
		bool Contains(i32 x, i32 y) const;
		bool Contains(double x, double y) const;
		bool Contains(Point const& value) const;
		bool Contains(Rectangle const& value) const;

		//Adjusts the edges of this rectangle by specified horizontal and vertical amounts.
		void Inflate(i32 horizontalAmount, i32 verticalAmount);
		void Inflate(double horizontalAmount, double verticalAmount);

		//Gets whether or not the other rectangle intersects with this rectangle.
		bool Intersects(Rectangle const& value) const;

		//Changes the location of this rectangle..
		void Offset(i32 offsetX, i32 offsetY);
		void Offset(double offsetX, double offsetY);
		void Offset(Point const& amount);
		void Offset(Vector2 const& amount);

		//Deconstruction method for rectangle.
		void Deconstruct(long& x, long& y, long& width, long& height) const;
		//Compares whether current rectangle is equal to specified rectangle.
		bool Equals(Rectangle const& other) const;
	};

	//-------------------------------//
	//-----		$ QUATERNION	-----//	
	//-------------------------------//

	struct Quaternion {
		double X;
		double Y;
		double Z;
		double W;

		Quaternion();
		Quaternion(double x, double y, double z, double w);
		Quaternion(Vector3 value, double w);
		Quaternion(Vector4 value);

		Quaternion operator -(Quaternion quaternion);
		friend Quaternion operator +(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator /(Quaternion quaternion1, Quaternion quaternion2);
		friend bool operator ==(Quaternion quaternion1, Quaternion quaternion2);
		friend bool operator !=(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator *(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator -(Quaternion quaternion1, Quaternion quaternion2);

		static Quaternion Identity();
		static Quaternion Add(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Concatenate(Quaternion const& value1, Quaternion const& value2);
		static Quaternion Conjugate(Quaternion const& value);
		static Quaternion CreateFromAxisAngle(Vector3 const& axis, double angle);
		static Quaternion CreateFromRotationMatrix(Matrix const& matrix);
		static Quaternion CreateFromYawPitchRoll(double yaw, double pitch, double roll);
		static Quaternion Divide(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static double Dot(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Inverse(Quaternion const& quaternion);
		static Quaternion Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount);
		static Quaternion Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount);
		static Quaternion Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, double scaleFactor);
		static Quaternion Negate(Quaternion const& quaternion);
		static Quaternion Normalize(Quaternion const& quaternion);

		void Conjugate();
		double Length() const;
		double LengthSquared() const;
		void Normalize();
		Vector4 ToVector4() const;
		bool Equals(Quaternion const& other) const;
	};

	//-------------------------------//
	//-----		$ MATRIX		-----//	
	//-------------------------------//

	struct Matrix {
		double M11;
		double M12;
		double M13;
		double M14;

		double M21;
		double M22;
		double M23;
		double M24;

		double M31;
		double M32;
		double M33;
		double M34;

		double M41;
		double M42;
		double M43;
		double M44;

		Matrix();

		Matrix(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31,
			double m32, double m33, double m34, double m41, double m42, double m43, double m44);

		Matrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);

		//Se for um número fora de 0 a 15 retornará M11.
		double& operator[] (size_t index);
		double& operator[] (Point row_col);
		Matrix operator- (Matrix matrix);
		friend Matrix operator+ (Matrix matrix1, Matrix matrix2);
		friend Matrix operator- (Matrix matrix1, Matrix matrix2);
		friend Matrix operator/ (Matrix matrix1, Matrix matrix2);
		friend Matrix operator/ (Matrix matrix, double divider);
		friend bool operator== (Matrix matrix1, Matrix matrix2);
		friend bool operator!= (Matrix matrix1, Matrix matrix2);
		friend Matrix operator* (Matrix matrix1, Matrix matrix2);
		friend Matrix operator* (Matrix matrix, double scaleFactor);

		static Matrix Identity();
		static Matrix Add(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 const& cameraUpVector, Vector3 const& cameraForwardVector);
		static Matrix CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition,
			Vector3 rotateAxis, Vector3 cameraForwardVector, Vector3 objectForwardVector);
		static Matrix CreateFromAxisAngle(Vector3 const& axis, double const& angle);
		static Matrix CreateFromQuaternion(Quaternion const& quaternion);
		static Matrix CreateFromYawPitchRoll(double yaw, double pitch, double roll);
		static Matrix CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector);
		static Matrix CreateOrthographic(double width, double height, double zNearPlane, double zFarPlane);
		static Matrix CreateOrthographicOffCenter(double left, double right, double bottom, double top, double zNearPlane, double zFarPlane);
		static Matrix CreatePerspective(double width, double height, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(Rectangle const& viewingVolume, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(double left, double right, double bottom, double top, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreateRotationX(double radians);
		static Matrix CreateRotationY(double radians);
		static Matrix CreateRotationZ(double radians);
		static Matrix CreateScale(double scale);
		static Matrix CreateScale(double xScale, double yScale, double zScale);
		static Matrix CreateScale(Vector3 const& scales);
		static Matrix CreateShadow(Vector3 const& lightDirection, Plane const& plane);
		static Matrix CreateTranslation(double xPosition, double yPosition, double zPosition);
		static Matrix CreateTranslation(Vector3 const& position);
		static Matrix CreateReflection(Plane const& value);
		static Matrix CreateWorld(Vector3 const& position, Vector3 const& forward, Vector3 const& up);
		static Matrix Divide(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Divide(Matrix const& matrix1, double divider);
		static Matrix Invert(Matrix const& matrix);
		static Matrix Lerp(Matrix const& matrix1, Matrix const& matrix2, double amount);
		static Matrix Multiply(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Multiply(Matrix const& matrix1, double scaleFactor);
		static std::vector<double> ToDoubleArray(Matrix const& matrix);
		static Matrix Negate(Matrix const& matrix);
		static Matrix Subtract(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Transpose(Matrix const& matrix);

		Vector3 Backward() const;
		Vector3 Down() const;
		Vector3 Forward() const;
		Vector3 Left() const;
		Vector3 Right() const;
		Vector3 Up() const;
		Vector3 Translation() const;

		void Backward(Vector3 value);
		void Down(Vector3 value);
		void Forward(Vector3 value);
		void Left(Vector3 value);
		void Right(Vector3 value);
		void Translation(Vector3 value);
		void Up(Vector3 value);
		bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;
		double Determinant() const;
		bool Equals(Matrix const& other) const;
	};	
}

#endif