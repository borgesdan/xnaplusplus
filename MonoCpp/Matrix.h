#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "CSharp.h"

namespace Xna {

	struct Vector4;
	struct Point;
	struct Vector3;
	struct Quaternion;
	struct Rectangle;
	struct Plane;

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