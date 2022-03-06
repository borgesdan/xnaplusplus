#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_

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
		Vector3 Radius;

		BoundingSphere();
		BoundingSphere(Vector3 center, double radius);

		friend std::ostream& operator<< (std::ostream& os, BoundingSphere const& bs);
		friend bool operator == (BoundingSphere a, BoundingSphere b);
		friend bool operator != (BoundingSphere a, BoundingSphere b);

		static BoundingSphere CreateFromFrustum(BoundingFrustum frustum);
		static BoundingSphere CreateFromPoints(std::vector<Vector3> points);
		static BoundingSphere CreateMerged(BoundingSphere original, BoundingSphere additional);

		static BoundingSphere CreateFromBoundingBox(BoundingBox box);		

		ContainmentType Contains(BoundingBox box) const;
		ContainmentType Contains(BoundingFrustum frustum) const;
		ContainmentType Contains(BoundingSphere sphere) const;
		ContainmentType Contains(Vector3 point) const;
		bool Intersects(BoundingBox box) const;
		bool Intersects(BoundingSphere sphere) const;		
		//bool Intersects(BoundingFrustum frustum);			//this code is not implemented in source code.
		PlaneIntersectionType Intersects(Plane plane) const;
		double Intersects(Ray ray) const;
		BoundingSphere Transform(Matrix matrix);

		void Deconstruct(Vector3& center, double& radius);
		bool Equals(BoundingSphere other);
	};
}

#endif // !_BOUNDING_SPHERE_H_
