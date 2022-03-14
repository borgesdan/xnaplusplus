#ifndef CURVE_H
#define CURVE_H

#include "CurveLoopType.h"
#include "CurveKeyCollection.h"
#include "CurveTangent.h"
#include "CSharp.h"

namespace Xna {
	
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