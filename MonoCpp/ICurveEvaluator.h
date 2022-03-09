#ifndef ICURVE_EVALUATOR_H
#define ICURVE_EVALUATOR_H

namespace Xna {
	
	template<typename T>
	// Interface for curve evaluation. Implemented by Curve.
	struct ICurveEvaluator {
		
		// Evaluate the value at a position of this ICurveEvaluator{T}.
		virtual T Evaluate(double position) = 0;
	};
}

#endif