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

		ContainmentType Contains(BoundingBox box);
		ContainmentType Contains(BoundingFrustum frustum);
		ContainmentType Contains(BoundingSphere sphere);
		ContainmentType Contains(Vector3 point);
		bool Intersects(BoundingBox box);
		bool Intersects(BoundingSphere sphere);		
		//bool Intersects(BoundingFrustum frustum);			//this code is not implemented in source code.
		PlaneIntersectionType Intersects(Plane plane);
		double Intersects(Ray ray);
		BoundingSphere Transform(Matrix matrix);

		void Deconstruct(Vector3& center, double& radius);
		bool Equals(BoundingSphere other);
	};
}

#endif // !_BOUNDING_SPHERE_H_
