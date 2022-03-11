#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

namespace Xna {		

	struct Point;
	struct Vector2;

	//Describes a 2D rectangle
	//C#: struct Rectangle
	struct Rectangle {		

		long X;		
		long Y;		
		long Width;		
		long Height;

		Rectangle();
		Rectangle(long x, long y, long width, long height);
		Rectangle(Point location, Point size);

		friend std::ostream& operator<< (std::ostream& os, Rectangle const& obj);
		friend bool operator== (Rectangle, Rectangle);
		friend bool operator!= (Rectangle, Rectangle);

		// Returns a rectangle with X=0, Y=0, Width=0, Height=0.
		static Rectangle Empty();
		
		//Creates a new rectangle that contains overlapping region of two other rectangles.
		static Rectangle Intersects(Rectangle const&, Rectangle const&);
		
		//Creates a new rectangle that completely contains two other rectangles.
		static Rectangle Union(Rectangle const&, Rectangle const&);

		//Returns the x coordinate of the left edge.
		long Left() const;
		//Returns the x coordinate of the right edge.
		long Right() const;
		//Returns the y coordinate of the top edge.
		long Top() const;
		//Returns the y coordinate of the bottom edge.
		long Bottom() const;
		//If this rectangle is with X=0, Y=0, Width=0, Height=0.
		bool IsEmpty() const;
		
		//The top-left coordinate.
		Point Location() const;
		void Location(Point const& value);
		
		//The width-height coordinates.
		Point Size() const;
		void Size(Point const& value);
		
		//A point located in the center of this rectangle.
		Point Center() const;

		//Gets whether or not the provided coordinates lie within the bounds.
		bool Contains(long x, long y) const;
		bool Contains(double x, double y) const;
		bool Contains(Point const& value) const;
		bool Contains(Rectangle const& value) const;		

		//Adjusts the edges of this rectangle by specified horizontal and vertical amounts.
		void Inflate(long horizontalAmount, long verticalAmount);
		void Inflate(double horizontalAmount, double verticalAmount);

		//Gets whether or not the other rectangle intersects with this rectangle.
		bool Intersects(Rectangle const& value) const;		

		//Changes the location of this rectangle..
		void Offset(long offsetX, long offsetY);
		void Offset(double offsetX, double offsetY);
		void Offset(Point const& amount);		
		void Offset(Vector2 const& amount);		

		//Deconstruction method for rectangle.
		void Deconstruct(long& x, long& y, long& width, long& height) const;
		//Compares whether current rectangle is equal to specified rectangle.
		bool Equals(Rectangle const& other) const;
	};
}

#endif