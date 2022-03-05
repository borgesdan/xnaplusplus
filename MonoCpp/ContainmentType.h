#ifndef _CONTAINMENT_TYPE_H_
#define _CONTAINMENT_TYPE_H_

namespace Xna {

	// Defines how the bounding volumes intersects or contain one another.
	// Disjoint: Indicates that there is no overlap between two bounding volumes.
	// Contains: Indicates that one bounding volume completely contains another volume.
	// Intersects: Indicates that bounding volumes partially overlap one another.
	enum class ContainmentType {
		Disjoint,
		Contains,
		Intersects
	};
}

#endif
