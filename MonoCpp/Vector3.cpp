#include "Vector3.h"

namespace Xna {
	Vector3::Vector3(): X(0), Y(0), Z(0) {}
	Vector3::Vector3(double x, double y, double z): X(x), Y(y), Z(z) {}
	Vector3::Vector3(double value): X(value), Y(value), Z(value) {}

	Vector3 Vector3::operator- () const {
		return Vector3(-X, -Y, -Z);
	}

	std::ostream& operator<< (std::ostream& os, Vector3 const& vec) {
		return os << "{X:" << vec.X << " Y:" << vec.Y << " Z:" << vec.Z << "}";
	}
}
