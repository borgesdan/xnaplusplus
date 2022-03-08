#include <numeric>
#include <stdexcept>
#include <cmath>

#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "BoundingSphere.h"
#include "Plane.h"
#include "Ray.h"

namespace Xna {

	BoundingSphere::BoundingSphere() {}
	BoundingSphere::BoundingSphere(Vector3 center, double radius):
		Center(center), Radius(radius){}

	// Operators

    std::ostream& operator<< (std::ostream& os, BoundingSphere const& bs) {
        return os << "{Center:" << bs.Center << " Radius:" << bs.Radius << "}";
    }

    bool operator == (BoundingSphere a, BoundingSphere b) {
        return a.Equals(b);
    }

    bool operator != (BoundingSphere a, BoundingSphere b) {
        return !a.Equals(b);
    }

	// Static
	BoundingSphere BoundingSphere::CreateFromFrustum(BoundingFrustum const& frustum) {
		return CreateFromPoints(frustum.GetCorners());
	}

	BoundingSphere BoundingSphere::CreateFromPoints(std::vector<Vector3> const& points)
            throw(std::invalid_argument) {

        //if (points == null)
        //    throw new ArgumentNullException("points");

        // From "Real-Time Collision Detection" (Page 89)

        Vector3 minx = Vector3(std::numeric_limits<double>::max());

        Vector3 maxx = -minx;
        Vector3 miny = minx;
        Vector3 maxy = -minx;
        Vector3 minz = minx;
        Vector3 maxz = -minx;

        // Find the most extreme points along the principle axis.
        long numPoints = 0;

        for (const Vector3 pt : points) {

            ++numPoints;

            if (pt.X < minx.X)
                minx = pt;
            if (pt.X > maxx.X)
                maxx = pt;
            if (pt.Y < miny.Y)
                miny = pt;
            if (pt.Y > maxy.Y)
                maxy = pt;
            if (pt.Z < minz.Z)
                minz = pt;
            if (pt.Z > maxz.Z)
                maxz = pt;
        }

        if (numPoints == 0) {
            throw std::invalid_argument("You should have at least one point in points.");
        }            

        double sqDistX = Vector3::DistanceSquared(maxx, minx);
        double sqDistY = Vector3::DistanceSquared(maxy, miny);
        double sqDistZ = Vector3::DistanceSquared(maxz, minz);

        // Pick the pair of most distant points.
        Vector3 min = minx;
        Vector3 max = maxx;

        if (sqDistY > sqDistX && sqDistY > sqDistZ) {
            max = maxy;
            min = miny;
        }

        if (sqDistZ > sqDistX && sqDistZ > sqDistY) {
            max = maxz;
            min = minz;
        }

        Vector3 center = (min + max) * 0.5f;
        double radius = Vector3::Distance(max, center);

        // Test every point and expand the sphere.
        // The current bounding sphere is just a good approximation and may not enclose all points.            
        // From: Mathematics for 3D Game Programming and Computer Graphics, Eric Lengyel, Third Edition.
        // Page 218
        float sqRadius = radius * radius;

        for (const Vector3 pt : points) {
            Vector3 diff = (pt - center);
            float sqDist = diff.LengthSquared();
            if (sqDist > sqRadius)
            {
                float distance = std::sqrt(sqDist); // equal to diff.Length();
                Vector3 direction = diff / distance;
                Vector3 G = center - radius * direction;
                center = (G + pt) / 2;
                radius = Vector3::Distance(pt, center);
                sqRadius = radius * radius;
            }
        }       

        return BoundingSphere(center, radius);
	}

    BoundingSphere BoundingSphere::CreateMerged(BoundingSphere const& original, BoundingSphere const& additional) {
        
        BoundingSphere result;
        Vector3 ocenterToaCenter = Vector3::Subtract(additional.Center, original.Center);
        float distance = ocenterToaCenter.Length();

        if (distance <= original.Radius + additional.Radius)//intersect
        {
            if (distance <= original.Radius - additional.Radius)//original contain additional
            {
                result = original;
                return;
            }
            if (distance <= additional.Radius - original.Radius)//additional contain original
            {
                result = additional;
                return;
            }
        }
        //else find center of new sphere and radius        
        double leftRadius = std::fmax(original.Radius - distance, additional.Radius);
        double Rightradius = std::fmax(original.Radius + distance, additional.Radius);
        ocenterToaCenter = ocenterToaCenter + (((leftRadius - Rightradius) 
            / (2 * ocenterToaCenter.Length())) 
            * ocenterToaCenter);//oCenterToResultCenter

        result.Center = original.Center + ocenterToaCenter;
        result.Radius = (leftRadius + Rightradius) / 2;

        return result;
    }

    BoundingSphere BoundingSphere::CreateFromBoundingBox(BoundingBox const& box) {

        // Find the center of the box.
        Vector3 center = Vector3((box.Min.X + box.Max.X) / 2.0f,
            (box.Min.Y + box.Max.Y) / 2.0f,
            (box.Min.Z + box.Max.Z) / 2.0f);

        // Find the distance between the center and one of the corners of the box.
        double radius = Vector3::Distance(center, box.Max);

        return BoundingSphere(center, radius);
    }

