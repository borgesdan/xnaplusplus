#ifndef _PLANE_INTERSECTION_TYPE_H_
#define _PLANE_INTERSECTION_TYPE_H_

namespace Xna {

	//Defines the intersection between a Plane and a bounding volume.
	//Front: There is no intersection, the bounding volume is in the negative half space of the plane.
	//Back: There is no intersection, the bounding volume is in the positive half space of the plane.
	//Intersectin: The plane is intersected.
	enum class PlaneIntersectionType {
		Front,
		Back,
		Intersecting
	};
}

#endif