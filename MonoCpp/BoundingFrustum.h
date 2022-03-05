#ifndef _BOUNDING_FRUSTUM_H_
#define _BOUNDING_FRUSTUM_H_

#include <vector>
#include "Matrix.h"
#include "Vector3.h"
#include "ContainmentType.h"
#include "PlaneIntersectionType.h"

namespace Xna {

	struct Plane;
	struct BoundingBox;
	struct BoundingFrustum;
	struct BoundingSphere;
	struct Ray;

	struct BoundingFrustum {

		static constexpr long PlaneCount = 6;
		static constexpr long CornerCount = 8;

		BoundingFrustum();
		BoundingFrustum(Matrix value);

		friend std::ostream& operator<< (std::ostream& os, BoundingFrustum const& bf);
		friend bool operator ==(BoundingFrustum a, BoundingFrustum b);
		friend bool operator !=(BoundingFrustum a, BoundingFrustum b);

		Matrix Matrix_();
		Matrix Matrix_(Matrix value);
		Plane Near();
		Plane Far();
		Plane Left();
		Plane Right();
		Plane Top();
		Plane Bottom();

		ContainmentType Contains(BoundingBox box);
		ContainmentType Contains(BoundingFrustum frustum);
		ContainmentType Contains(BoundingSphere sphere);
		ContainmentType Contains(Vector3 point);
		std::vector<Vector3> GetCorners();
		void GetCorners(std::vector<Vector3> corners);
		bool Intersects(BoundingBox box);
		bool Intersects(BoundingFrustum frustum);
		bool Intersects(BoundingSphere sphere);
		PlaneIntersectionType Intersects(Plane plane);
		double Intersects(Ray ray)

		bool Equals(BoundingFrustum other);

	private:
		Matrix _matrix;
		const std::vector<Vector3> _corners;
		const std::vector<Plane> _planes;

		static Vector3 IntersectionPoint(Plane a, Plane b, Plane c);
		void NormalizePlane(Plane& p);

		void CreateCorners();
		void CreatePlanes()
	};
}

#endif // !_BOUNDING_FRUSTUM_H_
