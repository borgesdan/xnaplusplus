#ifndef PLANE_H
#define PLANE_H

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

		friend std::ostream& operator<< (std::ostream& os, Plane const& pl);
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
		PlaneIntersectionType Intersects(BoundingBox const&) const;
		PlaneIntersectionType Intersects(BoundingFrustum const&) const;
		PlaneIntersectionType Intersects(BoundingSphere const&) const;
		PlaneIntersectionType Intersects(Vector3 const& point) const;
		void Deconstruct(Vector3, double);

	private:
		PlaneIntersectionType Intersects(Vector3 point);
	};

	struct PlaneHelper {

		// Returns a value indicating what side (positive/negative) of a plane a point is
		// point: The point to check with
		// plane: The plane to check against
		// Returns greater than zero if on the positive side, less than zero if on the negative size, 0 otherwise.
		static constexpr double ClassifyPoint(Vector3 const& point, Plane const& plane) {
			return point.X * plane.Normal.X 
				+ point.Y * plane.Normal.Y 
				+ point.Z * plane.Normal.Z 
				+ plane.D;
		}

	   // Returns the perpendicular distance from a point to a plane.	   
	   // point: The point to check.
	   // plane: The place to check.
	   // The perpendicular distance from the point to the plane.
		static constexpr double PerpendicularDistance(Vector3 const& point, Plane const& plane)	{
			// dist = (ax + by + cz + d) / sqrt(a*a + b*b + c*c)
			return std::abs((plane.Normal.X * point.X + plane.Normal.Y * point.Y + plane.Normal.Z * point.Z)
				/ std::sqrt(plane.Normal.X * plane.Normal.X + plane.Normal.Y * plane.Normal.Y + plane.Normal.Z * plane.Normal.Z));
		}

	};
}

#endif // !_PLANE_H_
