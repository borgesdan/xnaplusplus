#ifndef _POINT_H_
#define _POINT_H_

namespace Xna {
	
	struct Vector2;

	//Describes a 2D point.
	struct Point {
		long X;
		long Y;

		Point(long x, long y);
		Point(long value);

		friend Point operator+ (Point, Point);
		friend Point operator- (Point, Point);
		friend Point operator* (Point, Point);
		friend Point operator/ (Point, Point);
		friend Point operator== (Point, Point);
		friend Point operator!= (Point, Point);

		//Returns a point with coordinates 0, 0.
		static Point Zero();

		//Compares whether current instance is equal to specified point.
		bool Equals(Point const& other);		

		//Gets a vector2 representation for this object.		
		Vector2 ToVector2();

		//Deconstruction method for point.
		void Deconstruct(int& x, int& y);
	};
}

#endif