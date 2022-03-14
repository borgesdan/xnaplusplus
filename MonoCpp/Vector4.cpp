#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Matrix.h"
#include "MathHelper.h"

namespace Xna {

	Vector4::Vector4() :
		X(0), Y(0), Z(0), W(0) {}
	Vector4::Vector4(double x, double y, double z, double w) :
		X(x), Y(y), Z(z), W(w) {}
	Vector4::Vector4(Vector2 value, double z, double w) :
		X(value.X), Y(value.Y), Z(z), W(w) {}
	Vector4::Vector4(Vector3 value, double w) :
		X(value.X), Y(value.Y), Z(value.Z), W(w) {}
	Vector4::Vector4(double value) :
		X(value), Y(value), Z(value), W(value) {}

	//-----Operators
	Vector4 Vector4::operator- () const {
		return Vector4::Negate((*this));
	}

	Vector4 operator- (Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Subtract(value1, value2);
	}

	Vector4 operator+ (Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Add(value1, value2);
	}

	Vector4 operator* (Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Multiply(value1, value2);
	}

	Vector4 operator* (Vector4 const& value1, double scaleFactor) {
		return Vector4::Multiply(value1, scaleFactor);
	}

	Vector4 operator/ (Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Divide(value1, value2);
	}

	Vector4 operator/ (Vector4 const& value1, long divider) {
		return Vector4::Divide(value1, divider);
	}

	bool operator== (Vector4 const& value1, Vector4 const& value2) {
		return value1.Equals(value2);
	}

	bool operator!= (Vector4 const& value1, Vector4 const& value2) {
		return !value1.Equals(value2);
	}

	//-----Static
	Vector4 Vector4::Zero() { return Vector4(0); };
	Vector4 Vector4::One() { return Vector4(1.); };
	Vector4 Vector4::UnitX() { return Vector4(1., 0, 0, 0); };
	Vector4 Vector4::UnitY() { return Vector4(0, 1., 0, 0); };
	Vector4 Vector4::UnitZ() { return Vector4(0, 0, 1., 0); };
	Vector4 Vector4::UnitW() { return Vector4(0, 0, 0, 1.); };

