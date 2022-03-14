#include <algorithm>
#include <iterator>
#include <numeric>

#include "BoundingFrustum.h"
#include "Plane.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Ray.h"

namespace Xna {

	BoundingFrustum::BoundingFrustum(): 
		_corners(CornerCount), _planes(PlaneCount) {};

	BoundingFrustum::BoundingFrustum(Matrix value): 
		_matrix(value), _corners(CornerCount), _planes(PlaneCount) {
		CreatePlanes();
		CreateCorners();
	};

	// Operators	

	bool operator ==(BoundingFrustum a, BoundingFrustum b) {
		return a.Equals(b);
	}

	bool operator !=(BoundingFrustum a, BoundingFrustum b) {
		return !a.Equals(b);
	}

	// Members

	Matrix BoundingFrustum::Matrix_() const {
		return _matrix;
	}

	void BoundingFrustum::Matrix_(Matrix value) {
		_matrix = value;
		CreatePlanes();
		CreateCorners();
	}

	Plane BoundingFrustum::Near() const {
		return _planes[0];
	}

	Plane BoundingFrustum::Far() const {
		return _planes[1];
	}

	Plane BoundingFrustum::Left() const {
		return _planes[2];
	}

	Plane BoundingFrustum::Right() const {
		return _planes[3];
	}

	Plane BoundingFrustum::Top() const {
		return _planes[4];
	}

	Plane BoundingFrustum::Bottom() const {
		return _planes[5];
	}

	ContainmentType BoundingFrustum::Contains(BoundingBox const& box) const {

		bool intersects = false;

		for (i32 i = 0; i < PlaneCount; ++i)
		{
			PlaneIntersectionType planeIntersectionType = box.Intersects(_planes[i]);

			switch (planeIntersectionType) {

			case PlaneIntersectionType::Front:
				return ContainmentType::Disjoint;				
			case PlaneIntersectionType::Intersecting:
				intersects = true;
				break;
			}
		}

		return intersects ? ContainmentType::Intersects : ContainmentType::Contains;
	}

