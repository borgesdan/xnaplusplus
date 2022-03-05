#include "Rectangle.h"
#include "Point.h"
#include "Vector2.h"

namespace Xna {
	
	Rectangle::Rectangle(): X(0), Y(0), Width(0), Height(0) {}

	Rectangle::Rectangle(long x, long y, long width, long height) :
		X(x), Y(y), Width(width), Height(height) {}

	Rectangle::Rectangle(Point location, Point size) :
		X(location.X), Y(location.Y),
		Width(size.X), Height(size.Y) {}

	//operator

	bool operator== (Rectangle a, Rectangle b) {
		return a.Equals(b);
	}

	bool operator!= (Rectangle a, Rectangle b) {
		return !a.Equals(b);
	}

	//static	

	Rectangle Rectangle::Empty() { 
		return Rectangle(0, 0, 0, 0); 
	}

	Rectangle Rectangle::Intersects(Rectangle const& value1, Rectangle const& value2) {
		
		if (value1.Intersects(value2)) {

			long right_side = static_cast<long>(fmin(value1.X + value1.Width, value2.X + value2.Width));
			long left_side = static_cast<long>(fmin(value1.X, value2.X));
			long top_side = static_cast<long>(fmin(value1.Y, value2.Y));
			long bottom_side = static_cast<long>(fmin(value1.Y + value1.Height, value2.Y + value2.Height));
			return Rectangle(left_side, top_side, right_side - left_side, bottom_side - top_side);
		}

		return Rectangle(0, 0, 0, 0);
	}

	Rectangle Rectangle::Union(Rectangle const& value1, Rectangle const& value2) {
		int x = static_cast<long>(fmin(value1.X, value2.X));
		int y = static_cast<long>(fmin(value1.Y, value2.Y));

		return Rectangle(x, y,
			static_cast<long>(fmax(value1.Right(), value2.Right())) - x,
			static_cast<long>(fmax(value1.Bottom(), value2.Bottom())) - y);
	}

	//members

	long Rectangle::Left() const {
		return X;
	}

	long Rectangle::Right() const {
		return X + Width;
	}

	long Rectangle::Top() const {
		return Y;
	}

	long Rectangle::Bottom() const {
		return Y + Height;
	}

	bool Rectangle::IsEmpty() const {
		return Width == 0
			&& Height == 0
			&& X == 0
			&& Y == 0;
	}

	Point Rectangle::Location() const {
		return Point(X, Y);
	}

	void Rectangle::Location(Point const& value) {
		X = value.X;
		Y = value.Y;
	}

	Point Rectangle::Size() const {
		return Point(Width, Height);
	}

	void Rectangle::Size(Point const& value) {
		Width = value.X;
		Height = value.Y;
	}

	Point Rectangle::Center() const {
		return Point(X + (Width / 2), Y + (Height / 2));
	}

	bool Rectangle::Contains(long x, long y) const {
		return (X <= x && x < (X + Width))
			&& (Y <= y && y < (Y + Height));
	}

	bool Rectangle::Contains(double x, double y) const {
		long _x = static_cast<long>(x);
		long _y = static_cast<long>(y);
		
		return Contains(_x, _y);
	}

	bool Rectangle::Contains(Point const& value) const {
		return Contains(value.X, value.Y);
	}

	bool Rectangle::Contains(Rectangle const& value) const {
		return ((((X <= value.X) && ((value.X + value.Width) <= (X + Width))) 
			&& (Y <= value.Y)) && ((value.Y + value.Height) <= (Y + Height)));
	}

	bool Rectangle::Equals(Rectangle const& other) const {
		return ((X == other.X)
			&& (Y == other.Y)
			&& (Width == other.Width)
			&& (Height == other.Height));
	}

	void Rectangle::Inflate(long horizontalAmount, long verticalAmount) {
		X -= horizontalAmount;
		Y -= verticalAmount;
		Width += horizontalAmount * 2;
		Height += verticalAmount * 2;
	}

	void Rectangle::Inflate(double horizontalAmount, double verticalAmount) {
		long ha = static_cast<long>(horizontalAmount);
		long va = static_cast<long>(verticalAmount);
		Inflate(ha, va);
	}

	bool Rectangle::Intersects(Rectangle const& value) const {
		return value.Left() < Right() 
			&& Left() < value.Right()
			&& value.Top() < Bottom()
			&& Top() < value.Bottom();
	}

	void Rectangle::Offset(long offsetX, long offsetY) {
		X += offsetX;
		Y += offsetY;
	}

	void Rectangle::Offset(double offsetX, double offsetY) {
		long x = static_cast<long>(offsetX);
		long y = static_cast<long>(offsetY);
		Offset(x, y);
	}

	void Rectangle::Offset(Point const& amount) {
		Offset(amount.X, amount.Y);
	}

	void Rectangle::Offset(Vector2 const& amount) {
		Offset(amount.X, amount.Y);
	}

	void Rectangle::Deconstruct(long& x, long& y, long& width, long& height) {
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}
}