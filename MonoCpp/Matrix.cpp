#include <cmath>

#include "Matrix.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Point.h"
#include "Quaternion.h"
#include "MathHelper.h"
#include "Rectangle.h"
#include "Plane.h"

namespace Xna {

	Matrix::Matrix() :
		M11(0), M12(0), M13(0), M14(0),
		M21(0), M22(0), M23(0), M24(0),
		M31(0), M32(0), M33(0), M34(0),
		M41(0), M42(0), M43(0), M44(0) {}

	Matrix::Matrix(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31,
		double m32, double m33, double m34, double m41, double m42, double m43, double m44) :
		M11(m11), M12(m12), M13(m13), M14(m14),
		M21(m21), M22(m22), M23(m23), M24(m24),
		M31(m31), M32(m32), M33(m33), M34(m34),
		M41(m41), M42(m42), M43(m43), M44(m44) {}

	Matrix::Matrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4) :
		M11(row1.X), M12(row1.Y), M13(row1.Z), M14(row1.W),
		M21(row2.X), M22(row2.Y), M23(row2.Z), M24(row2.W),
		M31(row3.X), M32(row3.Y), M33(row3.Z), M34(row3.W),
		M41(row4.X), M42(row4.Y), M43(row4.Z), M44(row4.W) {}

	//----- Operators

	double& Matrix::operator[] (size_t index) {

		switch (index)
		{
		case 0: return M11;
		case 1: return M12;
		case 2: return M13;
		case 3: return M14;
		case 4: return M21;
		case 5: return M22;
		case 6: return M23;
		case 7: return M24;
		case 8: return M31;
		case 9: return M32;
		case 10: return M33;
		case 11: return M34;
		case 12: return M41;
		case 13: return M42;
		case 14: return M43;
		case 15: return M44;
		default: return M11;
		}
	}

	double& Matrix::operator[] (Point row_col) {

		i32 row = row_col.X;
		i32 column = row_col.Y;
		return (*this)[(row * 4) + column];
	}

	Matrix Matrix::operator- (Matrix matrix) {
		return Matrix::Negate(matrix);
	}

	Matrix operator+ (Matrix matrix1, Matrix matrix2) {
		return Matrix::Add(matrix1, matrix2);
	}

	Matrix operator- (Matrix matrix1, Matrix matrix2) {
		return Matrix::Subtract(matrix1, matrix2);
	}

	Matrix operator/ (Matrix matrix1, Matrix matrix2) {
		return Matrix::Divide(matrix1, matrix2);
	}

	Matrix operator/ (Matrix matrix, double divider) {
		return Matrix::Divide(matrix, divider);
	}

	Matrix operator* (Matrix matrix1, Matrix matrix2) {
		return Matrix::Multiply(matrix1, matrix2);
	}

	Matrix operator* (Matrix matrix, double scaleFactor) {
		return Matrix::Multiply(matrix, scaleFactor);
	}


	bool operator== (Matrix matrix1, Matrix matrix2) {
		return matrix1.Equals(matrix2);
	}

	bool operator!= (Matrix matrix1, Matrix matrix2) {
		return !matrix1.Equals(matrix2);
	}
	
	//----- Static
	Matrix Matrix::Identity() {
		return Matrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	Matrix Matrix::Add(Matrix const& matrix1, Matrix const& matrix2) {
		Matrix result = matrix1;
		
		result.M11 += matrix2.M11;
		result.M12 += matrix2.M12;
		result.M13 += matrix2.M13;
		result.M14 += matrix2.M14;
		result.M21 += matrix2.M21;
		result.M22 += matrix2.M22;
		result.M23 += matrix2.M23;
		result.M24 += matrix2.M24;
		result.M31 += matrix2.M31;
		result.M32 += matrix2.M32;
		result.M33 += matrix2.M33;
		result.M34 += matrix2.M34;
		result.M41 += matrix2.M41;
		result.M42 += matrix2.M42;
		result.M43 += matrix2.M43;
		result.M44 += matrix2.M44;
		return result;
	}

	Matrix Matrix::CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
		Vector3 const& cameraUpVector, Vector3 const& cameraForwardVector) {

		Vector3 vector;
		Vector3 vector2;
		Vector3 vector3;
		vector.X = objectPosition.X - cameraPosition.X;
		vector.Y = objectPosition.Y - cameraPosition.Y;
		vector.Z = objectPosition.Z - cameraPosition.Z;

		double num = vector.LengthSquared();

		if (num < 0.0001) {
			vector = -cameraForwardVector;
		}
		else {
			vector = Vector3::Multiply(vector, 1 / sqrt(num));
		}

		vector3 = Vector3::Cross(cameraUpVector, vector);
		vector3.Normalize();
		vector2 = Vector3::Cross(vector, vector3);

		Matrix result;

		result.M11 = vector3.X;
		result.M12 = vector3.Y;
		result.M13 = vector3.Z;
		result.M14 = 0;
		result.M21 = vector2.X;
		result.M22 = vector2.Y;
		result.M23 = vector2.Z;
		result.M24 = 0;
		result.M31 = vector.X;
		result.M32 = vector.Y;
		result.M33 = vector.Z;
		result.M34 = 0;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition,
		Vector3 rotateAxis, Vector3 cameraForwardVector, Vector3 objectForwardVector) {

		double num;
		Vector3 vector;
		Vector3 vector2;
		Vector3 vector3;
		vector2.X = objectPosition.X - cameraPosition.X;
		vector2.Y = objectPosition.Y - cameraPosition.Y;
		vector2.Z = objectPosition.Z - cameraPosition.Z;
		double num2 = vector2.LengthSquared();

		if (num2 < 0.0001) {
			vector2 = -cameraForwardVector;
		}
		else {
			vector2 = Vector3::Multiply(vector2, 1 / sqrt(num2));
		}

		Vector3 vector4 = rotateAxis;
		num = Vector3::Dot(rotateAxis, vector2);

		if (abs(num) > 0.9982547) {

			vector = objectForwardVector;
			num = Vector3::Dot(rotateAxis, vector);

			if (abs(num) > 0.9982547)
			{
				num = ((rotateAxis.X * Vector3::Forward().X)
					+ (rotateAxis.Y * Vector3::Forward().Y))
					+ (rotateAxis.Z * Vector3::Forward().Z);

				vector = (abs(num) > 0.9982547f)
					? Vector3::Right() : Vector3::Forward();
			}

			vector3 = Vector3::Cross(rotateAxis, vector);
			vector3.Normalize();

			vector = Vector3::Cross(vector3, rotateAxis);
			vector.Normalize();
		}
		else {

			vector3 = Vector3::Cross(rotateAxis, vector2);
			vector3.Normalize();
			vector = Vector3::Cross(vector3, vector4);
			vector.Normalize();
		}

		Matrix result;

		result.M11 = vector3.X;
		result.M12 = vector3.Y;
		result.M13 = vector3.Z;
		result.M14 = 0;
		result.M21 = vector4.X;
		result.M22 = vector4.Y;
		result.M23 = vector4.Z;
		result.M24 = 0;
		result.M31 = vector.X;
		result.M32 = vector.Y;
		result.M33 = vector.Z;
		result.M34 = 0;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateFromAxisAngle(Vector3 const& axis, double const& angle) {
		double x = axis.X;
		double y = axis.Y;
		double z = axis.Z;
		double num2 = sin(angle);
		double num = cos(angle);
		double num11 = x * x;
		double num10 = y * y;
		double num9 = z * z;
		double num8 = x * y;
		double num7 = x * z;
		double num6 = y * z;

		Matrix result;
		result.M11 = num11 + (num * (1.0 - num11));
		result.M12 = (num8 - (num * num8)) + (num2 * z);
		result.M13 = (num7 - (num * num7)) - (num2 * y);
		result.M14 = 0;
		result.M21 = (num8 - (num * num8)) - (num2 * z);
		result.M22 = num10 + (num * (1.0 - num10));
		result.M23 = (num6 - (num * num6)) + (num2 * x);
		result.M24 = 0;
		result.M31 = (num7 - (num * num7)) + (num2 * y);
		result.M32 = (num6 - (num * num6)) - (num2 * x);
		result.M33 = num9 + (num * (1.0 - num9));
		result.M34 = 0;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateFromQuaternion(Quaternion const& quaternion) {
		double num9 = quaternion.X * quaternion.X;
		double num8 = quaternion.Y * quaternion.Y;
		double num7 = quaternion.Z * quaternion.Z;
		double num6 = quaternion.X * quaternion.Y;
		double num5 = quaternion.Z * quaternion.W;
		double num4 = quaternion.Z * quaternion.X;
		double num3 = quaternion.Y * quaternion.W;
		double num2 = quaternion.Y * quaternion.Z;
		double num = quaternion.X * quaternion.W;

		Matrix result;
		result.M11 = 1.0 - (2.0 * (num8 + num7));
		result.M12 = 2.0 * (num6 + num5);
		result.M13 = 2.0 * (num4 - num3);
		result.M14 = 0.0;
		result.M21 = 2.0 * (num6 - num5);
		result.M22 = 1.0 - (2.0 * (num7 + num9));
		result.M23 = 2.0 * (num2 + num);
		result.M24 = 0.0;
		result.M31 = 2.0 * (num4 + num3);
		result.M32 = 2.0 * (num2 - num);
		result.M33 = 1.0 - (2.0 * (num8 + num9));
		result.M34 = 0.0;
		result.M41 = 0.0;
		result.M42 = 0.0;
		result.M43 = 0.0;
		result.M44 = 1.0;

		return result;
	}

	Matrix Matrix::CreateFromYawPitchRoll(double yaw, double pitch, double roll) {
		Quaternion quaternion =	Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
		return CreateFromQuaternion(quaternion);
	}

	Matrix Matrix::CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector) {

		Vector3 vector = Vector3::Normalize(cameraPosition - cameraTarget);
		Vector3 vector2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector));
		Vector3 vector3 = Vector3::Cross(vector, vector2);

		Matrix result;
		result.M11 = vector2.X;
		result.M12 = vector3.X;
		result.M13 = vector.X;
		result.M14 = 0.0;
		result.M21 = vector2.Y;
		result.M22 = vector3.Y;
		result.M23 = vector.Y;
		result.M24 = 0.0;
		result.M31 = vector2.Z;
		result.M32 = vector3.Z;
		result.M33 = vector.Z;
		result.M34 = 0.0;
		result.M41 = -Vector3::Dot(vector2, cameraPosition);
		result.M42 = -Vector3::Dot(vector3, cameraPosition);
		result.M43 = -Vector3::Dot(vector, cameraPosition);
		result.M44 = 1.0;

		return result;
	}

	Matrix Matrix::CreateOrthographic(double width, double height, double zNearPlane, double zFarPlane) {

		Matrix result;
		result.M11 = 2.0 / width;
		result.M12 = result.M13 = result.M14 = 0.0;
		result.M22 = 2.0 / height;
		result.M21 = result.M23 = result.M24 = 0.0;
		result.M33 = 1.0 / (zNearPlane - zFarPlane);
		result.M31 = result.M32 = result.M34 = 0.0;
		result.M41 = result.M42 = 0.0;
		result.M43 = zNearPlane / (zNearPlane - zFarPlane);
		result.M44 = 1.0;

		return result;
	}

	Matrix Matrix::CreateOrthographicOffCenter(double left, double right, double bottom, double top, double zNearPlane, double zFarPlane) {

		Matrix result;

		result.M11 = 2.0 / right - left;
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 2.0 / top - bottom;
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0 / zNearPlane - zFarPlane;
		result.M34 = 0.0f;
		result.M41 = left + right / left - right;
		result.M42 = top + bottom / bottom - top;
		result.M43 = zNearPlane / zNearPlane - zFarPlane;
		result.M44 = 1.0f;

		return result;
	}

	Matrix Matrix::CreatePerspective(double width, double height, double nearPlaneDistance, double farPlaneDistance) {

		if (nearPlaneDistance <= 0.0) {
			nearPlaneDistance = 0.1;
		}
		if (farPlaneDistance <= 0.0) {
			farPlaneDistance = 0.1;
		}
		if (nearPlaneDistance >= farPlaneDistance) {
			farPlaneDistance = 0.5;
		}

		double negFarRange = MathHelper::IsPositiveInfinity(farPlaneDistance)
			? -1.0
			: farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

		Matrix result;
		result.M11 = (2.0f * nearPlaneDistance) / width;
		result.M12 = result.M13 = result.M14 = 0.0f;
		result.M22 = (2.0f * nearPlaneDistance) / height;
		result.M21 = result.M23 = result.M24 = 0.0f;
		result.M33 = negFarRange;
		result.M31 = result.M32 = 0.0f;
		result.M34 = -1.0f;
		result.M41 = result.M42 = result.M44 = 0.0f;
		result.M43 = nearPlaneDistance * negFarRange;

		return result;
	}

	Matrix Matrix::CreatePerspectiveOffCenter(Rectangle const& viewingVolume, double nearPlaneDistance, double farPlaneDistance) {
		return CreatePerspectiveOffCenter(viewingVolume.Left(), viewingVolume.Right(), viewingVolume.Bottom(), viewingVolume.Top(), nearPlaneDistance, farPlaneDistance);
	}

	Matrix Matrix::CreatePerspectiveOffCenter(double left, double right, double bottom, double top, double nearPlaneDistance, double farPlaneDistance) {

		//TODO:

		if (nearPlaneDistance <= 0.0)
		{
			//throw new ArgumentException("nearPlaneDistance <= 0");
		}
		if (farPlaneDistance <= 0.0)
		{
			//throw new ArgumentException("farPlaneDistance <= 0");
		}
		if (nearPlaneDistance >= farPlaneDistance)
		{
			//throw new ArgumentException("nearPlaneDistance >= farPlaneDistance");
		}

		Matrix result;
		result.M11 = (2.0 * nearPlaneDistance) / (right - left);
		result.M12 = result.M13 = result.M14 = 0;
		result.M22 = (2.0 * nearPlaneDistance) / (top - bottom);
		result.M21 = result.M23 = result.M24 = 0;
		result.M31 = (left + right) / (right - left);
		result.M32 = (top + bottom) / (top - bottom);
		result.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		result.M34 = -1;
		result.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		result.M41 = result.M42 = result.M44 = 0.0;

		return result;
	}

	Matrix Matrix::CreateRotationX(double radians) {
		Matrix result = Matrix::Identity();

		double val1 = cos(radians);
		double val2 = sin(radians);

		result.M22 = val1;
		result.M23 = val2;
		result.M32 = -val2;
		result.M33 = val1;

		return result;
	}

	Matrix Matrix::CreateRotationY(double radians) {
		Matrix result = Matrix::Identity();

		double val1 = cos(radians);
		double val2 = sin(radians);

		result.M11 = val1;
		result.M13 = -val2;
		result.M31 = val2;
		result.M33 = val1;

		return result;
	}

	Matrix Matrix::CreateRotationZ(double radians) {
		Matrix result = Matrix::Identity();

		double val1 = cos(radians);
		double val2 = sin(radians);

		result.M11 = val1;
		result.M12 = val2;
		result.M21 = -val2;
		result.M22 = val1;

		return result;
	}

	Matrix Matrix::CreateScale(double scale) {
		return CreateScale(scale, scale, scale);
	}

	Matrix Matrix::CreateScale(double xScale, double yScale, double zScale) {

		Matrix result;

		result.M11 = xScale;
		result.M12 = 0;
		result.M13 = 0;
		result.M14 = 0;
		result.M21 = 0;
		result.M22 = yScale;
		result.M23 = 0;
		result.M24 = 0;
		result.M31 = 0;
		result.M32 = 0;
		result.M33 = zScale;
		result.M34 = 0;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateScale(Vector3 const& scales) {

		Matrix result;

		result.M11 = scales.X;
		result.M12 = 0;
		result.M13 = 0;
		result.M14 = 0;
		result.M21 = 0;
		result.M22 = scales.Y;
		result.M23 = 0;
		result.M24 = 0;
		result.M31 = 0;
		result.M32 = 0;
		result.M33 = scales.Z;
		result.M34 = 0;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateShadow(Vector3 const& lightDirection, Plane const& plane) {
		double dot = (plane.Normal.X * lightDirection.X) + (plane.Normal.Y * lightDirection.Y) + (plane.Normal.Z * lightDirection.Z);
		double x = -plane.Normal.X;
		double y = -plane.Normal.Y;
		double z = -plane.Normal.Z;
		double d = -plane.D;

		Matrix result;
		result.M11 = (x * lightDirection.X) + dot;
		result.M12 = x * lightDirection.Y;
		result.M13 = x * lightDirection.Z;
		result.M14 = 0;
		result.M21 = y * lightDirection.X;
		result.M22 = (y * lightDirection.Y) + dot;
		result.M23 = y * lightDirection.Z;
		result.M24 = 0;
		result.M31 = z * lightDirection.X;
		result.M32 = z * lightDirection.Y;
		result.M33 = (z * lightDirection.Z) + dot;
		result.M34 = 0;
		result.M41 = d * lightDirection.X;
		result.M42 = d * lightDirection.Y;
		result.M43 = d * lightDirection.Z;
		result.M44 = dot;

		return result;
	}

	Matrix Matrix::CreateTranslation(double xPosition, double yPosition, double zPosition) {
		return Matrix::CreateTranslation(Vector3(xPosition, yPosition, zPosition));
	}

	Matrix Matrix::CreateTranslation(Vector3 const& position) {
		Matrix result;
		result.M11 = 1;
		result.M12 = 0;
		result.M13 = 0;
		result.M14 = 0;
		result.M21 = 0;
		result.M22 = 1;
		result.M23 = 0;
		result.M24 = 0;
		result.M31 = 0;
		result.M32 = 0;
		result.M33 = 1;
		result.M34 = 0;
		result.M41 = position.X;
		result.M42 = position.Y;
		result.M43 = position.Z;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateReflection(Plane const& value) {
		Plane plane = Plane::Normalize(value);
		double x = plane.Normal.X;
		double y = plane.Normal.Y;
		double z = plane.Normal.Z;
		double num3 = -2.0 * x;
		double num2 = -2.0 * y;
		double num = -2.0 * z;

		Matrix result;
		result.M11 = (num3 * x) + 1.0;
		result.M12 = num2 * x;
		result.M13 = num * x;
		result.M14 = 0;
		result.M21 = num3 * y;
		result.M22 = (num2 * y) + 1;
		result.M23 = num * y;
		result.M24 = 0;
		result.M31 = num3 * z;
		result.M32 = num2 * z;
		result.M33 = (num * z) + 1;
		result.M34 = 0;
		result.M41 = num3 * plane.D;
		result.M42 = num2 * plane.D;
		result.M43 = num * plane.D;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateWorld(Vector3 const& position, Vector3 const& forward, Vector3 const& up) {
		Vector3 z = Vector3::Normalize(forward);
		Vector3 x = Vector3::Cross(forward, up);
		Vector3 y = Vector3::Cross(x, forward);
		
		x.Normalize();
		y.Normalize();

		Matrix result;		
		result.Right(x);
		result.Up(y);
		result.Forward(z);
		result.Translation(position);
		result.M44 = 1.0;

		return result;
	}


	Matrix Matrix::Divide(Matrix const& matrix1, Matrix const& matrix2) {
		Matrix result;

		result.M11 = matrix1.M11 / matrix2.M11;
		result.M12 = matrix1.M12 / matrix2.M12;
		result.M13 = matrix1.M13 / matrix2.M13;
		result.M14 = matrix1.M14 / matrix2.M14;
		result.M21 = matrix1.M21 / matrix2.M21;
		result.M22 = matrix1.M22 / matrix2.M22;
		result.M23 = matrix1.M23 / matrix2.M23;
		result.M24 = matrix1.M24 / matrix2.M24;
		result.M31 = matrix1.M31 / matrix2.M31;
		result.M32 = matrix1.M32 / matrix2.M32;
		result.M33 = matrix1.M33 / matrix2.M33;
		result.M34 = matrix1.M34 / matrix2.M34;
		result.M41 = matrix1.M41 / matrix2.M41;
		result.M42 = matrix1.M42 / matrix2.M42;
		result.M43 = matrix1.M43 / matrix2.M43;
		result.M44 = matrix1.M44 / matrix2.M44;
		return result;
	}

	Matrix Matrix::Divide(Matrix const& matrix1, double divider) {
		Matrix result;
		
		double num = 1.0 / divider;
		result.M11 = matrix1.M11 * num;
		result.M12 = matrix1.M12 * num;
		result.M13 = matrix1.M13 * num;
		result.M14 = matrix1.M14 * num;
		result.M21 = matrix1.M21 * num;
		result.M22 = matrix1.M22 * num;
		result.M23 = matrix1.M23 * num;
		result.M24 = matrix1.M24 * num;
		result.M31 = matrix1.M31 * num;
		result.M32 = matrix1.M32 * num;
		result.M33 = matrix1.M33 * num;
		result.M34 = matrix1.M34 * num;
		result.M41 = matrix1.M41 * num;
		result.M42 = matrix1.M42 * num;
		result.M43 = matrix1.M43 * num;
		result.M44 = matrix1.M44 * num;
		return result;
	}

	Matrix Matrix::Invert(Matrix const& matrix) {
		double num1 = matrix.M11;
		double num2 = matrix.M12;
		double num3 = matrix.M13;
		double num4 = matrix.M14;
		double num5 = matrix.M21;
		double num6 = matrix.M22;
		double num7 = matrix.M23;
		double num8 = matrix.M24;
		double num9 = matrix.M31;
		double num10 = matrix.M32;
		double num11 = matrix.M33;
		double num12 = matrix.M34;
		double num13 = matrix.M41;
		double num14 = matrix.M42;
		double num15 = matrix.M43;
		double num16 = matrix.M44;
		double num17 = (num11 * num16 - num12 * num15);
		double num18 = (num10 * num16 - num12 * num14);
		double num19 = (num10 * num15 - num11 * num14);
		double num20 = (num9 * num16 - num12 * num13);
		double num21 = (num9 * num15 - num11 * num13);
		double num22 = (num9 * num14 - num10 * num13);
		double num23 = (num6 * num17 - num7 * num18 + num8 * num19);
		double num24 = -(num5 * num17 - num7 * num20 + num8 * num21);
		double num25 = (num5 * num18 - num6 * num20 + num8 * num22);
		double num26 = -(num5 * num19 - num6 * num21 + num7 * num22);
		double num27 = (1.0 / (num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26));

		Matrix result;
		result.M11 = num23 * num27;
		result.M21 = num24 * num27;
		result.M31 = num25 * num27;
		result.M41 = num26 * num27;
		result.M12 = -(num2 * num17 - num3 * num18 + num4 * num19) * num27;
		result.M22 = (num1 * num17 - num3 * num20 + num4 * num21) * num27;
		result.M32 = -(num1 * num18 - num2 * num20 + num4 * num22) * num27;
		result.M42 = (num1 * num19 - num2 * num21 + num3 * num22) * num27;
		double num28 = (num7 * num16 - num8 * num15);
		double num29 = (num6 * num16 - num8 * num14);
		double num30 = (num6 * num15 - num7 * num14);
		double num31 = (num5 * num16 - num8 * num13);
		double num32 = (num5 * num15 - num7 * num13);
		double num33 = (num5 * num14 - num6 * num13);
		result.M13 = (num2 * num28 - num3 * num29 + num4 * num30) * num27;
		result.M23 = -(num1 * num28 - num3 * num31 + num4 * num32) * num27;
		result.M33 = (num1 * num29 - num2 * num31 + num4 * num33) * num27;
		result.M43 = -(num1 * num30 - num2 * num32 + num3 * num33) * num27;
		double num34 = (num7 * num12 - num8 * num11);
		double num35 = (num6 * num12 - num8 * num10);
		double num36 = (num6 * num11 - num7 * num10);
		double num37 = (num5 * num12 - num8 * num9);
		double num38 = (num5 * num11 - num7 * num9);
		double num39 = (num5 * num10 - num6 * num9);
		result.M14 = -(num2 * num34 - num3 * num35 + num4 * num36) * num27;
		result.M24 = (num1 * num34 - num3 * num37 + num4 * num38) * num27;
		result.M34 = -(num1 * num35 - num2 * num37 + num4 * num39) * num27;
		result.M44 = (num1 * num36 - num2 * num38 + num3 * num39) * num27;

		return result;
	}

	Matrix Matrix::Lerp(Matrix const& matrix1, Matrix const& matrix2, double amount) {
		Matrix result;
		
		result.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
		result.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
		result.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
		result.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
		result.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
		result.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
		result.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
		result.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
		result.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
		result.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
		result.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
		result.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
		result.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
		result.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
		result.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
		result.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);
		return result;
	}

	Matrix Matrix::Multiply(Matrix const& matrix1, Matrix const& matrix2) {
		double m11 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
		double m12 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
		double m13 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
		double m14 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
		double m21 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
		double m22 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
		double m23 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
		double m24 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
		double m31 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
		double m32 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
		double m33 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
		double m34 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
		double m41 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
		double m42 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
		double m43 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
		double m44 = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);
		
		Matrix result;
		result.M11 = m11;
		result.M12 = m12;
		result.M13 = m13;
		result.M14 = m14;
		result.M21 = m21;
		result.M22 = m22;
		result.M23 = m23;
		result.M24 = m24;
		result.M31 = m31;
		result.M32 = m32;
		result.M33 = m33;
		result.M34 = m34;
		result.M41 = m41;
		result.M42 = m42;
		result.M43 = m43;
		result.M44 = m44;
		return result;
	}

	Matrix Matrix::Multiply(Matrix const& matrix, double scaleFactor) {
		Matrix result = matrix;

		result.M11 *= scaleFactor;
		result.M12 *= scaleFactor;
		result.M13 *= scaleFactor;
		result.M14 *= scaleFactor;
		result.M21 *= scaleFactor;
		result.M22 *= scaleFactor;
		result.M23 *= scaleFactor;
		result.M24 *= scaleFactor;
		result.M31 *= scaleFactor;
		result.M32 *= scaleFactor;
		result.M33 *= scaleFactor;
		result.M34 *= scaleFactor;
		result.M41 *= scaleFactor;
		result.M42 *= scaleFactor;
		result.M43 *= scaleFactor;
		result.M44 *= scaleFactor;
		return result;
	}

	std::vector<double> Matrix::ToDoubleArray(Matrix const& matrix) {

		return std::vector<double> {
				matrix.M11, matrix.M12, matrix.M13, matrix.M14,
				matrix.M21, matrix.M22, matrix.M23, matrix.M24,
				matrix.M31, matrix.M32, matrix.M33, matrix.M34,
				matrix.M41, matrix.M42, matrix.M43, matrix.M44
		};
	}

	Matrix Matrix::Negate(Matrix const& matrix) {
		Matrix result;
		
		result.M11 = -matrix.M11;
		result.M12 = -matrix.M12;
		result.M13 = -matrix.M13;
		result.M14 = -matrix.M14;
		result.M21 = -matrix.M21;
		result.M22 = -matrix.M22;
		result.M23 = -matrix.M23;
		result.M24 = -matrix.M24;
		result.M31 = -matrix.M31;
		result.M32 = -matrix.M32;
		result.M33 = -matrix.M33;
		result.M34 = -matrix.M34;
		result.M41 = -matrix.M41;
		result.M42 = -matrix.M42;
		result.M43 = -matrix.M43;
		result.M44 = -matrix.M44;
		return result;
	}

	Matrix Matrix::Subtract(Matrix const& matrix1, Matrix const& matrix2) {

		Matrix result;

		result.M11 = matrix1.M11 - matrix2.M11;
		result.M12 = matrix1.M12 - matrix2.M12;
		result.M13 = matrix1.M13 - matrix2.M13;
		result.M14 = matrix1.M14 - matrix2.M14;
		result.M21 = matrix1.M21 - matrix2.M21;
		result.M22 = matrix1.M22 - matrix2.M22;
		result.M23 = matrix1.M23 - matrix2.M23;
		result.M24 = matrix1.M24 - matrix2.M24;
		result.M31 = matrix1.M31 - matrix2.M31;
		result.M32 = matrix1.M32 - matrix2.M32;
		result.M33 = matrix1.M33 - matrix2.M33;
		result.M34 = matrix1.M34 - matrix2.M34;
		result.M41 = matrix1.M41 - matrix2.M41;
		result.M42 = matrix1.M42 - matrix2.M42;
		result.M43 = matrix1.M43 - matrix2.M43;
		result.M44 = matrix1.M44 - matrix2.M44;
		return result;
	}

	Matrix Matrix::Transpose(Matrix const& matrix) {
		Matrix ret;

		ret.M11 = matrix.M11;
		ret.M12 = matrix.M21;
		ret.M13 = matrix.M31;
		ret.M14 = matrix.M41;

		ret.M21 = matrix.M12;
		ret.M22 = matrix.M22;
		ret.M23 = matrix.M32;
		ret.M24 = matrix.M42;

		ret.M31 = matrix.M13;
		ret.M32 = matrix.M23;
		ret.M33 = matrix.M33;
		ret.M34 = matrix.M43;

		ret.M41 = matrix.M14;
		ret.M42 = matrix.M24;
		ret.M43 = matrix.M34;
		ret.M44 = matrix.M44;

		return ret;
	}	

	//----- Members

	Vector3 Matrix::Backward() const {
		return Vector3(M31, M32, M33);
	}

	void Matrix::Backward(Vector3 value) {
		M31 = value.X;
		M32 = value.Y;
		M33 = value.Z;
	}

	Vector3 Matrix::Down() const {
		return Vector3(-M21, -M22, -M23);
	}

	void Matrix::Down(Vector3 value) {
		M21 = -value.X;
		M22 = -value.Y;
		M23 = -value.Z;
	}

	Vector3 Matrix::Forward() const {
		return Vector3(-M31, -M32, -M33);
	}

	void Matrix::Forward(Vector3 value) {
		M31 = -value.X;
		M32 = -value.Y;
		M33 = -value.Z;
	}

	Vector3 Matrix::Left() const {
		return Vector3(-M11, -M12, -M13);
	}

	void Matrix::Left(Vector3 value) {
		M11 = -value.X;
		M12 = -value.Y;
		M13 = -value.Z;
	}

	Vector3 Matrix::Right() const {
		return Vector3(M11, M12, M13);
	}

	void Matrix::Right(Vector3 value) {
		M11 = value.X;
		M12 = value.Y;
		M13 = value.Z;
	}

	Vector3 Matrix::Translation() const {
		return Vector3(M41, M42, M43);
	}

	void Matrix::Translation(Vector3 value) {
		M41 = value.X;
		M42 = value.Y;
		M43 = value.Z;
	}

	Vector3 Matrix::Up()  const {
		return Vector3(M21, M22, M23);
	}

	void Matrix::Up(Vector3 value) {
		M21 = value.X;
		M22 = value.Y;
		M23 = value.Z;
	}

	bool Matrix::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const {
		translation.X = M41;
		translation.Y = M42;
		translation.Z = M43;

		double xs = (MathHelper::Sign(M11 * M12 * M13 * M14) < 0) ? -1 : 1;
		double ys = (MathHelper::Sign(M21 * M22 * M23 * M24) < 0) ? -1 : 1;
		double zs = (MathHelper::Sign(M31 * M32 * M33 * M34) < 0) ? -1 : 1;

		scale.X = xs * MathHelper::Sqrt(M11 * M11 + M12 * M12 + M13 * M13);
		scale.Y = ys * MathHelper::Sqrt(M21 * M21 + M22 * M22 + M23 * M23);
		scale.Z = zs * MathHelper::Sqrt(M31 * M31 + M32 * M32 + M33 * M33);

		if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0)	{
			rotation = Quaternion::Identity();
			return false;
		}

		Matrix m1 = Matrix(M11 / scale.X, M12 / scale.X, M13 / scale.X, 0,
			M21 / scale.Y, M22 / scale.Y, M23 / scale.Y, 0,
			M31 / scale.Z, M32 / scale.Z, M33 / scale.Z, 0,
			0, 0, 0, 1);

		rotation = Quaternion::CreateFromRotationMatrix(m1);
		return true;
	}

	double Matrix::Determinant() const {
		double num22 = M11;
		double num21 = M12;
		double num20 = M13;
		double num19 = M14;
		double num12 = M21;
		double num11 = M22;
		double num10 = M23;
		double num9 = M24;
		double num8 = M31;
		double num7 = M32;
		double num6 = M33;
		double num5 = M34;
		double num4 = M41;
		double num3 = M42;
		double num2 = M43;
		double num = M44;
		double num18 = (num6 * num) - (num5 * num2);
		double num17 = (num7 * num) - (num5 * num3);
		double num16 = (num7 * num2) - (num6 * num3);
		double num15 = (num8 * num) - (num5 * num4);
		double num14 = (num8 * num2) - (num6 * num4);
		double num13 = (num8 * num3) - (num7 * num4);
		
		return (
			(((num22 * (((num11 * num18) - (num10 * num17)) + (num9 * num16))) - (num21 * (((num12 * num18) - (num10 * num15)) + (num9 * num14)))) + (num20 * (((num12 * num17) - (num11 * num15)) + (num9 * num13))))
			- (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13))));
	}

	bool Matrix::Equals(Matrix const& other) const {
		return (M11 == other.M11)
			&& (M22 == other.M22)
			&& (M33 == other.M33)
			&& (M44 == other.M44)
			&& (M12 == other.M12)
			&& (M13 == other.M13)
			&& (M14 == other.M14)
			&& (M21 == other.M21)
			&& (M23 == other.M23)
			&& (M24 == other.M24)
			&& (M31 == other.M31)
			&& (M32 == other.M32)
			&& (M34 == other.M34) 
			&& (M41 == other.M41)
			&& (M42 == other.M42)
			&& (M43 == other.M43);
	}
}