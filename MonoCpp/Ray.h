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

		Vector3();
		Vector3(Vector3 position, Vector3 direction);

		friend bool operator !=(Ray a, Ray b);
		friend bool operator ==(Ray a, Ray b);

		double Intersects(BoundingBox box);
		//double Intersects(BoundingFrustum frustum); //it's not implement in source code
		float Intersects(BoundingSphere sphere);
		float Intersects(Plane plane);

		void Deconstruct(Vector3& position, Vector3& direction);
		bool Equals(Ray other);
	};
}

#endif // !_RAY_H_
