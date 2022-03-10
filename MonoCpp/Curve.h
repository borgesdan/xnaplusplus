#ifndef CURVE_H
#define CURVE_H

#include "ICurveEvaluator.h"
#include "CurveLoopType.h"
#include "CurveKeyCollection.h"
#include "CurveTangent.h"

namespace Xna {
	
	class Curve : ICurveEvaluator<double> {

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
		double Evaluate(double position) override;
		void ComputeTangents(CurveTangent tangentType);
		void ComputeTangents(CurveTangent tangentInType, CurveTangent tangentOutType);
		void ComputeTangent(int keyIndex, CurveTangent tangentType);
		void ComputeTangent(int keyIndex, CurveTangent tangentInType, CurveTangent tangentOutType);

	private:
		long GetNumberOfCycle(double position);
		double GetCurvePosition(double position);
	};
}

#endif