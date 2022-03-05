#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

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
		double& operator[] (long);
		double& operator[] (Point);
		Matrix operator- ();
		friend Matrix operator+ (Matrix matrix1, Matrix matrix2);
		friend Matrix operator- (Matrix matrix1, Matrix matrix2);
		friend Matrix operator/ (Matrix matrix1, Matrix matrix2);
		friend Matrix operator/ (Matrix matrix, double divider);
		friend bool operator== (Matrix matrix1, Matrix matrix2);
		friend bool operator!= (Matrix matrix1, Matrix matrix2);
		friend Matrix operator* (Matrix matrix1, Matrix matrix2);
		friend Matrix operator* (Matrix matrix, double scaleFactor);

		static Matrix Identity();
		static Matrix Add(Matrix, Matrix);
		static Matrix CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition,
			Vector3 cameraUpVector, Vector3 cameraForwardVector);
		static Matrix CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition,
			Vector3 rotateAxis, Vector3 cameraForwardVector, Vector3 objectForwardVector);
		static Matrix CreateFromAxisAngle(Vector3 axis, double angle);
		static Matrix CreateFromQuaternion(Quaternion quaternion);
		static Matrix CreateFromYawPitchRoll(double yaw, double pitch, double roll);
		static Matrix CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);
		static Matrix CreateOrthographic(double width, double height, double zNearPlane, double zFarPlane);
		static Matrix CreateOrthographicOffCenter(double left, double right, double bottom, double top, double zNearPlane, double zFarPlane);
		static Matrix CreatePerspective(double width, double height, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(Rectangle viewingVolume, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(double left, double right, double bottom, double top, double nearPlaneDistance, double farPlaneDistance);
		static Matrix CreateRotationX(double radians);
		static Matrix CreateRotationY(double radians);
		static Matrix CreateRotationZ(double radians);
		static Matrix CreateScale(double scale);
		static Matrix CreateScale(double xScale, double yScale, double zScale);
		static Matrix CreateScale(Vector3 scales);
		static Matrix CreateShadow(Vector3 lightDirection, Plane plane);
		static Matrix CreateTranslation(double xPosition, double yPosition, double zPosition);
		static Matrix CreateTranslation(Vector3 position, Matrix result);
		static Matrix CreateTranslation(Vector3 position);
		static Matrix CreateReflection(Plane value);
		static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up);		
		static Matrix Divide(Matrix matrix1, Matrix matrix2);
		static Matrix Divide(Matrix matrix1, double divider);
		static Matrix Invert(Matrix matrix);
		static Matrix Lerp(Matrix matrix1, Matrix matrix2, double amount);
		static Matrix Multiply(Matrix matrix1, Matrix matrix2);
		static Matrix Multiply(Matrix matrix1, double scaleFactor);
		static std::vector<double> TodoubleArray(Matrix matrix);
		static Matrix Negate(Matrix matrix);
		static Matrix Subtract(Matrix matrix1, Matrix matrix2);
		static Matrix Transpose(Matrix matrix);
		static void FindDeterminants(Matrix matrix,  double major,
			double minor1,  double minor2,  double minor3,  double minor4,  double minor5,  double minor6,
			double minor7,  double minor8,  double minor9,  double minor10,  double minor11,  double minor12);

		Vector3 Backward();
		void Backward(Vector3 value);		
		Vector3 Down();
		void Down(Vector3 value);
		Vector3 Forward();
		void Forward(Vector3 value);	
		Vector3 Left();
		void Left(Vector3 value);
		Vector3 Right();
		void Right(Vector3 value);
		Vector3 Translation();
		void Translation(Vector3 value);
		Vector3 Up();
		void Up(Vector3 value);
		bool Decompose(Vector3 scale, Quaternion rotation, Vector3 translation);
		double Determinant();
		bool Equals(Matrix other);
	};
}

#endif // !_MATRIX_H_