#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CSharp.h"

namespace Xna {		

	struct Point;
	struct Vector2;

	//Describes a 2D rectangle
	//C#: struct Rectangle
	struct Rectangle {		

		i32 X;		
		i32 Y;		
		i32 Width;		
		i32 Height;

		Rectangle();
		Rectangle(i32 x, i32 y, i32 width, i32 height);
		Rectangle(Point location, Point size);

		friend bool operator== (Rectangle, Rectangle);
		friend bool operator!= (Rectangle, Rectangle);

		// Returns a rectangle with X=0, Y=0, Width=0, Height=0.
		static Rectangle Empty();
		
		//Creates a new rectangle that contains overlapping region of two other rectangles.
		static Rectangle Intersects(Rectangle const&, Rectangle const&);
		
		//Creates a new rectangle that completely contains two other rectangles.
		static Rectangle Union(Rectangle const&, Rectangle const&);

		//Returns the x coordinate of the left edge.
		i32 Left() const;
		//Returns the x coordinate of the right edge.
		i32 Right() const;
		//Returns the y coordinate of the top edge.
		i32 Top() const;
		//Returns the y coordinate of the bottom edge.
		i32 Bottom() const;
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
		bool Contains(i32 x, i32 y) const;
		bool Contains(double x, double y) const;
		bool Contains(Point const& value) const;
		bool Contains(Rectangle const& value) const;		

		//Adjusts the edges of this rectangle by specified horizontal and vertical amounts.
		void Inflate(i32 horizontalAmount, i32 verticalAmount);
		void Inflate(double horizontalAmount, double verticalAmount);

		//Gets whether or not the other rectangle intersects with this rectangle.
		bool Intersects(Rectangle const& value) const;		

		//Changes the location of this rectangle..
		void Offset(i32 offsetX, i32 offsetY);
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