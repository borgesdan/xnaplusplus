#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "Vector3.h"

namespace Xna {

	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;

	// Represents a ray with an origin and a direction in 3D space.
	// C#: struct Ray
	struct Ray {

		Vector3 Direction;
		Vector3 Position;

		Ray();
		Ray(Vector3 position, Vector3 direction);

		friend bool operator !=(Ray a, Ray b);
		friend bool operator ==(Ray a, Ray b);

		double Intersects(BoundingBox const& box) const;		
		double Intersects(BoundingSphere const& sphere) const;
		double Intersects(Plane const& plane) const;

		void Deconstruct(Vector3& position, Vector3& direction) const;
		bool Equals(Ray const& other) const;

		//C# code not implemented
		//double Intersects(BoundingFrustum frustum);
	};
}

#endif // !_RAY_H_
