#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"
#include "Vector4.h"
#include "PlaneIntersectionType.h"

namespace Xna {
	
	struct Matrix;
	struct Quaternion;
	struct BoundingBox;
	struct BoundingFrustum;
	struct BoundingSphere;

	// A plane in 3d space, represented by its normal away from the origin and its distance from the origin, D.
	struct Plane {

		double D;
		Vector3 Normal;

		Plane();
		Plane(Vector4 value);
		Plane(Vector3 normal, double d);
		Plane(Vector3 a, Vector3 b, Vector3 c);
		Plane(double a, double b, double c, double d);
		Plane(Vector3 pointOnPlane, Vector3 normal);

		friend std::ostream& operator<< (std::ostream& os, Plane const& pl);
		friend bool operator!= (Plane plane1, Plane plane2);
		friend bool operator== (Plane plane1, Plane plane2);

		static Plane Transform(Plane plane, Matrix matrix);
		static Plane Transform(Plane plane, Quaternion rotation);
		static Plane Normalize(Plane value);

		double Dot(Vector4 const& value) const;
		double DotCoordinate(Vector3 const& value) const;
		double DotNormal(Vector3 const& value) const;
		void Normalize();		
		PlaneIntersectionType Intersects(BoundingBox const& box) const;
		PlaneIntersectionType Intersects(BoundingFrustum const& frustum) const;
		PlaneIntersectionType Intersects(BoundingSphere const& sphere) const;
		PlaneIntersectionType Intersects(Vector3 const& point) const;
		void Deconstruct(Vector3& normal, double& d) const;
		bool Equals(Plane const& other) const;

		//----- PlaneHelper internal class in Plane.cs

		// Returns a value indicating what side (positive/negative) of a plane a point is
		// point: The point to check with
		// plane: The plane to check against
		// Returns greater than zero if on the positive side, less than zero if on the negative size, 0 otherwise.
		static double ClassifyPoint(Vector3 const& point, Plane const& plane);

		// Returns the perpendicular distance from a point to a plane.	   
		// point: The point to check.
		// plane: The place to check.
		// The perpendicular distance from the point to the plane.
		static double PerpendicularDistance(Vector3 const& point, Plane const& plane);
	};	
}

#endif