	// Members

    ContainmentType BoundingSphere::Contains(BoundingBox const& box) const {
        //check if all corner is in sphere
        bool inside = true;
        for(Vector3 corner : box.GetCorners()) {
            if (Contains(corner) == ContainmentType::Disjoint) {
                inside = false;
                break;
            }
        }

        if (inside) {
            return ContainmentType::Contains;
        }            

        //check if the distance from sphere center to cube face < radius
        double dmin = 0;

        if (Center.X < box.Min.X)
            dmin += (Center.X - box.Min.X) * (Center.X - box.Min.X);

        else if (Center.X > box.Max.X)
            dmin += (Center.X - box.Max.X) * (Center.X - box.Max.X);

        if (Center.Y < box.Min.Y)
            dmin += (Center.Y - box.Min.Y) * (Center.Y - box.Min.Y);

        else if (Center.Y > box.Max.Y)
            dmin += (Center.Y - box.Max.Y) * (Center.Y - box.Max.Y);

        if (Center.Z < box.Min.Z)
            dmin += (Center.Z - box.Min.Z) * (Center.Z - box.Min.Z);

        else if (Center.Z > box.Max.Z)
            dmin += (Center.Z - box.Max.Z) * (Center.Z - box.Max.Z);

        if (dmin <= Radius * Radius) {
            return ContainmentType::Intersects;
        }            

        //else disjoint
        return ContainmentType::Disjoint;
    }

    ContainmentType BoundingSphere::Contains(BoundingFrustum const& frustum) const {
        bool inside = true;
        auto corners = frustum.GetCorners();

        for(Vector3 corner : corners) {
            if (Contains(corner) == ContainmentType::Disjoint) {
                inside = false;
                break;
            }
        }
        if (inside)
            return ContainmentType::Contains;

        //check if the distance from sphere center to frustrum face < radius
        double dmin = 0;

        if (dmin <= Radius * Radius)
            return ContainmentType::Intersects;

        //else disjoint
        return ContainmentType::Disjoint;
    }
    
    ContainmentType BoundingSphere::Contains(BoundingSphere const& sphere) const {
        
        ContainmentType result;
        double sqDistance = Vector3::DistanceSquared(sphere.Center, Center);

        if (sqDistance > (sphere.Radius + Radius) * (sphere.Radius + Radius)) {
            result = ContainmentType::Disjoint;
        }
        else if (sqDistance <= (Radius - sphere.Radius) * (Radius - sphere.Radius)) {
            result = ContainmentType::Contains;
        }
        else {
            result = ContainmentType::Intersects;
        }

        return result;
    }
   
    ContainmentType BoundingSphere::Contains(Vector3 const& point) const {
        ContainmentType result;

        double sqRadius = Radius * Radius;
        double sqDistance = Vector3::DistanceSquared(point, Center);

        if (sqDistance > sqRadius) {
            result = ContainmentType::Disjoint;
        }
        else if (sqDistance < sqRadius) {
            result = ContainmentType::Contains;
        }
        else {
            result = ContainmentType::Intersects;
        }
            
        return result;
    }

    bool BoundingSphere::Intersects(BoundingBox const& box) const {
        return box.Intersects((*this));
    }

    bool BoundingSphere::Intersects(BoundingSphere const& sphere) const {
        bool result;

        double sqDistance = Vector3::DistanceSquared(sphere.Center, Center);

        if (sqDistance > (sphere.Radius + Radius) * (sphere.Radius + Radius))
            result = false;
        else
            result = true;

        return result;
    }

    PlaneIntersectionType BoundingSphere::Intersects(Plane const& plane) const {
        PlaneIntersectionType result;

        double distance = Vector3::Dot(plane.Normal, Center);        
        distance += plane.D;

        if (distance > Radius) {
            result = PlaneIntersectionType::Front;
        }            
        else if (distance < -Radius) {
            result = PlaneIntersectionType::Back;
        }            
        else {
            result = PlaneIntersectionType::Intersecting;
        }
            
        return result;
    }

    double BoundingSphere::Intersects(Ray const& ray) const {
        return ray.Intersects((*this));
    }

    BoundingSphere BoundingSphere::Transform(Matrix const& matrix) {
        BoundingSphere sphere;
        sphere.Center = Vector3::Transform(Center, matrix);
        sphere.Radius = Radius * std::sqrt(std::fmax(((matrix.M11 * matrix.M11) + (matrix.M12 * matrix.M12)) + (matrix.M13 * matrix.M13),
                std::fmax(((matrix.M21 * matrix.M21) + (matrix.M22 * matrix.M22)) + (matrix.M23 * matrix.M23), 
                ((matrix.M31 * matrix.M31) + (matrix.M32 * matrix.M32)) + (matrix.M33 * matrix.M33))));
        return sphere;
    }

    void BoundingSphere::Deconstruct(Vector3& center, double& radius) const{
        center = Center;
        radius = Radius;
    }
    
    bool BoundingSphere::Equals(BoundingSphere const& other) const {
        return Center == other.Center && Radius == other.Radius;
    }
}