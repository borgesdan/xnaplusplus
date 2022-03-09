#ifndef CURVE_KEY_H
#define CURVE_KEY_H

#include "CurveContinuity.h"

namespace Xna {

	// Key point on the Curve.
	class CurveKey {

		CurveContinuity _continuity;
		double _position;
		double _tangentIn;
		double _tangentOut;
		double _value;

	public:

		// Creates a new instance of CurveKey class.				
		CurveKey();

		// Creates a new instance of CurveKey class.		
		// position: Position on the curve.
		// value: Value of the control point.
		CurveKey(double position, double value);

		// Creates a new instance of CurveKey class.		
		// position: Position on the curve.
		// value: Value of the control point.
		// tangentIn: Tangent approaching point from the previous point on the curve.
		// tangentOut: Tangent leaving point toward next point on the curve.		
		CurveKey(double position, double value, double tangentIn, double tangentOut);
		

		// Creates a new instance of CurveKey class.		
		// position: Position on the curve.
		// value: Value of the control point.
		// tangentIn: Tangent approaching point from the previous point on the curve.
		// tangentOut: Tangent leaving point toward next point on the curve.
		// continuity: Indicates whether the curve is discrete or continuous.
		CurveKey(double position, double value, double tangentIn, double tangentOut, CurveContinuity continuity);

		friend bool operator ==(CurveKey value1, CurveKey value2);
		friend bool operator !=(CurveKey value1, CurveKey value2);

		// Gets the indicator whether the segment between this point and the next point on the curve is discrete or continuous.
		CurveContinuity Continuity() const;
		// Gets a position of the key on the curve.
		double Position() const;
		// Gets a tangent when approaching this point from the previous point on the curve.
		double TangentIn() const;
		// Gets a tangent when leaving this point to the next point on the curve.
		double TangentOut() const;
		// Gets a value of this point.
		double Value() const;
		//Sets the indicator whether the segment between this point and the next point on the curve is discrete or continuous.
		void Continuity(CurveContinuity value);
		// Sets a tangent when approaching this point from the previous point on the curve.
		void TangentIn(double value);
		// Sets a tangent when leaving this point to the next point on the curve.
		void TangentOut(double value);
		// Sets a value of this point.
		void Value(double value);

		// Creates a copy of this key.
		CurveKey Clone();
		
		int CurveKey::CompareTo(CurveKey other) const;
		bool Equals(CurveKey other) const;
	};
}

#endif