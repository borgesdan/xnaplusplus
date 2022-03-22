#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "CSharp.h"

namespace Xna {

	// Defines the continuity of keys on a Curve.
	enum class CurveContinuity {
		// Interpolation can be used between this key and the next.
		Smooth,
		// Interpolation cannot be used. A position between the two points returns this point.
		Step
	};
	
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

	// Defines the different tangent types to be calculated for CurveKey points in a Curve.
	enum class CurveTangent {

		// The tangent which always has a value equal to zero. 
		Flat,
		// The tangent which contains a difference between current tangent value and the tangent value from the previous CurveKey. 
		Linear,
		// The smoouth tangent which contains the inflection between CurveKey.
		//TangentIn and CurveKey.TangentOut by taking into account the values of both neighbors of the CurveKey.
		Smooth
	};

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

		i32 CurveKey::CompareTo(CurveKey other) const;
		bool Equals(CurveKey other) const;
	};

	class CurveKeyCollection {

		std::vector<CurveKey> _keys;

	public:
		CurveKeyCollection();

		size_t Count() const;
		bool IsReadOnly() const;

		//IEnumerator IEnumerable.GetEnumerator()		
		CurveKey& Get(size_t index);
		void Set(size_t index, CurveKey value);
		void Add(CurveKey const& item);
		void Clear();
		CurveKeyCollection Clone() const;
		bool Contains(CurveKey item);
		void CopyTo(std::vector<CurveKey>& vec, i32 vecIndex) const;
		//IEnumerator<CurveKey> GetEnumerator()
		i32 IndexOf(CurveKey item);
		void RemoveAt(i32 index);
		bool Remove(CurveKey item);

		//std::vector<CurveKey>& GetList();
		std::vector<CurveKey>::const_iterator Begin() const;
		std::vector<CurveKey>::const_iterator End() const;
	};
	
	class Curve {

		CurveLoopType _preLoop;
		CurveLoopType _postLoop;
		CurveKeyCollection _keys;

	public:

		Curve();

		bool IsConstant() const;
		CurveLoopType PreLoop() const;
		void PreLoop(CurveLoopType value);
		CurveLoopType PostLoop() const;
		void PostLoop(CurveLoopType value);
		CurveKeyCollection& Keys();

		Curve Clone() const;
		double Evaluate(double position);
		void ComputeTangents(CurveTangent tangentType);
		void ComputeTangents(CurveTangent tangentInType, CurveTangent tangentOutType);
		void ComputeTangent(size_t keyIndex, CurveTangent tangentType);
		void ComputeTangent(size_t keyIndex, CurveTangent tangentInType, CurveTangent tangentOutType);

	private:
		i32 GetNumberOfCycle(double position);
		double GetCurvePosition(double position);
	};
}

#endif