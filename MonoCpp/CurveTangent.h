#ifndef CURVE_TANGENT_H
#define CURVE_TANGENT_H

namespace Xna {

	// Defines the different tangent types to be calculated for CurveKey points in a Curve.
	enum class CurveTangent {
		
		// The tangent which always has a value equal to zero. 
		Flat,
		// The tangent which contains a difference between current tangent value and the tangent value from the previous CurveKey. 
		Linear,
		// The smoouth tangent which contains the inflection between CurveKey.
		//TangentIn and CurveKey.TangentOut by taking into account the values of both neighbors of the CurveKey.
		Smoth
	};
}

#endif