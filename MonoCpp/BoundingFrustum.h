#ifndef BOUNDING_FRUSTUM_H
#define BOUNDING_FRUSTUM_H

#include <vector>
#include "Matrix.h"
#include "ContainmentType.h"
#include "PlaneIntersectionType.h"
#include "Vector3.h"

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

		constexpr Matrix Matrix_() const;
		void Matrix_(Matrix value);
		constexpr Plane Near() const;
		constexpr Plane Far() const;
		constexpr Plane Left() const;
		constexpr Plane Right() const;
		constexpr Plane Top() const;
		constexpr Plane Bottom() const;

		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;
		std::vector<Vector3> GetCorners() const;
		void GetCorners(std::vector<Vector3> corners);
		bool Intersects(BoundingBox box) const;
		bool Intersects(BoundingFrustum frustum) const;
		bool Intersects(BoundingSphere sphere) const;
		PlaneIntersectionType Intersects(Plane plane) const;
		double Intersects(Ray ray) const;

		bool Equals(BoundingFrustum other);

	private:
		Matrix _matrix;
		const std::vector<Vector3> _corners;
		const std::vector<Plane> _planes;

		static Vector3 IntersectionPoint(Plane a, Plane b, Plane c);
		void NormalizePlane(Plane& p);

		void CreateCorners();
		void CreatePlanes();
	};
}

#endif // !_BOUNDING_FRUSTUM_H_
