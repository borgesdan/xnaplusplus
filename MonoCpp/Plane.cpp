#include "Plane.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "BoundingSphere.h"

namespace Xna {

	static void constructPlane(Vector3& normal, float d) {

	}

	Plane::Plane() :
		Normal(Vector3()), D(0) {}

	Plane::Plane(Vector4 value) :
		Normal(Vector3(value.X, value.Y, value.Z)), D(value.W) {}

	Plane::Plane(Vector3 normal, double d) :
		Normal(normal), D(d) {}

	Plane::Plane(Vector3 a, Vector3 b, Vector3 c) {
		Vector3 ab = b - a;
		Vector3 ac = c - a;

		Vector3 cross = Vector3::Cross(ab, ac);
		Normal = Vector3::Normalize(cross);
		D = -Vector3::Dot(Normal, a);
	}

	Plane::Plane(double a, double b, double c, double d) :
		Normal(Vector3(a, b, c)), D(d) {}

	Plane::Plane(Vector3 pointOnPlane, Vector3 normal) {
		Normal = normal;
		D = -(
			pointOnPlane.X * normal.X +
			pointOnPlane.Y * normal.Y +
			pointOnPlane.Z * normal.Z
			);
	}

	std::ostream& operator<< (std::ostream& os, Plane const& pl) {
		return os << "{Normal:" << pl.Normal << " D:" << pl.D << "}";
	}

	bool operator!= (Plane plane1, Plane plane2) {
		return !plane1.Equals(plane2);
	}

	bool operator== (Plane plane1, Plane plane2) {
		return plane1.Equals(plane2);
	}

	Plane Plane::Transform(Plane plane, Matrix matrix) {
		Matrix transformedMatrix = Matrix::Invert(matrix);
		transformedMatrix = Matrix::Transpose(transformedMatrix);

		Vector4 vector = Vector4(plane.Normal, plane.D);

		Vector4 transformedVector = Vector4::Transform(vector, transformedMatrix);

		return Plane(transformedVector);
	}

	Plane Plane::Transform(Plane plane, Quaternion rotation) {
		Vector3 result = Vector3::Transform(plane.Normal, rotation);
		return Plane(result, plane.D);
	}

	Plane Plane::Normalize(Plane value) {
		double length = value.Normal.Length();
		double factor = 1.0 / length;

		Vector3 result = Vector3::Multiply(value.Normal, factor);
		return Plane(result, value.D * factor);
	}

	double Plane::Dot(Vector4 const& value) const {
		return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + (D * value.W));
	}

	double Plane::DotCoordinate(Vector3 const& value) const {
		return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + D);
	}

	double Plane::DotNormal(Vector3 const& value) const {
		return (((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z));
	}

	void Plane::Normalize() {
		Plane value = Plane::Normalize(*this);
		Normal = value.Normal;
		D = value.D;
	}

	PlaneIntersectionType Plane::Intersects(BoundingBox const& box) const {
		return box.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(BoundingFrustum const& frustum) const {
		return frustum.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(BoundingSphere const& sphere) const {
		return sphere.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(Vector3 const& point) const {
		double distance = DotCoordinate(point);

		if (distance > 0)
			return PlaneIntersectionType::Front;

		if (distance < 0)
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Intersecting;
	}

	void Plane::Deconstruct(Vector3& normal, double& d) const {
		normal = Normal;
		d = D;
	}

	bool Plane::Equals(Plane const& other) const {
		return (Normal == other.Normal) && D == other.D;
	}

	double  Plane::ClassifyPoint(Vector3 const& point, Plane const& plane) {
		return point.X * plane.Normal.X
			+ point.Y * plane.Normal.Y
			+ point.Z * plane.Normal.Z
			+ plane.D;
	}

	double  Plane::PerpendicularDistance(Vector3 const& point, Plane const& plane) {
		return std::abs((plane.Normal.X * point.X + plane.Normal.Y * point.Y + plane.Normal.Z * point.Z)
			/ std::sqrt(plane.Normal.X * plane.Normal.X + plane.Normal.Y * plane.Normal.Y + plane.Normal.Z * plane.Normal.Z));
	}
}