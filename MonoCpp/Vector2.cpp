#include <cmath>
#include "Vector2.h"
#include "Point.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "MathHelper.h"
#include "Vector3.h"

namespace Xna {
	Vector2::Vector2() : X(0), Y(0) {}
	Vector2::Vector2(double x, double y) : X(x), Y(y) {}
	Vector2::Vector2(double value) : X(value), Y(value) {}

	//Operators

	Vector2 Vector2::operator- () {
		return Vector2::Negate(*this);
	}

	Vector2 operator+ (Vector2 value1, Vector2 value2) {
		return Vector2::Add(value1, value2);
	}

	Vector2 operator- (Vector2 value1, Vector2 value2) {
		return Vector2::Subtract(value1, value2);
	}

	Vector2 operator* (Vector2 value1, Vector2 value2) {
		return Vector2::Multiply(value1, value2);
	}

	Vector2 operator* (Vector2 value, double scaleFactor) {
		return Vector2::Multiply(value, scaleFactor);
	}

	Vector2 operator* (double scaleFactor, Vector2 value) {
		return Vector2::Multiply(value, scaleFactor);
	}

	Vector2 operator/ (Vector2 value, Vector2 divider) {
		return Vector2::Divide(value, divider);
	}

	Vector2 operator/ (Vector2 value, double divider) {
		return Vector2::Divide(value, divider);
	}

	Vector2 operator== (Vector2 a, Vector2 b) {
		return a.Equals(b);
	}

	Vector2 operator!= (Vector2 a, Vector2 b) {
		return !a.Equals(b);
	}

	//Static

	Vector2 Vector2::Zero() {
		return Vector2(0);
	}

	Vector2 Vector2::One() {
		return Vector2(1.0, 1.0);
	}

	Vector2 Vector2::UnitX() {
		return Vector2(1.0, 0.0);
	}

	Vector2 Vector2::UnitY() {
		return Vector2(0, 1.0);
	}

