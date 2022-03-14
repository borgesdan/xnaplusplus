#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <vector>
#include "ContainmentType.h"
#include "PlaneIntersectionType.h"
#include "Vector3.h"

namespace Xna {

	struct BoundingSphere;
	struct BoundingFrustum;
	struct Ray;
	struct Plane;

	// Represents an axis-aligned bounding box (AABB) in 3D space.
	struct BoundingBox {

		//The number of corners in a BoundingBox. This is equal to 8.
		static constexpr i32 CornerCount = 8;

		// The minimum extent of this BoundingBox.
		Vector3 Min;
		//The maximum extent of this BoundingBox.
		Vector3 Max;

		//Create a BoundingBox
		BoundingBox();
		//Create a BoundingBox with the minimum and the maxmum extent.
		BoundingBox(Vector3 min, Vector3 max);

		friend bool operator ==(BoundingBox a, BoundingBox b);
		friend bool operator !=(BoundingBox a, BoundingBox b);

		// Create a bounding box from the given list of points.
		// points: The array of Vector3 instances defining the point cloud to bound.
		// index: The base index to start iterating from.
		// count: The number of points to iterate.
		static BoundingBox CreateFromPoints(std::vector<Vector3> const& points, i32 index = 0, i32 count = -1);

		// Create the enclosing BoundingBox of a BoundingSphere.
		static BoundingBox CreateFromSphere(BoundingSphere const& sphere);

		// Create the BoundingBox enclosing two other BoundingBox instances.
		static BoundingBox CreateMerged(BoundingBox const& original, BoundingBox const& additional);

		// Check if this BoundingBox contains another BoundingBox.		
		ContainmentType Contains(BoundingBox const& box) const;
		// Check if this BoundingBox contains a BoundingFrustum.
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		// Check if this BoundingBox contains a BoundingSphere.
		ContainmentType Contains(BoundingSphere const& sphere) const;
		// Check if this BoundingBox contains a Vector3.
		ContainmentType Contains(Vector3 const& point) const;

		// Get an array of Vector3 containing the corners of this BoundingBox.
		std::vector<Vector3> GetCorners() const;

		// Fill the first 8 places of an array of Vector3"
		// with the corners of this BoundingBox.
		void GetCorners(std::vector<Vector3>& corners) const;

		// Check if this BoundingBox intersects another BoundingBox.
		bool Intersects(BoundingBox const& box) const;

		// Check if this BoundingBox intersects a BoundingFrustum.
		bool Intersects(BoundingFrustum const& frustum) const;

		// Check if this BoundingBox intersects a BoundingSphere.
		bool Intersects(BoundingSphere const& sphere) const;

		// Check if this BoundingBox intersects a Plane.		
		PlaneIntersectionType Intersects(Plane const& plane) const;

		// Check if this BoundingBox intersects a Ray.
		// Returns the distance along the <see cref="Ray"/> to the intersection point or
		// NaN if the Ray does not intesect this BoundingBox.
		// The original C# source code returns an object of type Nullable<float>
		double Intersects(Ray ray) const;

		//Deconstruction method for BoundingBox.
		void Deconstruct(Vector3& min, Vector3& max) const;

		bool Equals(BoundingBox const& other) const;


	private:
		static const Vector3 MaxVector3;
		static const Vector3 MinVector3;
	};
}

#endif
