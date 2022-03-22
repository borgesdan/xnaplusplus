#ifndef SPACE3D_H
#define SPACE3D_H

#include <vector>
#include "Structs.h"
#include "CSharp.h"

namespace Xna {

	struct BoundingBox;
	struct BoundingSphere;
	struct BoundingFrustum;
	struct Plane;

	//-------------------------------------------//
	//-----		$ ContainmentType			-----//	
	//-------------------------------------------//
	
	// Defines how the bounding volumes intersects or contain one another.
	enum class ContainmentType {
		//Indicates that there is no overlap between two bounding volumes.
		Disjoint,
		//Indicates that one bounding volume completely contains another volume.
		Contains,
		//Indicates that bounding volumes partially overlap one another.
		Intersects
	};

	//-------------------------------------------//
	//-----		$ PlaneIntersectionType		-----//	
	//-------------------------------------------//

	//Defines the intersection between a Plane and a bounding volume.
	enum class PlaneIntersectionType {
		//There is no intersection, the bounding volume is in the negative half space of the plane.
		Front,
		//There is no intersection, the bounding volume is in the positive half space of the plane.
		Back,
		//The plane is intersected.
		Intersecting
	};

	//-------------------------------//
	//-----		$ Ray			-----//	
	//-------------------------------//

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

	//-------------------------------//
	//-----		$ Plane			-----//	
	//-------------------------------//

	struct Plane {

		double D;
		Vector3 Normal;

		Plane();
		Plane(Vector4 value);
		Plane(Vector3 normal, double d);
		Plane(Vector3 a, Vector3 b, Vector3 c);
		Plane(double a, double b, double c, double d);
		Plane(Vector3 pointOnPlane, Vector3 normal);

		friend bool operator!= (Plane plane1, Plane plane2);
		friend bool operator== (Plane plane1, Plane plane2);

		static Plane Transform(Plane plane, Matrix matrix);
		static Plane Transform(Plane plane, Quaternion rotation);
		static Plane Normalize(Plane value);

		double Dot(Vector4 const& value) const;
		double DotCoordinate(Vector3 const& value) const;
		double DotNormal(Vector3 const& value) const;
		void Normalize();
		PlaneIntersectionType Intersects(BoundingBox const& box) const;
		PlaneIntersectionType Intersects(BoundingFrustum const& frustum) const;
		PlaneIntersectionType Intersects(BoundingSphere const& sphere) const;
		PlaneIntersectionType Intersects(Vector3 const& point) const;
		void Deconstruct(Vector3& normal, double& d) const;
		bool Equals(Plane const& other) const;

		//----- PlaneHelper internal class in Plane.cs

		// Returns a value indicating what side (positive/negative) of a plane a point is
		// point: The point to check with
		// plane: The plane to check against
		// Returns greater than zero if on the positive side, less than zero if on the negative size, 0 otherwise.
		static double ClassifyPoint(Vector3 const& point, Plane const& plane);

		// Returns the perpendicular distance from a point to a plane.	   
		// point: The point to check.
		// plane: The place to check.
		// The perpendicular distance from the point to the plane.
		static double PerpendicularDistance(Vector3 const& point, Plane const& plane);
	};	

	//-----------------------------------//
	//-----		$ BoundingFrustum	-----//	
	//-----------------------------------//

	struct BoundingFrustum {

		// The number of planes in the frustum.
		static constexpr i32 PlaneCount = 6;
		// The number of corner points in the frustum.
		static constexpr i32 CornerCount = 8;

		BoundingFrustum();

		// Constructs the frustum by extracting the view planes from a matrix.
		BoundingFrustum(Matrix value);

		friend bool operator ==(BoundingFrustum a, BoundingFrustum b);
		friend bool operator !=(BoundingFrustum a, BoundingFrustum b);

		// Gets or sets the Matrix of the frustum.
		Matrix Matrix_() const;
		// Sets or sets the Matrix of the frustum.
		void Matrix_(Matrix value);
		// Gets the near plane of the frustum.
		Plane Near() const;
		// Gets the far plane of the frustum.
		Plane Far() const;
		// Gets the left plane of the frustum.
		Plane Left() const;
		// Gets the right plane of the frustum.
		Plane Right() const;
		// Gets the top plane of the frustum.
		Plane Top() const;
		// Gets the bottom plane of the frustum.
		Plane Bottom() const;

		// Containment test between this BoundingFrustum and specified BoundingBox.
		ContainmentType Contains(BoundingBox const& box) const;
		// Containment test between this BoundingFrustum and specified BoundingFrustum.
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		// Containment test between this BoundingFrustum and specified BoundingSphere.
		ContainmentType Contains(BoundingSphere const& sphere) const;
		// Containment test between this BoundingFrustum and specified Vector3.
		ContainmentType Contains(Vector3 const& point) const;
		// Returns a copy of internal corners array.
		std::vector<Vector3> GetCorners() const;
		// Returns a copy of internal corners array.
		void GetCorners(std::vector<Vector3>& corners);
		// Gets whether or not a specified BoundingBox intersects with this BoundingFrustum.
		bool Intersects(BoundingBox const& box) const;
		// Gets whether or not a specified BoundingFrustum intersects with this BoundingFrustum.
		bool Intersects(BoundingFrustum const& frustum) const;
		// Gets whether or not a specified BoundingSphere intersects with this BoundingFrustum.
		bool Intersects(BoundingSphere const& sphere) const;
		// Gets type of intersection between specified Plane and this BoundingFrustum.
		PlaneIntersectionType Intersects(Plane const& plane) const;
		// Gets the distance of intersection of Ray and this BoundingFrustum or null if no intersection happens.
		// Returns the distance at which ray intersects with this BoundingFrustum or NaN if no intersection happens.</returns>
		// The original C# source code returns an object of type Nullable<float>
		double Intersects(Ray const& ray) const;

		// Compares whether current instance is equal to specified BoundingFrustum.
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

	//-----------------------------------//
	//-----		$ BoundingSphere	-----//	
	//-----------------------------------//

	// Describes a sphere in 3D-space for bounding operations.
	struct BoundingSphere {

		Vector3 Center;
		double Radius;

		BoundingSphere();
		BoundingSphere(Vector3 center, double radius);

		friend bool operator == (BoundingSphere a, BoundingSphere b);
		friend bool operator != (BoundingSphere a, BoundingSphere b);

		static BoundingSphere CreateFromFrustum(BoundingFrustum const& frustum);
		static BoundingSphere CreateFromPoints(std::vector<Vector3> const& points);
		static BoundingSphere CreateMerged(BoundingSphere const& original, BoundingSphere const& additional);
		static BoundingSphere CreateFromBoundingBox(BoundingBox const& box);

		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingSphere const& sphere) const;
		//bool Intersects(BoundingFrustum frustum);			//this code is not implemented in source code.
		PlaneIntersectionType Intersects(Plane const& plane) const;
		double Intersects(Ray const& ray) const;
		BoundingSphere Transform(Matrix const& matrix);

		void Deconstruct(Vector3& center, double& radius) const;
		bool Equals(BoundingSphere const& other) const;
	};

	//-------------------------------//
	//-----		$ BoundingBox	-----//	
	//-------------------------------//

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
		// Returns the distance along the Ray to the intersection point or
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