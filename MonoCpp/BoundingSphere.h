#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include <vector>
#include "Vector3.h"
#include "ContainmentType.h"
#include "PlaneIntersectionType.h"

namespace Xna {
	
	struct BoundingFrustum;
	struct BoundingBox;
	struct Ray;
	struct Plane;
	struct Matrix;

	// Describes a sphere in 3D-space for bounding operations.
	struct BoundingSphere {

		Vector3 Center;
		double Radius;

		BoundingSphere();
		BoundingSphere(Vector3 center, double radius);

		friend bool operator == (BoundingSphere a, BoundingSphere b);
		friend bool operator != (BoundingSphere a, BoundingSphere b);

		static BoundingSphere CreateFromFrustum(BoundingFrustum const& frustum);
		static BoundingSphere CreateFromPoints(std::vector<Vector3> const& points);
		static BoundingSphere CreateMerged(BoundingSphere const& original, BoundingSphere const& additional);
		static BoundingSphere CreateFromBoundingBox(BoundingBox const& box);

		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingSphere const& sphere) const;
		//bool Intersects(BoundingFrustum frustum);			//this code is not implemented in source code.
		PlaneIntersectionType Intersects(Plane const& plane) const;
		double Intersects(Ray const& ray) const;
		BoundingSphere Transform(Matrix const& matrix);

		void Deconstruct(Vector3& center, double& radius) const;
		bool Equals(BoundingSphere const& other) const;
	};
}

#endif
