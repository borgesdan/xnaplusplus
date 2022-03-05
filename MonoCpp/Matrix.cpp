#include <cmath>

#include "Matrix.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Point.h"
#include "Quaternion.h"
#include "MathHelper.h"
#include "Rectangle.h"

namespace Xna {
	
    Matrix::Matrix():
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

	double& Matrix::operator[] (long index) {
        
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

        long row = row_col.X;
        long column = row_col.Y;        
        return (*this)[(row * 4) + column];
    }

    // static
    Matrix Matrix::Identity() {
        return Matrix(1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1);
    }

    Matrix Matrix::Add(Matrix matrix1, Matrix matrix2) {
        matrix1.M11 += matrix2.M11;
        matrix1.M12 += matrix2.M12;
        matrix1.M13 += matrix2.M13;
        matrix1.M14 += matrix2.M14;
        matrix1.M21 += matrix2.M21;
        matrix1.M22 += matrix2.M22;
        matrix1.M23 += matrix2.M23;
        matrix1.M24 += matrix2.M24;
        matrix1.M31 += matrix2.M31;
        matrix1.M32 += matrix2.M32;
        matrix1.M33 += matrix2.M33;
        matrix1.M34 += matrix2.M34;
        matrix1.M41 += matrix2.M41;
        matrix1.M42 += matrix2.M42;
        matrix1.M43 += matrix2.M43;
        matrix1.M44 += matrix2.M44;
        return matrix1;
    }

    Matrix Matrix::CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition,
        Vector3 cameraUpVector, Vector3 cameraForwardVector) {

        Vector3 vector(0);
        Vector3 vector2(0);
        Vector3 vector3(0);
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

    Matrix Matrix::CreateFromAxisAngle(Vector3 axis, double angle) {
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

    Matrix Matrix::CreateFromQuaternion(Quaternion quaternion) {
        //TODO
        return Matrix();
    }

    Matrix Matrix::CreateFromYawPitchRoll(double yaw, double pitch, double roll) {
        //TODO: It's necessary the quaternion class
        return Matrix();
    }

    Matrix Matrix::CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector) {

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

        //TODO
        if (nearPlaneDistance <= 0.0) {
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
        
        double negFarRange = IsPositiveInfinity(farPlaneDistance) 
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

    Matrix Matrix::CreatePerspectiveOffCenter(Rectangle viewingVolume, double nearPlaneDistance, double farPlaneDistance) {
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

    Matrix Matrix::CreateScale(Vector3 scales) {

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

    // members

    Vector3 Matrix::Backward() {
        return Vector3(M31, M32, M33);
    }

    void Matrix::Backward(Vector3 value) {
        M31 = value.X;
        M32 = value.Y;
        M33 = value.Z;
    }

    Vector3 Matrix::Down() {
        return Vector3(-M21, -M22, -M23);
    }

    void Matrix::Down(Vector3 value) {
        M21 = -value.X;
        M22 = -value.Y;
        M23 = -value.Z;
    }

    Vector3 Matrix::Forward() {
        return Vector3(-M31, -M32, -M33);
    }

    void Matrix::Forward(Vector3 value) {
        M31 = -value.X;
        M32 = -value.Y;
        M33 = -value.Z;
    }

    Vector3 Matrix::Left() {
        return Vector3(-M11, -M12, -M13);
    }

    void Matrix::Left(Vector3 value) {
        M11 = -value.X;
        M12 = -value.Y;
        M13 = -value.Z;
    }

    Vector3 Matrix::Right() {
        return Vector3(M11, M12, M13);
    }

    void Matrix::Right(Vector3 value) {
        M11 = value.X;
        M12 = value.Y;
        M13 = value.Z;
    }

    Vector3 Matrix::Translation() {
        return Vector3(M41, M42, M43);
    }

    void Matrix::Translation(Vector3 value) {
        M41 = value.X;
        M42 = value.Y;
        M43 = value.Z;
    }

    Vector3 Matrix::Up() {
        return Vector3(M21, M22, M23);
    }

    void Matrix::Up(Vector3 value) {
        M21 = value.X;
        M22 = value.Y;
        M23 = value.Z;
    }
}