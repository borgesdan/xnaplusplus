#include "BoundingFrustum.h"
#include "Plane.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

namespace Xna {

	BoundingFrustum::BoundingFrustum() {};

	BoundingFrustum::BoundingFrustum(Matrix value) {
		_matrix = value;
		CreatePlanes();
		CreateCorners();
	};

	// Operators
	std::ostream& operator<< (std::ostream& os, BoundingFrustum const& bf) {
		return os << "{Near: " << bf._planes[0] <<
			" Far:" << bf._planes[1] <<
			" Left:" << bf._planes[2] <<
			" Right:" << bf._planes[3] <<
			" Top:" << bf._planes[4] <<
			" Bottom:" << bf._planes[5] <<
			"}";
	}

	bool operator ==(BoundingFrustum a, BoundingFrustum b) {
		return a.Equals(b);
	}

	bool operator !=(BoundingFrustum a, BoundingFrustum b) {
		return !a.Equals(b);
	}

	// Members

	constexpr Matrix BoundingFrustum::Matrix_() const {
		return _matrix;
	}

	void BoundingFrustum::Matrix_(Matrix value) {
		_matrix = value;
		CreatePlanes();
		CreateCorners();
	}

	constexpr Plane BoundingFrustum::Near() const {
		return _planes[0];
	}

	constexpr Plane BoundingFrustum::Far() const {
		return _planes[1];
	}

	constexpr Plane BoundingFrustum::Left() const {
		return _planes[2];
	}

	constexpr Plane BoundingFrustum::Right() const {
		return _planes[3];
	}

	constexpr Plane BoundingFrustum::Top() const {
		return _planes[4];
	}

	constexpr Plane BoundingFrustum::Bottom() const {
		return _planes[5];
	}

	ContainmentType BoundingFrustum::Contains(BoundingBox const& box) const {

		ContainmentType result;
		bool intersects = false;

		for (long i = 0; i < PlaneCount; ++i)
		{
			PlaneIntersectionType planeIntersectionType = box.Intersects(_planes[i]);

			switch (planeIntersectionType) {

			case PlaneIntersectionType::Front:
				result = ContainmentType::Disjoint;
				return;
			case PlaneIntersectionType::Intersecting:
				intersects = true;
				break;
			}
		}
		result = intersects ? ContainmentType::Intersects : ContainmentType::Contains;
		return result;
	}

	ContainmentType BoundingFrustum::Contains(BoundingFrustum const& frustum) const {
		
		if (*(this) == frustum)                
			return ContainmentType::Contains;

		bool intersects = false;
		for (long i = 0; i < PlaneCount; ++i)
		{
			PlaneIntersectionType planeIntersectionType = frustum.Intersects(_planes[i]);
			
			switch (planeIntersectionType)
			{
			case PlaneIntersectionType::Front:
				return ContainmentType::Disjoint;
			case PlaneIntersectionType::Intersecting:
				intersects = true;
				break;
			}
		}

		return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
	}

	ContainmentType BoundingFrustum::Contains(BoundingSphere const& sphere) const {

		ContainmentType result;

		bool intersects = false;
		for (long i = 0; i < PlaneCount; ++i)
		{
			PlaneIntersectionType planeIntersectionType = sphere.Intersects(_planes[i]);
		
			switch (planeIntersectionType)
			{
			case PlaneIntersectionType::Front:
				result = ContainmentType::Disjoint;
				return;
			case PlaneIntersectionType::Intersecting:
				intersects = true;
				break;
			}
		}
		result = intersects ? ContainmentType::Intersects : ContainmentType::Contains;

		return result;
	}

	ContainmentType BoundingFrustum::Contains(Vector3 const& point) const {

		ContainmentType result;

		for (long i = 0; i < PlaneCount; ++i)
		{			
			if (PlaneHelper::ClassifyPoint(point, _planes[i]) > 0)
			{
				result = ContainmentType::Disjoint;
				return;
			}
		}

		result = ContainmentType::Contains;
	}
}