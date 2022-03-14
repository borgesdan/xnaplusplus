#include <limits>
#include "Ray.h"
#include "Plane.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "MathHelper.h"

namespace Xna {
    static double nan = std::numeric_limits<double>::quiet_NaN();

	Ray::Ray() : 
		Position(Vector3()), Direction(Vector3()) {}

	Ray::Ray(Vector3 position, Vector3 direction) :
		Position(position), Direction(direction) {}

    std::ostream& operator<< (std::ostream& os, Ray const& o) {
        return os << "{{Position:" << o.Position << " Direction:" << o.Direction << "}}";
    }
	
	bool operator !=(Ray a, Ray b) {
		return a.Equals(b);
	}

	bool operator ==(Ray a, Ray b) {
		return !a.Equals(b);
	}

	double Ray::Intersects(BoundingBox const& box) const {
        const double Epsilon = MathHelper::EPSILON;        

        double tMin = nan;
        double tMax = nan;

        if (std::abs(Direction.X) < Epsilon)
        {
            if (Position.X < box.Min.X || Position.X > box.Max.X)
                return nan;
        }
        else
        {
            tMin = (box.Min.X - Position.X) / Direction.X;
            tMax = (box.Max.X - Position.X) / Direction.X;

            if (tMin > tMax)
            {
                double temp = tMin;
                tMin = tMax;
                tMax = temp;
            }
        }

        if (std::abs(Direction.Y) < Epsilon)
        {
            if (Position.Y < box.Min.Y || Position.Y > box.Max.Y)
                return nan;
        }
        else
        {
            double tMinY = (box.Min.Y - Position.Y) / Direction.Y;
            double tMaxY = (box.Max.Y - Position.Y) / Direction.Y;

            if (tMinY > tMaxY)
            {
                double temp = tMinY;
                tMinY = tMaxY;
                tMaxY = temp;
            }

            //(tMin.HasValue && tMin > tMaxZ) || (tMax.HasValue && tMinZ > tMax)
            if ((!MathHelper::IsNan(tMin) && tMin > tMaxY) || (!MathHelper::IsNan(tMax) && tMinY > tMax))
                return nan;

            //!tMin.HasValue || tMinZ > tMin) tMin = tMinZ;
            if (MathHelper::IsNan(tMin) || tMinY > tMin) tMin = tMinY;
            //!tMax.HasValue || tMaxZ < tMax) tMax = tMaxZ;
            if (MathHelper::IsNan(tMax) || tMaxY < tMax) tMax = tMaxY;
        }

        if (std::abs(Direction.Z) < Epsilon)
        {
            if (Position.Z < box.Min.Z || Position.Z > box.Max.Z)
                return nan;
        }
        else
        {
            double tMinZ = (box.Min.Z - Position.Z) / Direction.Z;
            double tMaxZ = (box.Max.Z - Position.Z) / Direction.Z;

            if (tMinZ > tMaxZ)
            {
                double temp = tMinZ;
                tMinZ = tMaxZ;
                tMaxZ = temp;
            }

            if ((!MathHelper::IsNan(tMin) && tMin > tMaxZ) ||
                (!MathHelper::IsNan(tMax) && tMinZ > tMax))
                return nan;

            if (MathHelper::IsNan(tMin) || tMinZ > tMin) tMin = tMinZ;
            if (MathHelper::IsNan(tMax) || tMaxZ < tMax) tMax = tMaxZ;
        }

        // having a positive tMax and a negative tMin means the ray is inside the box
        // we expect the intesection distance to be 0 in that case
        if ((!MathHelper::IsNan(tMin) && tMin < 0) && tMax > 0) 
            return 0;

        // a negative tMin means that the intersection point is behind the ray's origin
        // we discard these as not hitting the AABB
        if (tMin < 0) 
            return nan;

        return tMin;
	};

    double Ray::Intersects(BoundingSphere const& sphere) const {
        
        Vector3 difference = sphere.Center - Position;

        double differenceLengthSquared = difference.LengthSquared();
        double sphereRadiusSquared = sphere.Radius * sphere.Radius;

        double distanceAlongRay = 0.0;        
        
        if (differenceLengthSquared < sphereRadiusSquared){
            return 0.0;
        }

        distanceAlongRay = Vector3::Dot(Direction, difference);
        
        if (distanceAlongRay < 0) {
            return nan;
        }
        
        float dist = sphereRadiusSquared + distanceAlongRay * distanceAlongRay - differenceLengthSquared;

        return (dist < 0) ? nan : distanceAlongRay - MathHelper::Sqrt(dist);
    }
   
    double Ray::Intersects(Plane const& plane) const {
        
        const double den = Vector3::Dot(Direction, plane.Normal);
        double result;

        if (std::abs(den) < 0.00001) {
            return nan;
        }

        result = (-plane.D - Vector3::Dot(plane.Normal, Position)) / den;

        if (result < 0.0f)
        {
            if (result < -0.00001f) {
                return nan;
            }

            result = 0.0f;
        }

        return result;
    }

    void Ray::Deconstruct(Vector3& position, Vector3& direction) const {
        position = Position;
        direction = Direction;
    }

    bool Ray::Equals(Ray const& other) const {
        return Position.Equals(other.Position) && Direction.Equals(other.Direction);
    }
}