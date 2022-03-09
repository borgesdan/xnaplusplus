#ifndef _CONTAINMENT_TYPE_H_
#define _CONTAINMENT_TYPE_H_

namespace Xna {

	// Defines how the bounding volumes intersects or contain one another.
	enum class ContainmentType {
		//Indicates that there is no overlap between two bounding volumes.
		Disjoint,
		//Indicates that one bounding volume completely contains another volume.
		Contains,
		//Indicates that bounding volumes partially overlap one another.
		Intersects
	};
}

#endif
