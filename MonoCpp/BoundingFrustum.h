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

	// Defines a viewing frustum for intersection operations.
	struct BoundingFrustum {

		// The number of planes in the frustum.
		static constexpr long PlaneCount = 6;
		// The number of corner points in the frustum.
		static constexpr long CornerCount = 8;

		BoundingFrustum();

		// Constructs the frustum by extracting the view planes from a matrix.
		BoundingFrustum(Matrix value);

		friend std::ostream& operator<< (std::ostream& os, BoundingFrustum const& bf);
		friend bool operator ==(BoundingFrustum a, BoundingFrustum b);
		friend bool operator !=(BoundingFrustum a, BoundingFrustum b);

		// Gets or sets the Matrix of the frustum.
		constexpr Matrix Matrix_() const;
		// Sets or sets the Matrix of the frustum.
		void Matrix_(Matrix value);
		// Gets the near plane of the frustum.
		constexpr Plane Near() const;
		// Gets the far plane of the frustum.
		constexpr Plane Far() const;
		// Gets the left plane of the frustum.
		constexpr Plane Left() const;
		// Gets the right plane of the frustum.
		constexpr Plane Right() const;
		// Gets the top plane of the frustum.
		constexpr Plane Top() const;
		// Gets the bottom plane of the frustum.
		constexpr Plane Bottom() const;

		// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingBox"/>.
		ContainmentType Contains(BoundingBox const& box) const;
		// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingFrustum"/>.
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="BoundingSphere"/>.
		ContainmentType Contains(BoundingSphere const& sphere) const;
		// Containment test between this <see cref="BoundingFrustum"/> and specified <see cref="Vector3"/>.
		ContainmentType Contains(Vector3 const& point) const;
		// Returns a copy of internal corners array.
		std::vector<Vector3> GetCorners() const;
		// Returns a copy of internal corners array.
		void GetCorners(std::vector<Vector3>& corners);
		// Gets whether or not a specified <see cref="BoundingBox"/> intersects with this <see cref="BoundingFrustum"/>.
		bool Intersects(BoundingBox const& box) const;
		// Gets whether or not a specified <see cref="BoundingFrustum"/> intersects with this <see cref="BoundingFrustum"/>.
		bool Intersects(BoundingFrustum const& frustum) const;
		// Gets whether or not a specified <see cref="BoundingSphere"/> intersects with this <see cref="BoundingFrustum"/>.
		bool Intersects(BoundingSphere const& sphere) const;
		// Gets type of intersection between specified <see cref="Plane"/> and this <see cref="BoundingFrustum"/>.
		PlaneIntersectionType Intersects(Plane const& plane) const;
		// Gets the distance of intersection of <see cref="Ray"/> and this <see cref="BoundingFrustum"/> or null if no intersection happens.
		// Returns the distance at which ray intersects with this <see cref="BoundingFrustum"/> or NaN if no intersection happens.</returns>
		// The original C# source code returns an object of type Nullable<float>
		double Intersects(Ray const& ray) const;

		// Compares whether current instance is equal to specified <see cref="BoundingFrustum"/>.
		bool Equals(BoundingFrustum const& other);

	private:
		Matrix _matrix;
		std::vector<Vector3> _corners;
		std::vector<Plane> _planes;

		static Vector3 IntersectionPoint(Plane const& a, Plane const& b, Plane const& c);
		void NormalizePlane(Plane& p);

		void CreateCorners();
		void CreatePlanes();
	};
}

#endif
