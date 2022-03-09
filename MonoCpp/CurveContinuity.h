#ifndef CURVE_CONTINUITY_H
#define CURVE_CONTINUITY_H

namespace Xna {
	
	// Defines the continuity of keys on a Curve.
	enum class CurveContinuity {
		// Interpolation can be used between this key and the next.
		Smooth,
		// Interpolation cannot be used. A position between the two points returns this point.
		Step
	};
}

#endif