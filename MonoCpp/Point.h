#ifndef POINT_H
#define POINT_H

#include "CSharp.h"

namespace Xna {
	
	struct Vector2;

	//Describes a 2D point.
	//C#: struct Point
	struct Point {
		i32 X;
		i32 Y;

		Point(i32 x, i32 y);
		Point(i32 value);

		friend Point operator+ (Point value1, Point value2);
		friend Point operator- (Point value1, Point value2);
		friend Point operator* (Point value1, Point value2);
		friend Point operator/ (Point value1, Point value2);
		friend Point operator== (Point value1, Point value2);
		friend Point operator!= (Point value1, Point value2);

		//Returns a point with coordinates 0, 0.
		static Point Zero();
		
		//Gets a vector2 representation for this object.		
		Vector2 ToVector2() const;

		//Deconstruction method for point.
		void Deconstruct(i32& x, i32& y) const;
		//Compares whether current instance is equal to specified point.
		bool Equals(Point const& other) const;
	};
}

#endif