#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"
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

	std::ostream& operator<< (std::ostream& os, Vector3 const& vec) {
		return os << "{X:" << vec.X << " Y:" << vec.Y << " Z:" << vec.Z << "}";
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

	//----- Members
}
