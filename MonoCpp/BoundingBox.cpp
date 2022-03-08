#include <stdexcept>
#include <cmath>
#include <numeric>

#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "Ray.h"

namespace Xna {

	static const Vector3 MaxVector3 = Vector3(std::numeric_limits<double>::max());
	static const Vector3 MinVector3 = Vector3(std::numeric_limits<double>::min());

	// Constructors

	BoundingBox::BoundingBox(): Min(0), Max(0) {};
	BoundingBox::BoundingBox(Vector3 min, Vector3 max):	Min(0), Max(0) {}

	// Operators
	
	std::ostream& operator<< (std::ostream& os, BoundingBox const& bb) {
		return os << "{{Min:" << bb.Min << " Max:" << bb.Max << "}}";
	}

	bool operator ==(BoundingBox a, BoundingBox b) {
		return a.Equals(b);
	}	

	bool operator !=(BoundingBox a, BoundingBox b)
	{
		return !a.Equals(b);
	}

	// Static

	BoundingBox BoundingBox::CreateFromPoints(std::vector<Vector3> const& points, int index = 0, int count = -1)
		throw(std::invalid_argument) {

		if (points.size() == 0) {
			throw std::invalid_argument("The size of the 'points' argument must be greater than 0.");
		}

		if (count == -1) {
			count = points.size();
		}

		Vector3 minVec = MaxVector3;
		Vector3 maxVec = MinVector3;

		for (int i = index; i < count; i++) {

			minVec.X = (minVec.X < points[i].X) ? minVec.X : points[i].X;
			minVec.Y = (minVec.Y < points[i].Y) ? minVec.Y : points[i].Y;
			minVec.Z = (minVec.Z < points[i].Z) ? minVec.Z : points[i].Z;

			maxVec.X = (maxVec.X > points[i].X) ? maxVec.X : points[i].X;
			maxVec.Y = (maxVec.Y > points[i].Y) ? maxVec.Y : points[i].Y;
			maxVec.Z = (maxVec.Z > points[i].Z) ? maxVec.Z : points[i].Z;
		}

		return BoundingBox(minVec, maxVec);
	}

	BoundingBox BoundingBox::CreateFromSphere(BoundingSphere const& sphere) {
		
		BoundingBox result;
		Vector3 corner(sphere.Radius);
		result.Min = sphere.Center - corner;
		result.Max = sphere.Center + corner;
	}

	BoundingBox BoundingBox::CreateMerged(BoundingBox const& original, BoundingBox const& additional) {

		BoundingBox result;
		result.Min.X = std::min(original.Min.X, additional.Min.X);
		result.Min.Y = std::min(original.Min.Y, additional.Min.Y);
		result.Min.Z = std::min(original.Min.Z, additional.Min.Z);
		result.Max.X = std::max(original.Max.X, additional.Max.X);
		result.Max.Y = std::max(original.Max.Y, additional.Max.Y);
		result.Max.Z = std::max(original.Max.Z, additional.Max.Z);

		return result;
	}

	// Members

