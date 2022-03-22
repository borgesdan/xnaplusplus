#include <cmath>
#include "Curve.h"

namespace Xna {
	CurveKey::CurveKey():
		_position(0),
		_value(0),
		_tangentIn(0),
		_tangentOut(0),
		_continuity(CurveContinuity::Smooth) {}

	CurveKey::CurveKey(double position, double value):
		_position(position),
		_value(value),
		_tangentIn(0),
		_tangentOut(0),
		_continuity(CurveContinuity::Smooth) {}

	CurveKey::CurveKey(double position, double value, double tangentIn, double tangentOut):
		_position(position),
		_value(value),
		_tangentIn(tangentIn),
		_tangentOut(tangentOut),
		_continuity(CurveContinuity::Smooth) {}

	CurveKey::CurveKey(double position, double value, double tangentIn, double tangentOut, CurveContinuity continuity) :
		_position(position),
		_value(value),
		_tangentIn(tangentIn),
		_tangentOut(tangentOut),
		_continuity(continuity){}

	// Operators
	bool operator ==(CurveKey value1, CurveKey value2) {
		return value1.Equals(value2);
	}

	bool operator !=(CurveKey value1, CurveKey value2) {
		return !value1.Equals(value2);
	}

	// Members

	CurveContinuity CurveKey::Continuity() const {
		return _continuity;
	}

	double CurveKey::Position() const {
		return _position;
	}
	 
	double CurveKey::TangentIn() const {
		return _tangentIn;
	}

	double CurveKey::TangentOut() const {
		return _tangentOut;
	}

	double CurveKey::Value() const {
		return _value;
	}

	void CurveKey::Continuity(CurveContinuity value) {
		_continuity = value;
	}

	void CurveKey::TangentIn(double value) {
		_tangentIn = value;
	}

	void CurveKey::TangentOut(double value) {
		_tangentOut = value;
	}

	void CurveKey::Value(double value) {
		_value = value;
	}

	CurveKey CurveKey::Clone() {
		return CurveKey(_position, _value, _tangentIn, _tangentOut, _continuity);
	}

	i32 CurveKey::CompareTo(CurveKey other) const {
		if (_position < other._position) return -1;
		if (_position > other._position) return 1;
		if (_position == other._position) return 0;

		// At least one of the values is NaN.
		if (std::isnan(_position)) {
			return (std::isnan(other._position) ? 0 : - 1);
		}
		else {
			return 1;
		}
	}

	bool CurveKey::Equals(CurveKey other) const {
		return _position == other._position
			&& _value == other._value
			&& _tangentIn == other._tangentIn
			&& _tangentOut == other._tangentOut
			&& _continuity == other._continuity;
	}
}