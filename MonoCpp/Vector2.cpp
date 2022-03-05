#include <cmath>
#include "Vector2.h"
#include "Point.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "MathHelper.h"

namespace Xna {
	Vector2::Vector2(double x, double y) : X(x), Y(y) {}
	Vector2::Vector2(double value) : X(value), Y(value) {}

	//Operators

	Vector2 Vector2::operator- () {
		return Vector2(-X, -Y);
	}

	Vector2 operator+ (Vector2 value1, Vector2 value2) {
		return Vector2(value1.X + value2.X, value1.Y + value2.Y);
	}

	Vector2 operator- (Vector2 value1, Vector2 value2) {
		return Vector2(value1.X - value2.X, value1.Y - value2.Y);
	}

	Vector2 operator* (Vector2 value1, Vector2 value2) {
		return Vector2(value1.X * value2.X, value1.Y * value2.Y);
	}

	Vector2 operator* (Vector2 value, long scaleFactor) {
		return Vector2(value.X * scaleFactor, value.Y * scaleFactor);
	}

	Vector2 operator* (long scaleFactor, Vector2 value) {
		return value * scaleFactor;
	}

	Vector2 operator/ (Vector2 source, Vector2 divisor) {
		return Vector2(source.X / divisor.X, source.Y / divisor.Y);
	}

	Vector2 operator/ (Vector2 value, long const& divider) {
		double factor = 1.0 / divider;
		value.X *= factor;
		value.Y *= factor;
		return value;
	}

	Vector2 operator== (Vector2 a, Vector2 b) {
		//return a.Equals(b);
		return false;
	}

	Vector2 operator!= (Vector2 a, Vector2 b) {
		//return !a.Equals(b);
		return false;
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

	Vector2 Vector2::Add(Vector2 value1, Vector2 const& value2) {
		value1.X += value2.X;
		value1.Y += value2.Y;
		return value2;
	}

	Vector2 Vector2::Barycentric(Vector2 value1, Vector2 value2, Vector2 value3, double amount1, double amount2) {
		return Vector2(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2));			
	}

	Vector2 Vector2::CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, double amount) {
		return Vector2(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
	}	

	Vector2 Vector2::Ceiling(Vector2 value) {
		value.X = ceil(value.X);
		value.Y = ceil(value.Y);

		return value;
	}

	Vector2 Vector2::Clamp(Vector2 value1, Vector2 min, Vector2 max) {
		return Vector2(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y));
	}

	Vector2 Vector2::Distance(Vector2 value1, Vector2 value2) {
		double v1 = value1.X - value2.X;
		double v2 = value1.Y - value2.Y;
		return sqrt((v1 * v1) + (v2 * v2));
	}

	Vector2 Vector2::DistanceSquared(Vector2 value1, Vector2 value2) {
		double v1 = value1.X - value2.X;
		double v2 = value1.Y - value2.Y;
		return (v1 * v1) + (v2 * v2);
	}

	Vector2 Vector2::Divide(Vector2 value1, Vector2 value2) {
		value1.X /= value2.X;
		value1.Y /= value2.Y;
		return value1;
	}

	Vector2 Vector2::Divide(Vector2 value1, double divider) {
		double factor = 1 / divider;
		value1.X *= factor;
		value1.Y *= factor;
		return value1;
	}

	double Vector2::Dot(Vector2 value1, Vector2 value2) {
		return (value1.X * value2.X) + (value1.Y * value2.Y);
	}

	Vector2 Vector2::Floor(Vector2 value) {
		value.X = floor(value.X);
		value.Y = floor(value.Y);
		return value;
	}

	Vector2 Vector2::Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, double amount) {
		return Vector2(MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount));
	}

	Vector2 Vector2::Lerp(Vector2 value1, Vector2 value2, double amount) {
		return Vector2(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::LerpPrecise(Vector2 value1, Vector2 value2, double amount)
	{
		return Vector2(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Max(Vector2 value1, Vector2 value2)
	{
		return Vector2(
			value1.X > value2.X ? value1.X : value2.X,
			value1.Y > value2.Y ? value1.Y : value2.Y);
	}

	Vector2 Vector2::Min(Vector2 value1, Vector2 value2)
	{
		return Vector2(
			value1.X < value2.X ? value1.X : value2.X,
			value1.Y < value2.Y ? value1.Y : value2.Y);
	}

	Vector2 Vector2::Multiply(Vector2 value1, Vector2 value2)
	{
		value1.X *= value2.X;
		value1.Y *= value2.Y;
		return value1;
	}

	Vector2 Vector2::Multiply(Vector2 value1, double scaleFactor)
	{
		value1.X *= scaleFactor;
		value1.Y *= scaleFactor;
		return value1;
	}

	Vector2 Vector2::Negate(Vector2 value)
	{
		value.X = -value.X;
		value.Y = -value.Y;
		return value;
	}

	Vector2 Vector2::Normalize(Vector2 value)
	{
		double val = 1.0 / sqrt((value.X * value.X) + (value.Y * value.Y));
		value.X *= val;
		value.Y *= val;
		return value;
	}

	Vector2 Vector2::Reflect(Vector2 vector, Vector2 normal)
	{
		Vector2 result(0);
		double val = 2.0f * ((vector.X * normal.X) + (vector.Y * normal.Y));
		result.X = vector.X - (normal.X * val);
		result.Y = vector.Y - (normal.Y * val);
		return result;
	}

	Vector2 Vector2::Round(Vector2 value)
	{
		value.X = round(value.X);
		value.Y = round(value.Y);
		return value;
	}

	Vector2 Vector2::SmoothStep(Vector2 value1, Vector2 value2, double amount)
	{
		return Vector2(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Subtract(Vector2 value1, Vector2 value2)
	{
		value1.X -= value2.X;
		value1.Y -= value2.Y;
		return value1;
	}

	//Members	

	void Vector2::Ceiling() {
		X = ceil(X);
		Y = ceil(Y);
	}

	void Vector2::Floor() {
		X = floor(X);
		Y = floor(Y);
	}

	double Vector2::Length() {
		return sqrt((X * X) + (Y * Y));
	}

	double Vector2::LengthSquared() {
		return (X * X) + (Y * Y);
	}

	void Vector2::Normalize()
	{
		double val = 1.0f / sqrt((X * X) + (Y * Y));
		X *= val;
		Y *= val;
	}

	void Vector2::Round()
	{
		X = round(X);
		Y = round(Y);
	}

	Point Vector2::ToPoint()
	{
		return Point(static_cast<long>(X), static_cast<long>(X));
	}

	bool Vector2::Equals(Vector2 const& other) {
		return (X == other.X) && (Y == other.Y);
	}

	void Vector2::Deconstruct(double& x, double& y)
	{
		x = X;
		y = Y;
	}
}