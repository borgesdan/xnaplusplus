#include "Structs.h"
#include "MathHelper.h"

namespace Xna {
	Vector3::Vector3() :
		X(0), Y(0), Z(0) {}

	Vector3::Vector3(double x, double y, double z) :
		X(x), Y(y), Z(z) {}

	Vector3::Vector3(double value) :
		X(value), Y(value), Z(value) {}

	Vector3::Vector3(Vector2 value, double z) :
		X(value.X), Y(value.Y), Z(z) {}

	Vector3 Vector3::operator- () const {
		return Vector3(-X, -Y, -Z);
	}

	//----- Operators	

	Vector3 operator- (Vector3 value1, Vector3 value2) {
		return Vector3::Subtract(value1, value2);
	}

	Vector3 operator+ (Vector3 value1, Vector3 value2) {
		return Vector3::Add(value1, value2);
	}

	Vector3 operator* (Vector3 value1, Vector3 value2) {
		return Vector3::Multiply(value1, value2);
	}

	Vector3 operator* (double scaleFactor, Vector3 value) {
		return Vector3::Subtract(value, scaleFactor);
	}

	Vector3 operator* (Vector3 value, double scaleFactor) {
		return Vector3::Subtract(value, scaleFactor);
	}

	Vector3 operator/ (Vector3 value1, Vector3 value2) {
		return Vector3::Divide(value1, value2);
	}

	Vector3 operator/ (Vector3 value, double divider) {
		return Vector3::Divide(value, divider);
	}

	bool operator== (Vector3 value1, Vector3 value2) {
		return value1.Equals(value2);
	}

	bool operator!= (Vector3 value1, Vector3 value2) {
		return !value1.Equals(value2);
	}

	//----- Static
	Vector3 Vector3::Zero() { return Vector3(0); }
	Vector3 Vector3::One() { return Vector3(1.); }
	Vector3 Vector3::UnitX() { return Vector3(1., 0); }
	Vector3 Vector3::UnitY() { return Vector3(0, 1.); }
	Vector3 Vector3::UnitZ() { return Vector3(0, 0, 1.); }
	Vector3 Vector3::Up() { return Vector3(0, 1., 0); }
	Vector3 Vector3::Down() { return Vector3(0, -1., 0); }
	Vector3 Vector3::Right() { return Vector3(1., 0, 0); }
	Vector3 Vector3::Left() { return Vector3(-1., 0, 0); }
	Vector3 Vector3::Forward() { return Vector3(0, 0, -1.); }
	Vector3 Vector3::Backward() { return Vector3(0, 0, 1.); }