	Vector2 Vector2::Add(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X + value2.X,
			value1.Y + value2.Y);
	}

	Vector2 Vector2::Subtract(Vector2 const& value1, Vector2 const& value2)
	{
		return Vector2(
			value1.X - value2.X,
			value1.Y - value2.Y);
	}

	Vector2 Vector2::Multiply(Vector2 const& value1, Vector2 const& value2)
	{
		return Vector2(
			value1.X * value2.X,
			value1.Y * value2.Y);
	}

	Vector2 Vector2::Multiply(Vector2 const& value1, double scaleFactor)
	{
		return Vector2(
			value1.X * scaleFactor,
			value1.Y * scaleFactor);
	}

	Vector2 Vector2::Divide(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X / value2.X,
			value1.Y / value2.Y);
	}

	Vector2 Vector2::Divide(Vector2 const& value1, double divider) {
		double factor = 1. / divider;
		return Vector2(
			value1.X * factor,
			value1.Y * factor);
	}

	Vector2 Vector2::Barycentric(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3, double amount1, double amount2) {
		return Vector2(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2));
	}

	Vector2 Vector2::CatmullRom(Vector2 const& value1, Vector2 const& value2, Vector2 const& value3, Vector2 const& value4, double amount) {
		return Vector2(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
	}

	Vector2 Vector2::Ceiling(Vector2 const& value) {
		return Vector2(
			MathHelper::Ceiling(value.X),
			MathHelper::Ceiling(value.Y));
	}

	Vector2 Vector2::Clamp(Vector2 const& value1, Vector2 const& min, Vector2 const& max) {
		return Vector2(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y));
	}

	double Vector2::Distance(Vector2 const& value1, Vector2 const& value2) {
		return MathHelper::Sqrt(DistanceSquared(value1, value2));
	}

	double Vector2::DistanceSquared(Vector2 const& value1, Vector2 const& value2) {
		return
			(value1.X - value2.X) * (value1.X - value2.X) +
			(value1.Y - value2.Y) * (value1.Y - value2.Y);
	}

	double Vector2::Dot(Vector2 const& value1, Vector2 const& value2) {
		return (value1.X * value2.X) + (value1.Y * value2.Y);
	}

	Vector2 Vector2::Floor(Vector2 const& value) {
		return Vector2(
			MathHelper::Floor(value.X),
			MathHelper::Floor(value.Y));
	}

	Vector2 Vector2::Hermite(Vector2 const& value1, Vector2 const& tangent1, Vector2 const& value2, Vector2 const& tangent2, double amount) {
		return Vector2(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount));
	}

	Vector2 Vector2::Lerp(Vector2 const& value1, Vector2 const& value2, double amount) {
		return Vector2(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::LerpPrecise(Vector2 const& value1, Vector2  const& value2, double amount)
	{
		return Vector2(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Max(Vector2 const& value1, Vector2 const& value2)
	{
		return Vector2(
			MathHelper::Max(value1.X, value2.X),
			MathHelper::Max(value1.Y, value2.Y));
	}

	Vector2 Vector2::Min(Vector2 const& value1, Vector2 const& value2)
	{
		return Vector2(
			MathHelper::Min(value1.X, value2.X),
			MathHelper::Min(value1.Y, value2.Y));
	}

	Vector2 Vector2::Negate(Vector2 const& value)
	{
		return Vector2(-value.X, -value.Y);
	}

	Vector2 Vector2::Normalize(Vector2 const& value)
	{
		double factor = MathHelper::Sqrt((value.X * value.X)
			+ (value.Y * value.Y));

		factor = 1. / factor;

		return Vector2(
			value.X * factor,
			value.Y * factor);

	}

	Vector2 Vector2::Reflect(Vector2 const& vector, Vector2 const& normal)
	{
		double dotProduct = Vector2::Dot(vector, normal);

		return Vector2(
			vector.X - (2.0f * normal.X) * dotProduct,
			vector.Y - (2.0f * normal.Y) * dotProduct);
	}

	Vector2 Vector2::Round(Vector2 const& value)
	{
		return Vector2(
			MathHelper::Round(value.X),
			MathHelper::Round(value.Y));
	}

	Vector2 Vector2::SmoothStep(Vector2 const& value1, Vector2 const& value2, double amount)
	{
		return Vector2(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Transform(Vector2 const& position, Matrix const& matrix) {
		return Vector2(
			(position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41,
			(position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42);
	}

	Vector2 Vector2::Transform(Vector2 const& value, Quaternion const& rotation) {

		Vector3 rot1 = Vector3(rotation.X + rotation.X, rotation.Y + rotation.Y, rotation.Z + rotation.Z);
		Vector3 rot2 = Vector3(rotation.X, rotation.X, rotation.W);
		Vector3 rot3 = Vector3(1, rotation.Y, rotation.Z);
		Vector3 rot4 = rot1 * rot2;
		Vector3 rot5 = rot1 * rot3;

		Vector2 v;
		v.X = (float)((double)value.X * (1.0 - (double)rot5.Y - (double)rot5.Z) + (double)value.Y * ((double)rot4.Y - (double)rot4.Z));
		v.Y = (float)((double)value.X * ((double)rot4.Y + (double)rot4.Z) + (double)value.Y * (1.0 - (double)rot4.X - (double)rot5.Z));

		return v;
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length) {
		for (i32 x = 0; x < length; x++)
		{
			Vector2 position = sourceArray[static_cast<std::vector<Xna::Vector2, std::allocator<Xna::Vector2>>::size_type>(sourceIndex) + x];
			Vector2 destination = destinationArray[static_cast<std::vector<Xna::Vector2, std::allocator<Xna::Vector2>>::size_type>(destinationIndex) + x];
			destination.X = (position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41;
			destination.Y = (position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42;
			destinationArray[static_cast<std::vector<Xna::Vector2, std::allocator<Xna::Vector2>>::size_type>(destinationIndex) + x] = destination;
		}
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Quaternion const& rotation, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length) {
		for (size_t x = 0; x < length; x++)
		{
			Vector2 position = sourceArray[sourceIndex + x];
			Vector2 destination = destinationArray[destinationIndex + x];

			Vector2 v = Vector2::Transform(position, rotation);

			destination.X = v.X;
			destination.Y = v.Y;

			destinationArray[destinationIndex + x] = destination;
		}
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray) {
		Vector2::Transform(sourceArray, 0, matrix, destinationArray, 0, sourceArray.size());
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, Quaternion const& rotation, std::vector<Vector2> destinationArray) {
		Vector2::Transform(sourceArray, 0, rotation, destinationArray, 0, sourceArray.size());
	}

	Vector2 Vector2::TransformNormal(Vector2 const& normal, Matrix const& matrix) {
		return Vector2((normal.X * matrix.M11) + (normal.Y * matrix.M21),
			(normal.X * matrix.M12) + (normal.Y * matrix.M22));
	}

	void Vector2::TransformNormal(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix, std::vector<Vector2> destinationArray, size_t destinationIndex, size_t length) {
		for (size_t i = 0; i < length; i++)
		{
			Vector2 normal = sourceArray[sourceIndex + i];

			destinationArray[destinationIndex + i]
				= Vector2((normal.X * matrix.M11) + (normal.Y * matrix.M21),
					(normal.X * matrix.M12) + (normal.Y * matrix.M22));
		}
	}

	void Vector2::TransformNormal(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2> destinationArray) {
		for (i32 i = 0; i < sourceArray.size(); i++)
		{
			Vector2 normal = sourceArray[i];

			destinationArray[i] = Vector2((normal.X * matrix.M11) + (normal.Y * matrix.M21),
				(normal.X * matrix.M12) + (normal.Y * matrix.M22));
		}
	}

	//Members	

	void Vector2::Ceiling() {
		Vector2 value = Vector2::Ceiling(*this);
		X = value.X;
		Y = value.Y;
	}

	void Vector2::Floor() {
		Vector2 value = Vector2::Floor(*this);
		X = value.X;
		Y = value.Y;
	}

	double Vector2::Length() const {
		return MathHelper::Sqrt((X * X) + (Y * Y));
	}

	double Vector2::LengthSquared() const {
		return (X * X) + (Y * Y);
	}

	void Vector2::Normalize() {
		Vector2 value = Vector2::Normalize(*this);
		X = value.X;
		Y = value.Y;
	}

	void Vector2::Round() {
		Vector2 value = Vector2::Round(*this);
		X = value.X;
		Y = value.Y;
	}

	Point Vector2::ToPoint() const {
		return Point(static_cast<long>(X), static_cast<long>(X));
	}

	bool Vector2::Equals(Vector2 const& other) const {
		return (X == other.X) && (Y == other.Y);
	}

	void Vector2::Deconstruct(double& x, double& y) const
	{
		x = X;
		y = Y;
	}
}