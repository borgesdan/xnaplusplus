#include "Point.h"
#include "Vector2.h"

namespace Xna {
	
	Point::Point(i32 x, i32 y): X(x), Y(y) {}
	Point::Point(i32 value): X(value), Y(value) {}

	Point operator+ (Point value1, Point value2) {
		return Point(value1.X + value2.X, value1.Y + value2.Y);
	}

	Point operator- (Point value1, Point value2) {
		return Point(value1.X - value2.X, value1.Y - value2.Y);
	}

	Point operator* (Point value1, Point value2) {
		return Point(value1.X * value2.X, value1.Y * value2.Y);
	}

	Point operator/ (Point source, Point divisor) {
		return Point(source.X / divisor.X, source.Y / divisor.Y);
	}

	Point operator== (Point a, Point b) {
		return a.Equals(b);
	}

	Point operator!= (Point a, Point b) {
		return !a.Equals(b);
	}

	Point Point::Zero() {
		return Point(0);
	}	

	Vector2 Point::ToVector2() const {
		double x = static_cast<double>(X);
		double y = static_cast<double>(Y);
		return Vector2(x, y);
	}

	void Point::Deconstruct(int& x, int& y) const {
		x = X;
		y = Y;
	}

	bool Point::Equals(Point const& other) const {
		return X == other.X && Y == other.Y;
	}
}