	ContainmentType BoundingBox::Contains(BoundingBox const& box) const {
		
		if (box.Max.X < Min.X
			|| box.Min.X > Max.X
			|| box.Max.Y < Min.Y
			|| box.Min.Y > Max.Y
			|| box.Max.Z < Min.Z
			|| box.Min.Z > Max.Z) {

			return ContainmentType::Disjoint;
		}

		if (box.Min.X >= Min.X
			&& box.Max.X <= Max.X
			&& box.Min.Y >= Min.Y
			&& box.Max.Y <= Max.Y
			&& box.Min.Z >= Min.Z
			&& box.Max.Z <= Max.Z) {

			return ContainmentType::Contains;
		}			

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains(BoundingFrustum const& frustum) const {
		long i;
		ContainmentType contained;
		auto corners = frustum.GetCorners();
		auto cornersSize = corners.size();

		for (i = 0; i < cornersSize; i++) {
			contained = Contains(corners[i]);

			if (contained == ContainmentType::Disjoint)
				break;
		}		

		if (i == cornersSize) {
			return ContainmentType::Contains;
		}

		if (i != 0) {
			return ContainmentType::Intersects;
		}

		i++;
		for (; i < cornersSize; i++) {
			contained = Contains(corners[i]);

			if (contained != ContainmentType::Contains)
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	ContainmentType BoundingBox::Contains(BoundingSphere const& sphere) const {
		
		if (sphere.Center.X - Min.X >= sphere.Radius
			&& sphere.Center.Y - Min.Y >= sphere.Radius
			&& sphere.Center.Z - Min.Z >= sphere.Radius
			&& Max.X - sphere.Center.X >= sphere.Radius
			&& Max.Y - sphere.Center.Y >= sphere.Radius
			&& Max.Z - sphere.Center.Z >= sphere.Radius) {
			return ContainmentType::Contains;
		}

		double dmin = 0;

		double e = sphere.Center.X - Min.X;
		if (e < 0)
		{
			if (e < -sphere.Radius) {
				return ContainmentType::Disjoint;
			}
			dmin += e * e;
		}
		else
		{
			e = sphere.Center.X - Max.X;
			if (e > 0)
			{
				if (e > sphere.Radius)
				{
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		e = sphere.Center.Y - Min.Y;
		if (e < 0)
		{
			if (e < -sphere.Radius)
			{
				return ContainmentType::Disjoint;
			}
			dmin += e * e;
		}
		else
		{
			e = sphere.Center.Y - Max.Y;
			if (e > 0)
			{
				if (e > sphere.Radius)
				{
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		e = sphere.Center.Z - Min.Z;
		if (e < 0)
		{
			if (e < -sphere.Radius)
			{
				return ContainmentType::Disjoint;
			}
			dmin += e * e;
		}
		else
		{
			e = sphere.Center.Z - Max.Z;
			if (e > 0)
			{
				if (e > sphere.Radius)
				{
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		if (dmin <= sphere.Radius * sphere.Radius)
			return ContainmentType::Intersects;

		return ContainmentType::Disjoint;

	}

	ContainmentType BoundingBox::Contains(Vector3 const& point) const {
		ContainmentType result;

		if (point.X < Min.X
			|| point.X > Max.X
			|| point.Y < Min.Y
			|| point.Y > Max.Y
			|| point.Z < Min.Z
			|| point.Z > Max.Z) {

			result = ContainmentType::Disjoint;
		}
		else {

			result = ContainmentType::Contains;
		}

		return result;
	}	

	std::vector<Vector3> BoundingBox::GetCorners() const {
		return std::vector<Vector3>{
			Vector3(Min.X, Max.Y, Max.Z),
				Vector3(Max.X, Max.Y, Max.Z),
				Vector3(Max.X, Min.Y, Max.Z),
				Vector3(Min.X, Min.Y, Max.Z),
				Vector3(Min.X, Max.Y, Min.Z),
				Vector3(Max.X, Max.Y, Min.Z),
				Vector3(Max.X, Min.Y, Min.Z),
				Vector3(Min.X, Min.Y, Min.Z)
		};
	}

	void BoundingBox::GetCorners(std::vector<Vector3>& corners) const {
		corners[0].X = Min.X;
		corners[0].Y = Max.Y;
		corners[0].Z = Max.Z;
		corners[1].X = Max.X;
		corners[1].Y = Max.Y;
		corners[1].Z = Max.Z;
		corners[2].X = Max.X;
		corners[2].Y = Min.Y;
		corners[2].Z = Max.Z;
		corners[3].X = Min.X;
		corners[3].Y = Min.Y;
		corners[3].Z = Max.Z;
		corners[4].X = Min.X;
		corners[4].Y = Max.Y;
		corners[4].Z = Min.Z;
		corners[5].X = Max.X;
		corners[5].Y = Max.Y;
		corners[5].Z = Min.Z;
		corners[6].X = Max.X;
		corners[6].Y = Min.Y;
		corners[6].Z = Min.Z;
		corners[7].X = Min.X;
		corners[7].Y = Min.Y;
		corners[7].Z = Min.Z;
	}

	bool BoundingBox::Intersects(BoundingBox const& box) const {

		bool result;

		if ((Max.X >= box.Min.X) && (Min.X <= box.Max.X)) {
			
			if ((Max.Y < box.Min.Y) || (Min.Y > box.Max.Y))	{
				result = false;
				return;
			}

			result = (Max.Z >= box.Min.Z) && (Min.Z <= box.Max.Z);
			return;
		}

		result = false;
		return;
	}

	bool BoundingBox::Intersects(BoundingFrustum const& frustum) const {
		return Contains(frustum) != ContainmentType::Disjoint;
	}

	bool BoundingBox::Intersects(BoundingSphere const& sphere) const {
		
		double squareDistance = 0.0;
		Vector3 point = sphere.Center;

		if (point.X < Min.X) 
			squareDistance += (Min.X - point.X) * (Min.X - point.X);		
		if (point.X > Max.X) 
			squareDistance += (point.X - Max.X) * (point.X - Max.X);
		if (point.Y < Min.Y) 
			squareDistance += (Min.Y - point.Y) * (Min.Y - point.Y);
		if (point.Y > Max.Y)
			squareDistance += (point.Y - Max.Y) * (point.Y - Max.Y);
		if (point.Z < Min.Z)
			squareDistance += (Min.Z - point.Z) * (Min.Z - point.Z);
		if (point.Z > Max.Z)
			squareDistance += (point.Z - Max.Z) * (point.Z - Max.Z);
		
		return squareDistance <= sphere.Radius * sphere.Radius;
	}

	PlaneIntersectionType BoundingBox::Intersects(Plane const& plane) const {
		
		PlaneIntersectionType result;
		Vector3 positiveVertex;
		Vector3 negativeVertex;

		if (plane.Normal.X >= 0) {
			positiveVertex.X = Max.X;
			negativeVertex.X = Min.X;
		}
		else {
			positiveVertex.X = Min.X;
			negativeVertex.X = Max.X;
		}

		if (plane.Normal.Y >= 0) {
			positiveVertex.Y = Max.Y;
			negativeVertex.Y = Min.Y;
		}
		else {
			positiveVertex.Y = Min.Y;
			negativeVertex.Y = Max.Y;
		}

		if (plane.Normal.Z >= 0) {
			positiveVertex.Z = Max.Z;
			negativeVertex.Z = Min.Z;
		}
		else {
			positiveVertex.Z = Min.Z;
			negativeVertex.Z = Max.Z;
		}
		
		double distance = plane.Normal.X * negativeVertex.X 
			+ plane.Normal.Y * negativeVertex.Y 
			+ plane.Normal.Z * negativeVertex.Z 
			+ plane.D;

		if (distance > 0) {
			result = PlaneIntersectionType::Front;
			return;
		}
		
		distance = plane.Normal.X * positiveVertex.X 
			+ plane.Normal.Y * positiveVertex.Y 
			+ plane.Normal.Z * positiveVertex.Z 
			+ plane.D;
		
		if (distance < 0) {
			result = PlaneIntersectionType::Back;
			return;
		}

		result = PlaneIntersectionType::Intersecting;

		return result;
	}

	double BoundingBox::Intersects(Ray ray) const {
		return ray.Intersects((*this));
	}

	void BoundingBox::Deconstruct(Vector3 &min, Vector3 &max) const
	{
		min = Min;
		max = Max;
	}

	constexpr bool BoundingBox::Equals(BoundingBox const& other) const {
		return (Min == other.Min) && (Max == other.Max);
	}
}