	Vector4 Vector4::Add(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X + value2.X,
			value1.Y + value2.Y,
			value1.Z + value2.Z,
			value1.W + value2.W);
	}

	Vector4 Vector4::Subtract(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X - value2.X,
			value1.Y - value2.Y,
			value1.Z - value2.Z,
			value1.W - value2.W);
	}

	Vector4 Vector4::Multiply(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X * value2.X,
			value1.Y * value2.Y,
			value1.Z * value2.Z,
			value1.W * value2.W);
	}

	Vector4 Vector4::Multiply(Vector4 const& value1, double scaleFactor) {
		return Vector4(
			value1.X * scaleFactor,
			value1.Y * scaleFactor,
			value1.Z * scaleFactor,
			value1.W * scaleFactor);
	}

	Vector4 Vector4::Divide(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X / value2.X,
			value1.Y / value2.Y,
			value1.Z / value2.Z,
			value1.W / value2.W);
	}

	Vector4 Vector4::Divide(Vector4 const& value1, double divider) {
		double factor = 1. / divider;
		return Vector4(
			value1.X * factor,
			value1.Y * factor,
			value1.Z * factor,
			value1.W * factor);
	}

	Vector4 Vector4::Barycentric(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, double amount1, double amount2) {
		return Vector4(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
			MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2),
			MathHelper::Barycentric(value1.W, value2.W, value3.W, amount1, amount2));
	}

	Vector4 Vector4::CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, Vector4 const& value4, double amount) {
		return Vector4(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
			MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount),
			MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount));
	}

	Vector4 Vector4::Ceiling(Vector4 const& value) {
		return Vector4(
			MathHelper::Ceiling(value.X),
			MathHelper::Ceiling(value.Y),
			MathHelper::Ceiling(value.Z),
			MathHelper::Ceiling(value.W));
	}

	Vector4 Vector4::Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max) {
		return Vector4(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y),
			MathHelper::Clamp(value1.Z, min.Z, max.Z),
			MathHelper::Clamp(value1.W, min.W, max.W));
	}

	double Vector4::Distance(Vector4 const& value1, Vector4 const& value2) {
		return MathHelper::Sqrt(DistanceSquared(value1, value2));
	}

	double Vector4::DistanceSquared(Vector4 const& value1, Vector4 const& value2) {
		return
			(value1.W - value2.W) * (value1.W - value2.W) +
			(value1.X - value2.X) * (value1.X - value2.X) +
			(value1.Y - value2.Y) * (value1.Y - value2.Y) +
			(value1.Z - value2.Z) * (value1.Z - value2.Z);
	}

	double Vector4::Dot(Vector4 const& value1, Vector4 const& value2) {
		return
			value1.X * value2.X +
			value1.Y * value2.Y +
			value1.Z * value2.Z +
			value1.W * value2.W;
	}

	Vector4 Vector4::Floor(Vector4 const& value) {
		return Vector4(
			MathHelper::Floor(value.X),
			MathHelper::Floor(value.Y),
			MathHelper::Floor(value.Z),
			MathHelper::Floor(value.W));
	}

	Vector4 Vector4::Hermite(Vector4 const& value1, Vector4 const& tangent1, Vector4 const& value2, Vector4 const& tangent2, double amount) {
		return Vector4(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
			MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount),
			MathHelper::Hermite(value1.W, tangent1.W, value2.W, tangent2.W, amount));
	}

	Vector4 Vector4::Lerp(Vector4 const& value1, Vector4 const& value2, double amount) {
		return Vector4(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount),
			MathHelper::Lerp(value1.Z, value2.Z, amount),
			MathHelper::Lerp(value1.W, value2.W, amount));
	}

	Vector4 Vector4::LerpPrecise(Vector4 const& value1, Vector4 const& value2, double amount) {
		return Vector4(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
			MathHelper::LerpPrecise(value1.Z, value2.Z, amount),
			MathHelper::LerpPrecise(value1.W, value2.W, amount));
	}

	Vector4 Vector4::Max(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			MathHelper::Max(value1.X, value2.X),
			MathHelper::Max(value1.Y, value2.Y),
			MathHelper::Max(value1.Z, value2.Z),
			MathHelper::Max(value1.W, value2.W));
	}

	Vector4 Vector4::Min(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			MathHelper::Min(value1.X, value2.X),
			MathHelper::Min(value1.Y, value2.Y),
			MathHelper::Min(value1.Z, value2.Z),
			MathHelper::Min(value1.W, value2.W));
	}

	Vector4 Vector4::Negate(Vector4 const& value) {
		return Vector4(-value.X, -value.Y, -value.Z, -value.W);
	}

	Vector4 Vector4::Normalize(Vector4 const& value) {
		double factor = MathHelper::Sqrt((value.X * value.X)
			+ (value.Y * value.Y)
			+ (value.Z * value.Z)
			+ (value.W * value.W));

		factor = 1. / factor;

		return Vector4(
			value.X * factor,
			value.Y * factor,
			value.Z * factor,
			value.W * factor);
	}

	Vector4 Vector4::Round(Vector4 const& value) {
		return Vector4(
			MathHelper::Round(value.X),
			MathHelper::Round(value.Y),
			MathHelper::Round(value.Z),
			MathHelper::Round(value.W));
	}

	Vector4 Vector4::SmoothStep(Vector4 const& value1, Vector4 value2, double amount) {
		return Vector4(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount),
			MathHelper::SmoothStep(value1.W, value2.W, amount));
	}

	Vector4 Vector4::Transform(Vector2 const& value, Matrix const& matrix) {
		return Vector4(
			(value.X * matrix.M11) + (value.Y * matrix.M21) + matrix.M41,
			(value.X * matrix.M12) + (value.Y * matrix.M22) + matrix.M42,
			(value.X * matrix.M13) + (value.Y * matrix.M23) + matrix.M43,
			(value.X * matrix.M14) + (value.Y * matrix.M24) + matrix.M44);
	}

	Vector4 Vector4::Transform(Vector3 const& value, Matrix const& matrix) {
		return Vector4(
			(value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + matrix.M41,
			(value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + matrix.M42,
			(value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + matrix.M43,
			(value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + matrix.M44);
	}

	Vector4 Vector4::Transform(Vector4 const& value, Matrix const& matrix) {
		return Vector4(
			(value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + (value.W * matrix.M41),
			(value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + (value.W * matrix.M42),
			(value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + (value.W * matrix.M43),
			(value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + (value.W * matrix.M44));

	}

	void Vector4::Transform(std::vector<Vector4> const& sourceArray, int sourceIndex,
		Matrix& matrix, std::vector<Vector4>& destinationArray, int destinationIndex, int length) {

		for (int i = 0; i < length; i++)
		{
			//Vector4 value = sourceArray[sourceIndex + i];
			//destinationArray[destinationIndex + i] = Transform(value, matrix);
			Vector4 value = sourceArray[static_cast<std::vector<Xna::Vector4, std::allocator<Xna::Vector4>>::size_type>(sourceIndex) + i];
			destinationArray[static_cast<std::vector<Xna::Vector4, std::allocator<Xna::Vector4>>::size_type>(destinationIndex) + i] = Transform(value, matrix);
		}

	}

	void Vector4::Transform(std::vector<Vector4> const& sourceArray, Matrix& matrix, std::vector<Vector4>& destinationArray) {

		for (int i = 0; i < sourceArray.size(); i++)
		{
			Vector4 value = sourceArray[i];
			destinationArray[i] = Transform(value, matrix);
		}
	}

	//-----Members
	void Vector4::Ceiling() {
		Vector4 value = Vector4::Ceiling(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	void Vector4::Floor() {
		Vector4 value = Vector4::Floor(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	double Vector4::Length() const {
		return MathHelper::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
	}

	double Vector4::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	void Vector4::Normalize() {
		Vector4 normal = Vector4::Normalize((*this));
		X = normal.X;
		Y = normal.Y;
		Z = normal.Z;
		W = normal.W;
	}

	void Vector4::Round() {
		Vector4 round = Vector4::Round((*this));
		X = round.X;
		Y = round.Y;
		Z = round.Z;
		W = round.W;
	}

	void Vector4::Deconstruct(double& x, double& y, double& z, double& w) const {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	bool Vector4::Equals(Vector4 const& other) const {
		return W == other.W
			&& X == other.X
			&& Y == other.Y
			&& Z == other.Z;
	}
}