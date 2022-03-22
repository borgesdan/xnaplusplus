#include "Structs.h"
#include "MathHelper.h"

namespace Xna {
	Quaternion::Quaternion() :
		X(0), Y(0), Z(0), W(0) {}

	Quaternion::Quaternion(double x, double y, double z, double w) :
		X(x), Y(y), Z(z), W(w) {}

	Quaternion::Quaternion(Vector3 value, double w) :
		X(value.X), Y(value.Y), Z(value.Z), W(0) {}

	Quaternion::Quaternion(Vector4 value) :
		X(value.X), Y(value.Y), Z(value.Z), W(value.W) {}

	Quaternion Quaternion::operator -(Quaternion quaternion) {
		return Quaternion::Negate(quaternion);
	}

	Quaternion operator +(Quaternion quaternion1, Quaternion quaternion2) {
		return Quaternion::Add(quaternion1, quaternion2);
	}

	Quaternion operator /(Quaternion quaternion1, Quaternion quaternion2) {
		return Quaternion::Divide(quaternion1, quaternion2);
	}

	bool operator ==(Quaternion quaternion1, Quaternion quaternion2) {
		return quaternion1.Equals(quaternion2);
	}

	bool operator !=(Quaternion quaternion1, Quaternion quaternion2) {
		return !quaternion1.Equals(quaternion2);
	}

	Quaternion operator *(Quaternion quaternion1, Quaternion quaternion2) {
		return Quaternion::Multiply(quaternion1, quaternion2);
	}

	Quaternion operator -(Quaternion quaternion1, Quaternion quaternion2) {
		return Quaternion::Subtract(quaternion1, quaternion2);
	}

	Quaternion Quaternion::Identity() { return Quaternion(0, 0, 0, 1); }

	Quaternion Quaternion::Add(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion(
			quaternion1.X + quaternion2.X,
			quaternion1.Y + quaternion2.Y,
			quaternion1.Z + quaternion2.Z,
			quaternion1.W + quaternion2.W);
	}

	Quaternion Quaternion::Concatenate(Quaternion const& value1, Quaternion const& value2) {
		Quaternion quaternion;

		double x1 = value1.X;
		double y1 = value1.Y;
		double z1 = value1.Z;
		double w1 = value1.W;

		double x2 = value2.X;
		double y2 = value2.Y;
		double z2 = value2.Z;
		double w2 = value2.W;

		quaternion.X = ((x2 * w1) + (x1 * w2)) + ((y2 * z1) - (z2 * y1));
		quaternion.Y = ((y2 * w1) + (y1 * w2)) + ((z2 * x1) - (x2 * z1));
		quaternion.Z = ((z2 * w1) + (z1 * w2)) + ((x2 * y1) - (y2 * x1));
		quaternion.W = (w2 * w1) - (((x2 * x1) + (y2 * y1)) + (z2 * z1));

		return quaternion;
	}

	Quaternion Quaternion::Conjugate(Quaternion const& value) {
		return Quaternion(-value.X, -value.Y, -value.Z, value.W);
	}

	Quaternion Quaternion::CreateFromAxisAngle(Vector3 const& axis, double angle) {
		double half = angle * 0.5f;
		double sin = MathHelper::Sin(half);
		double cos = MathHelper::Cos(half);
		return Quaternion(axis.X * sin, axis.Y * sin, axis.Z * sin, cos);
	}

