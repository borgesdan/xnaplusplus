#ifndef CURVE_LOOP_TYPE_H
#define CURVE_LOOP_TYPE_H

namespace Xna {
    
    // Defines how the Curve value is determined for position before first point or after the end point on the Curve.
	enum class CurveLoopType {
       
        // The value of Curve will be evaluated as first point for positions before the beginning and end point for positions after the end.        
        Constant,
        
        // The positions will wrap around from the end to beginning of the Curve for determined the value.        
        Cycle,
        
        // The positions will wrap around from the end to beginning of the Curve.
        // The value will be offset by the difference between the values of first and end CurveKey multiplied by the wrap amount.
        // If the position is before the beginning of the Curve the difference will be subtracted from its value; otherwise the difference will be added.        
        CycleOffset,
        
        // The value at the end of the Curve act as an offset from the same side of the Curve toward the opposite side.        
        Oscillate,
        
        // The linear interpolation will be performed for determined the value.         
        Linear
	};
}

#endif