	ContainmentType BoundingFrustum::Contains(BoundingFrustum const& frustum) const {
		
		if (*(this) == frustum)                
			return ContainmentType::Contains;

		bool intersects = false;
		for (i32 i = 0; i < PlaneCount; ++i)
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

		bool intersects = false;
		for (i32 i = 0; i < PlaneCount; ++i)
		{
			PlaneIntersectionType planeIntersectionType = sphere.Intersects(_planes[i]);
		
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

	ContainmentType BoundingFrustum::Contains(Vector3 const& point) const {

		for (i32 i = 0; i < PlaneCount; ++i)
		{			
			if (Plane::ClassifyPoint(point, _planes[i]) > 0) {
				return ContainmentType::Disjoint;
			}
		}

		return ContainmentType::Contains;
	}

	std::vector<Vector3> BoundingFrustum::GetCorners() const {
		
		return std::vector<Vector3>(_corners);
	}

	void BoundingFrustum::GetCorners(std::vector<Vector3>& corners) {		

		std::copy(_corners.begin(), _corners.end(), std::back_inserter(corners));
	}

	bool BoundingFrustum::Intersects(BoundingBox const& box) const {
		return Contains(box) != ContainmentType::Disjoint;
	}

	bool BoundingFrustum::Intersects(BoundingFrustum const& frustum) const {
		return Contains(frustum) != ContainmentType::Disjoint;
	}

	bool BoundingFrustum::Intersects(BoundingSphere const& sphere) const {
		return Contains(sphere) != ContainmentType::Disjoint;
	}

	PlaneIntersectionType BoundingFrustum::Intersects(Plane const& plane) const {

		PlaneIntersectionType result = plane.Intersects(_corners[0]);

		for (i32 i = 1; i < _corners.size(); i++) {
			if (plane.Intersects(_corners[i]) != result) {
				result = PlaneIntersectionType::Intersecting;
			}
		}			

		return result;
	}

	double BoundingFrustum::Intersects(Ray const& ray) const {

		constexpr double nan = std::numeric_limits<double>::quiet_NaN();
		ContainmentType ctype = Contains(ray.Position);

		switch (ctype)
		{
			case ContainmentType::Disjoint:
				return nan;
			case ContainmentType::Contains:
				return 0.0;
			case ContainmentType::Intersects:
				//TODO: NotImplementedException
				return nan;
			default:
				//TODO: ArgumentOutOfRangeException;
				return nan;
		}

		return nan;
	}

	bool BoundingFrustum::Equals(BoundingFrustum const& other) {		

		//if (Equals(a, null))
		//	return (Equals(b, null));

		//if (Equals(b, null))
		//	return (Equals(a, null));

		return _matrix == other._matrix;
	}

	// Private
		// Static
	Vector3 BoundingFrustum::IntersectionPoint(Plane const& a, Plane const& b, Plane const& c) {

		Vector3 result;

		Vector3 v1, v2, v3;
		Vector3 cross =	Vector3::Cross(b.Normal, c.Normal);

		double f = Vector3::Dot(a.Normal, cross);
		f *= -1.0;

		cross = Vector3::Cross(b.Normal, c.Normal);
		v1 = Vector3::Multiply(cross, a.D);

		cross = Vector3::Cross(c.Normal, a.Normal);
		v2 = Vector3::Multiply(cross, b.D);

		cross = Vector3::Cross(a.Normal, b.Normal);
		v3 = Vector3::Multiply(cross, c.D);		

		result.X = (v1.X + v2.X + v3.X) / f;
		result.Y = (v1.Y + v2.Y + v3.Y) / f;
		result.Z = (v1.Z + v2.Z + v3.Z) / f;

		return result;
	}

		// Members

	void BoundingFrustum::NormalizePlane(Plane& p) {
		double factor = 1.0 / p.Normal.Length();
		p.Normal.X *= factor;
		p.Normal.Y *= factor;
		p.Normal.Z *= factor;
		p.D *= factor;
	}

	void BoundingFrustum::CreateCorners() {

		_corners[0] = IntersectionPoint(_planes[0], _planes[2], _planes[4]);
		_corners[1] = IntersectionPoint(_planes[0], _planes[3], _planes[4]);
		_corners[2] = IntersectionPoint(_planes[0], _planes[3], _planes[5]);
		_corners[3] = IntersectionPoint(_planes[0], _planes[2], _planes[5]);
		_corners[4] = IntersectionPoint(_planes[1], _planes[2], _planes[4]);
		_corners[5] = IntersectionPoint(_planes[1], _planes[3], _planes[4]);
		_corners[6] = IntersectionPoint(_planes[1], _planes[3], _planes[5]);
		_corners[7] = IntersectionPoint(_planes[1], _planes[2], _planes[5]);

	}

	void BoundingFrustum::CreatePlanes() {

		_planes[0] = Plane(-_matrix.M13, -_matrix.M23, -_matrix.M33, -_matrix.M43);
		_planes[1] = Plane(_matrix.M13 - _matrix.M14, _matrix.M23 - _matrix.M24, _matrix.M33 - _matrix.M34, _matrix.M43 - _matrix.M44);
		_planes[2] = Plane(-_matrix.M14 - _matrix.M11, -_matrix.M24 - _matrix.M21, -_matrix.M34 - _matrix.M31, -_matrix.M44 - _matrix.M41);
		_planes[3] = Plane(_matrix.M11 - _matrix.M14, _matrix.M21 - _matrix.M24, _matrix.M31 - _matrix.M34, _matrix.M41 - _matrix.M44);
		_planes[4] = Plane(_matrix.M12 - _matrix.M14, _matrix.M22 - _matrix.M24, _matrix.M32 - _matrix.M34, _matrix.M42 - _matrix.M44);
		_planes[5] = Plane(-_matrix.M14 - _matrix.M12, -_matrix.M24 - _matrix.M22, -_matrix.M34 - _matrix.M32, -_matrix.M44 - _matrix.M42);

		NormalizePlane(_planes[0]);
		NormalizePlane(_planes[1]);
		NormalizePlane(_planes[2]);
		NormalizePlane(_planes[3]);
		NormalizePlane(_planes[4]);
		NormalizePlane(_planes[5]);
	}
}