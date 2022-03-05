#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

namespace Xna {		

	struct Point;
	struct Vector2;

	//Describes a 2D rectangle
	struct Rectangle {		

		long X;		
		long Y;		
		long Width;		
		long Height;

		Rectangle();
		Rectangle(long x, long y, long width, long height);
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
		void Location(Point const&);
		
		//The width-height coordinates.
		Point Size() const;
		void Size(Point const&);
		
		//A point located in the center of this rectangle.
		Point Center() const;

		//Gets whether or not the provided coordinates lie within the bounds.
		bool Contains(long, long) const;
		bool Contains(double, double) const;
		bool Contains(Point const&) const;
		bool Contains(Rectangle const&) const;

		//Compares whether current rectangle is equal to specified rectangle.
		bool Equals(Rectangle const&) const;

		//Adjusts the edges of this rectangle by specified horizontal and vertical amounts.
		void Inflate(long, long);
		void Inflate(double, double);

		//Gets whether or not the other rectangle intersects with this rectangle.
		bool Intersects(Rectangle const&) const;		

		//Changes the location of this rectangle..
		void Offset(long, long);
		void Offset(double, double);
		void Offset(Point const&);		
		void Offset(Vector2 const&);		

		//Deconstruction method for rectangle.
		void Deconstruct(long&, long&, long&, long&);
	};
}

#endif