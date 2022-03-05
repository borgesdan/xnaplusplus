#ifndef _PLANE_H_
#define _PLANE_H_

#include "Vector3.h"
#include "Vector4.h"

namespace Xna {
	
	struct Matrix;
	struct Quaternion;
	struct BoundingBox;
	struct BoundingFrustum;
	struct BoundingSphere;
	enum class PlaneIntersectionType;

	// A plane in 3d space, represented by its normal away from the origin and its distance from the origin, D.
	struct Plane {

		double D;
		Vector3 Normal;

		Plane();
		Plane(Vector4);
		Plane(Vector3, double);
		Plane(Vector3, Vector3, Vector3);
		Plane(double, double, double, double);
		Plane(Vector3 normal);

		friend bool operator!= (Plane plane1, Plane plane2);
		friend bool operator== (Plane plane1, Plane plane2);

		static Plane Transform(Plane, Matrix);
		static Plane Transform(Plane plane, Quaternion rotation);
		static Plane Normalize(Plane value);

		double Dot(Vector4);
		double DotCoordinate(Vector3);
		double DotNormal(Vector3);
		void Normalize();
		bool Equals(Plane other);
		PlaneIntersectionType Intersects(BoundingBox);
		PlaneIntersectionType Intersects(BoundingFrustum);
		PlaneIntersectionType Intersects(BoundingSphere);
		void Deconstruct(Vector3, double);

	private:
		PlaneIntersectionType Intersects(Vector3 point);
	};
}

#endif // !_PLANE_H_