	Vector3 Vector3::Add(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X + value2.X,
			value1.Y + value2.Y,
			value1.Z + value2.Z);
	}

	Vector3 Vector3::Subtract(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X - value2.X,
			value1.Y - value2.Y,
			value1.Z - value2.Z);
	}

	Vector3 Vector3::Divide(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X / value2.X,
			value1.Y / value2.Y,
			value1.Z / value2.Z);
	}
	Vector3 Vector3::Divide(Vector3 const& value1, double divider) {
		double factor = 1. / divider;
		return Vector3(
			value1.X * factor,
			value1.Y * factor,
			value1.Z * factor);
	}

	Vector3 Vector3::Multiply(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X * value2.X,
			value1.Y * value2.Y,
			value1.Z * value2.Z);
	}

	Vector3 Vector3::Multiply(Vector3 const& value1, double scaleFactor) {
		return Vector3(
			value1.X * scaleFactor,
			value1.Y * scaleFactor,
			value1.Z * scaleFactor);
	}

	Vector3 Vector3::Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, double amount1, double amount2) {
		return Vector3(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
			MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2));
	}

	Vector3 Vector3::CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, Vector3 const& value4, double amount) {
		return Vector3(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
			MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount));
	}

	Vector3 Vector3::Ceiling(Vector3 const& value) {
		return Vector3(
			MathHelper::Ceiling(value.X),
			MathHelper::Ceiling(value.Y),
			MathHelper::Ceiling(value.Z));
	}

	Vector3 Vector3::Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max) {
		return Vector3(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y),
			MathHelper::Clamp(value1.Z, min.Z, max.Z));
	}

	Vector3 Vector3::Cross(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.Y * value2.Z - value2.Y * value1.Z,
			-(value1.X * value2.Z - value2.X * value1.Z),
			value1.X * value2.Y - value2.X * value1.Y);
	}

	double Vector3::Dot(Vector3 const& value1, Vector3 const& value2) {
		return
			value1.X * value2.X +
			value1.Y * value2.Y +
			value1.Z * value2.Z;
	}

	double Vector3::Distance(Vector3 const& value1, Vector3 const& value2) {
		return MathHelper::Sqrt(DistanceSquared(value1, value2));
	}

	double Vector3::DistanceSquared(Vector3 const& value1, Vector3 const& value2) {
		return
			(value1.X - value2.X) * (value1.X - value2.X) +
			(value1.Y - value2.Y) * (value1.Y - value2.Y) +
			(value1.Z - value2.Z) * (value1.Z - value2.Z);
	}

	Vector3 Vector3::Floor(Vector3 const& value) {
		return Vector3(
			MathHelper::Floor(value.X),
			MathHelper::Floor(value.Y),
			MathHelper::Floor(value.Z));
	}

	Vector3 Vector3::Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2, Vector3 const& tangent2, double amount) {
		return Vector3(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
			MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount));
	}

	Vector3 Vector3::Normalize(Vector3 const& value) {
		double factor = MathHelper::Sqrt((value.X * value.X)
			+ (value.Y * value.Y)
			+ (value.Z * value.Z));

		factor = 1. / factor;

		return Vector3(
			value.X * factor,
			value.Y * factor,
			value.Z * factor);
	}

	Vector3 Vector3::Lerp(Vector3 const& value1, Vector3 const& value2, double amount) {
		return Vector3(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount),
			MathHelper::Lerp(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::LerpPrecise(Vector3 const& value1, Vector3 const& value2, double amount) {
		return Vector3(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
			MathHelper::LerpPrecise(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::Max(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			MathHelper::Max(value1.X, value2.X),
			MathHelper::Max(value1.Y, value2.Y),
			MathHelper::Max(value1.Z, value2.Z));
	}

	Vector3 Vector3::Min(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			MathHelper::Min(value1.X, value2.X),
			MathHelper::Min(value1.Y, value2.Y),
			MathHelper::Min(value1.Z, value2.Z));
	}

	Vector3 Vector3::Negate(Vector3 const& value) {
		return Vector3(-value.X, -value.Y, -value.Z);
	}

	Vector3 Vector3::Reflect(Vector3 const& vector, Vector3 const& normal) {

		double dotProduct = Vector3::Dot(vector, normal);

		return Vector3(
			vector.X - (2.0f * normal.X) * dotProduct,
			vector.Y - (2.0f * normal.Y) * dotProduct,
			vector.Z - (2.0f * normal.Z) * dotProduct);
	}

	Vector3 Vector3::Round(Vector3 const& value) {
		return Vector3(
			MathHelper::Round(value.X),
			MathHelper::Round(value.Y),
			MathHelper::Round(value.Z));
	}

	Vector3 Vector3::SmoothStep(Vector3 const& value1, Vector3 const& value2, double amount) {
		return Vector3(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::Transform(Vector3 const& position, Matrix const& matrix) {
		return Vector3(
			(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
			(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
			(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43);
	}
	Vector3 Vector3::Transform(Vector3 const& value, Quaternion const& rotation) {
		Vector3 result;

		double x = 2. * (rotation.Y * value.Z - rotation.Z * value.Y);
		double y = 2. * (rotation.Z * value.X - rotation.X * value.Z);
		double z = 2. * (rotation.X * value.Y - rotation.Y * value.X);

		result.X = value.X + x * rotation.W + (rotation.Y * z - rotation.Z * y);
		result.Y = value.Y + y * rotation.W + (rotation.Z * x - rotation.X * z);
		result.Z = value.Z + z * rotation.W + (rotation.X * y - rotation.Y * x);

		return result;
	}

	void  Vector3::Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix& matrix, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {
		for (size_t i = 0; i < length; i++) {
			Vector3 position = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] =
				Vector3(
					(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
					(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
					(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43);
		}
	}

	void  Vector3::Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Quaternion& rotation, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {
		for (size_t i = 0; i < length; i++) {
			Vector3 position = sourceArray[sourceIndex + i];

			double x = 2 * (rotation.Y * position.Z - rotation.Z * position.Y);
			double y = 2 * (rotation.Z * position.X - rotation.X * position.Z);
			double z = 2 * (rotation.X * position.Y - rotation.Y * position.X);

			destinationArray[destinationIndex + i] =
				Vector3(
					position.X + x * rotation.W + (rotation.Y * z - rotation.Z * y),
					position.Y + y * rotation.W + (rotation.Z * x - rotation.X * z),
					position.Z + z * rotation.W + (rotation.X * y - rotation.Y * x));
		}
	}

	void  Vector3::Transform(std::vector<Vector3> const& sourceArray, Matrix& matrix, std::vector<Vector3>& destinationArray) {
		for (i32 i = 0; i < sourceArray.size(); i++) {
			Vector3 position = sourceArray[i];
			destinationArray[i] =
				Vector3(
					(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
					(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
					(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43);
		}
	}

	void  Vector3::Transform(std::vector<Vector3> const& sourceArray, Quaternion& rotation, std::vector<Vector3>& destinationArray) {
		for (i32 i = 0; i < sourceArray.size(); i++) {
			Vector3 position = sourceArray[i];

			double x = 2 * (rotation.Y * position.Z - rotation.Z * position.Y);
			double y = 2 * (rotation.Z * position.X - rotation.X * position.Z);
			double z = 2 * (rotation.X * position.Y - rotation.Y * position.X);

			destinationArray[i] =
				Vector3(
					position.X + x * rotation.W + (rotation.Y * z - rotation.Z * y),
					position.Y + y * rotation.W + (rotation.Z * x - rotation.X * z),
					position.Z + z * rotation.W + (rotation.X * y - rotation.Y * x));
		}
	}

	Vector3 Vector3::TransformNormal(Vector3 const& normal, Matrix const& matrix) {
		return Vector3(
			(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
			(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
			(normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33));

	}

	void Vector3::TransformNormal(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix& matrix, std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {
		for (size_t x = 0; x < length; x++)
		{
			Vector3 normal = sourceArray[sourceIndex + x];

			destinationArray[destinationIndex + x] =
				Vector3(
					(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
					(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
					(normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33));
		}
	}

	void  Vector3::TransformNormal(std::vector<Vector3> const& sourceArray, Matrix& matrix, std::vector<Vector3>& destinationArray) {
		for (i32 i = 0; i < sourceArray.size(); i++)
		{
			Vector3 normal = sourceArray[i];

			destinationArray[i] =
				Vector3(
					(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
					(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
					(normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33));
		}
	}

	//----- Members

	void Vector3::Round() {
		Vector3 value = Vector3::Round(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	void Vector3::Ceiling() {
		Vector3 value = Vector3::Ceiling(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}
	void Vector3::Normalize() {
		Vector3 value = Vector3::Normalize(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	double Vector3::Length() const {
		return MathHelper::Sqrt((X * X) + (Y * Y) + (Z * Z));
	}

	double Vector3::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z);
	}

	void Vector3::Floor() {
		Vector3 value = Vector3::Floor(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	void Vector3::Deconstruct(double& x, double& y, double& z) const {
		x = X;
		y = Y;
		z = Z;
	}

	bool Vector3::Equals(Vector3 const& other) const {
		return X == other.X
			&& Y == other.Y
			&& Z == other.Z;
	}
}