	Quaternion Quaternion::CreateFromRotationMatrix(Matrix const& matrix) {
		Quaternion quaternion;
		double sqrt;
		double half;
		double scale = matrix.M11 + matrix.M22 + matrix.M33;

		if (scale > 0.0f)
		{
			sqrt = MathHelper::Sqrt(scale + 1.0f);
			quaternion.W = sqrt * 0.5f;
			sqrt = 0.5f / sqrt;

			quaternion.X = (matrix.M23 - matrix.M32) * sqrt;
			quaternion.Y = (matrix.M31 - matrix.M13) * sqrt;
			quaternion.Z = (matrix.M12 - matrix.M21) * sqrt;

			return quaternion;
		}
		if ((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33))
		{
			sqrt = MathHelper::Sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
			half = 0.5f / sqrt;

			quaternion.X = 0.5f * sqrt;
			quaternion.Y = (matrix.M12 + matrix.M21) * half;
			quaternion.Z = (matrix.M13 + matrix.M31) * half;
			quaternion.W = (matrix.M23 - matrix.M32) * half;

			return quaternion;
		}
		if (matrix.M22 > matrix.M33)
		{
			sqrt = MathHelper::Sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
			half = 0.5f / sqrt;

			quaternion.X = (matrix.M21 + matrix.M12) * half;
			quaternion.Y = 0.5f * sqrt;
			quaternion.Z = (matrix.M32 + matrix.M23) * half;
			quaternion.W = (matrix.M31 - matrix.M13) * half;

			return quaternion;
		}
		sqrt = MathHelper::Sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
		half = 0.5f / sqrt;

		quaternion.X = (matrix.M31 + matrix.M13) * half;
		quaternion.Y = (matrix.M32 + matrix.M23) * half;
		quaternion.Z = 0.5f * sqrt;
		quaternion.W = (matrix.M12 - matrix.M21) * half;

		return quaternion;
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(double yaw, double pitch, double roll) {
		double halfRoll = roll * 0.5f;
		double halfPitch = pitch * 0.5f;
		double halfYaw = yaw * 0.5f;

		double sinRoll = MathHelper::Sin(halfRoll);
		double cosRoll = MathHelper::Cos(halfRoll);
		double sinPitch = MathHelper::Sin(halfPitch);
		double cosPitch = MathHelper::Cos(halfPitch);
		double sinYaw = MathHelper::Sin(halfYaw);
		double cosYaw = MathHelper::Cos(halfYaw);

		return Quaternion((cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
			(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
			(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
			(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll));
	}

	Quaternion Quaternion::Divide(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		Quaternion quaternion;
		double x = quaternion1.X;
		double y = quaternion1.Y;
		double z = quaternion1.Z;
		double w = quaternion1.W;
		double num14 = (((quaternion2.X * quaternion2.X) + (quaternion2.Y * quaternion2.Y)) + (quaternion2.Z * quaternion2.Z)) + (quaternion2.W * quaternion2.W);
		double num5 = 1.0 / num14;
		double num4 = -quaternion2.X * num5;
		double num3 = -quaternion2.Y * num5;
		double num2 = -quaternion2.Z * num5;
		double num = quaternion2.W * num5;
		double num13 = (y * num2) - (z * num3);
		double num12 = (z * num4) - (x * num2);
		double num11 = (x * num3) - (y * num4);
		double num10 = ((x * num4) + (y * num3)) + (z * num2);
		quaternion.X = ((x * num) + (num4 * w)) + num13;
		quaternion.Y = ((y * num) + (num3 * w)) + num12;
		quaternion.Z = ((z * num) + (num2 * w)) + num11;
		quaternion.W = (w * num) - num10;
		return quaternion;
	}

	double Quaternion::Dot(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return ((((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W));
	}

	Quaternion Quaternion::Inverse(Quaternion const& quaternion) {
		Quaternion quaternion2;
		double num2 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
		double num = 1.0 / num2;
		quaternion2.X = -quaternion.X * num;
		quaternion2.Y = -quaternion.Y * num;
		quaternion2.Z = -quaternion.Z * num;
		quaternion2.W = quaternion.W * num;
		return quaternion2;
	}

	Quaternion Quaternion::Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount) {
		double num = amount;
		double num2 = 1.0 - num;
		Quaternion quaternion;
		double num5 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
		if (num5 >= 0.0)
		{
			quaternion.X = (num2 * quaternion1.X) + (num * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y) + (num * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z) + (num * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W) + (num * quaternion2.W);
		}
		else
		{
			quaternion.X = (num2 * quaternion1.X) - (num * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y) - (num * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z) - (num * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W) - (num * quaternion2.W);
		}
		double num4 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
		double num3 = 1.0 / MathHelper::Sqrt(num4);
		quaternion.X *= num3;
		quaternion.Y *= num3;
		quaternion.Z *= num3;
		quaternion.W *= num3;
		return quaternion;
	}

	Quaternion Quaternion::Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount) {
		double num2;
		double num3;
		Quaternion quaternion;
		double num = amount;
		double num4 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
		bool flag = false;
		if (num4 < 0.0)
		{
			flag = true;
			num4 = -num4;
		}
		if (num4 > 0.999999f)
		{
			num3 = 1.0 - num;
			num2 = flag ? -num : num;
		}
		else
		{
			double num5 = MathHelper::Acos(num4);
			double num6 = (double)(1.0 / MathHelper::Sin(num5));
			num3 = MathHelper::Sin((1.0 - num) * num5) * num6;
			num2 = flag ? (-MathHelper::Sin(num * num5) * num6) : (MathHelper::Sin(num * num5) * num6);
		}
		quaternion.X = (num3 * quaternion1.X) + (num2 * quaternion2.X);
		quaternion.Y = (num3 * quaternion1.Y) + (num2 * quaternion2.Y);
		quaternion.Z = (num3 * quaternion1.Z) + (num2 * quaternion2.Z);
		quaternion.W = (num3 * quaternion1.W) + (num2 * quaternion2.W);
		return quaternion;
	}

	Quaternion Quaternion::Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		Quaternion quaternion;
		quaternion.X = quaternion1.X - quaternion2.X;
		quaternion.Y = quaternion1.Y - quaternion2.Y;
		quaternion.Z = quaternion1.Z - quaternion2.Z;
		quaternion.W = quaternion1.W - quaternion2.W;
		return quaternion;
	}

	Quaternion Quaternion::Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		Quaternion quaternion;
		double x = quaternion1.X;
		double y = quaternion1.Y;
		double z = quaternion1.Z;
		double w = quaternion1.W;
		double num4 = quaternion2.X;
		double num3 = quaternion2.Y;
		double num2 = quaternion2.Z;
		double num = quaternion2.W;
		double num12 = (y * num2) - (z * num3);
		double num11 = (z * num4) - (x * num2);
		double num10 = (x * num3) - (y * num4);
		double num9 = ((x * num4) + (y * num3)) + (z * num2);
		quaternion.X = ((x * num) + (num4 * w)) + num12;
		quaternion.Y = ((y * num) + (num3 * w)) + num11;
		quaternion.Z = ((z * num) + (num2 * w)) + num10;
		quaternion.W = (w * num) - num9;
		return quaternion;
	}

	Quaternion Quaternion::Multiply(Quaternion const& quaternion1, double scaleFactor) {
		Quaternion quaternion;
		quaternion.X = quaternion1.X * scaleFactor;
		quaternion.Y = quaternion1.Y * scaleFactor;
		quaternion.Z = quaternion1.Z * scaleFactor;
		quaternion.W = quaternion1.W * scaleFactor;
		return quaternion;
	}

	Quaternion Quaternion::Negate(Quaternion const& quaternion) {
		return Quaternion(-quaternion.X, -quaternion.Y, -quaternion.Z, -quaternion.W);
	}

	Quaternion Quaternion::Normalize(Quaternion const& quaternion) {
		Quaternion result;
		double num = 1.0 / MathHelper::Sqrt((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W));
		result.X = quaternion.X * num;
		result.Y = quaternion.Y * num;
		result.Z = quaternion.Z * num;
		result.W = quaternion.W * num;
		return result;
	}

	void Quaternion::Conjugate() {
		Quaternion value = Quaternion::Conjugate(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	double Quaternion::Length() const {
		return MathHelper::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
	}

	double Quaternion::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	void Quaternion::Normalize() {
		Quaternion value = Normalize(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	Vector4 Quaternion::ToVector4() const {
		return Vector4(X, Y, Z, W);
	}

	bool Quaternion::Equals(Quaternion const& other) const {
		return 
			X == other.X &&
			Y == other.Y &&
			Z == other.Z &&
			W == other.W;
	}
}