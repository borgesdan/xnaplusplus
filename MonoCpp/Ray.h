#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

namespace Xna {

	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;

	struct Ray {

		Vector3 Direction;
		Vector3 Position;

		Ray();
		Ray(Vector3 position, Vector3 direction);

		friend bool operator !=(Ray a, Ray b);
		friend bool operator ==(Ray a, Ray b);

		double Intersects(BoundingBox const& box) const;
		//double Intersects(BoundingFrustum frustum); //it's not implement in source code
		double Intersects(BoundingSphere const& sphere) const;
		double Intersects(Plane const& plane) const;

		void Deconstruct(Vector3& position, Vector3& direction);
		bool Equals(Ray other);
	};
}

#endif // !_RAY_H_
