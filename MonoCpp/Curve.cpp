#include <cmath>
#include <numeric>
#include "Curve.h"

namespace Xna {
	Curve::Curve():
    _preLoop(CurveLoopType::Constant), _postLoop(CurveLoopType::Constant) {}

	// Members
	bool Curve::IsConstant() const {
		return _keys.Count() <= 1;
	}

	CurveLoopType Curve::PreLoop() const {
		return _preLoop;
	}

	void Curve::PreLoop(CurveLoopType value) {
		_preLoop = value;
	}

	CurveLoopType Curve::PostLoop() const {
		return _postLoop;
	}

	void Curve::PostLoop(CurveLoopType value) {
		_postLoop = value;
	}

	CurveKeyCollection& Curve::Keys() {
		return _keys;
	}

	Curve Curve::Clone() const {
		Curve curve;
		curve._keys = _keys.Clone();
		curve._preLoop = _preLoop;
		curve._postLoop = _postLoop;

		return curve;
	}

	double Curve::Evaluate(double position) {
        if (_keys.Count() == 0) {
            return 0.;
        }

        if (_keys.Count() == 1) {
            return _keys.Get(0).Value();
        }

        CurveKey first = _keys.Get(0);
        CurveKey last = _keys.Get(_keys.Count() - 1);
        i32 cycle = GetNumberOfCycle(position);
        double virtualPos = 0.0;

        if (position < first.Position()) {
            switch (_preLoop)
            {
            case CurveLoopType::Constant:                
                return first.Value();

            case CurveLoopType::Linear:                
                return first.Value() - first.TangentIn() * (first.Position() - position);

            case CurveLoopType::Cycle:                                
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);

            case CurveLoopType::CycleOffset:                                
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return (GetCurvePosition(virtualPos) + cycle * (last.Value() - first.Value()));

            case CurveLoopType::Oscillate:                                
                if (0 == cycle % 2) {
                    virtualPos = position - (cycle * (last.Position() - first.Position()));
                }                    
                else {
                    virtualPos = last.Position() - position + first.Position() + (cycle * (last.Position() - first.Position()));
                }
                    
                return GetCurvePosition(virtualPos);
            }
        }
        else if (position > last.Position())
        {
            i32 cycle = 0;
            switch (_postLoop)
            {
            case CurveLoopType::Constant:                
                return last.Value();

            case CurveLoopType::Linear:                
                return last.Value() + first.TangentOut() * (position - last.Position());

            case CurveLoopType::Cycle:                
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);

            case CurveLoopType::CycleOffset:                                
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return (GetCurvePosition(virtualPos) + cycle * (last.Value() - first.Value()));

            case CurveLoopType::Oscillate:                                
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                if (0 == cycle % 2)
                    virtualPos = position - (cycle * (last.Position() - first.Position()));
                else
                    virtualPos = last.Position() - position + first.Position() + (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);
            }
        }

        //in curve
        return GetCurvePosition(position);
	}

    void Curve::ComputeTangents(CurveTangent tangentType) {
        ComputeTangents(tangentType, tangentType);
    }

    void Curve::ComputeTangents(CurveTangent tangentInType, CurveTangent tangentOutType) {
        
        for (i32 i = 0; i < _keys.Count(); ++i) {
            ComputeTangent(i, tangentInType, tangentOutType);
        }
    }
    void Curve::ComputeTangent(size_t keyIndex, CurveTangent tangentType) {
        ComputeTangent(keyIndex, tangentType, tangentType);
    }

    void Curve::ComputeTangent(size_t keyIndex, CurveTangent tangentInType, CurveTangent tangentOutType) {
        CurveKey &key = _keys.Get(keyIndex);

        double p0;
        double p;
        double p1;
        p0 = p = p1 = key.Position();

        double v0;
        double v;
        double v1;
        v0 = v = v1 = key.Value();

        if (keyIndex > 0)
        {
            p0 = _keys.Get(keyIndex - 1).Position();
            v0 = _keys.Get(keyIndex - 1).Value();
        }

        if (keyIndex < _keys.Count() - 1)
        {
            p1 = _keys.Get(keyIndex + 1).Position();
            v1 = _keys.Get(keyIndex + 1).Value();
        }

        switch (tangentInType)
        {
        case CurveTangent::Flat:
            key.TangentIn(0);
            break;
        case CurveTangent::Linear:
            key.TangentIn(v - v0);
            break;
        case CurveTangent::Smooth:
            double pn = p1 - p0;
            if (std::abs(pn) < std::numeric_limits<double>::epsilon())
                key.TangentIn(0);
            else
                key.TangentIn((v1 - v0) * ((p - p0) / pn));
            break;
        }

        switch (tangentOutType)
        {
        case CurveTangent::Flat:
            key.TangentOut(0);
            break;
        case CurveTangent::Linear:
            key.TangentOut(v1 - v);
            break;
        case CurveTangent::Smooth:
            double pn = p1 - p0;
            if (std::abs(pn) < std::numeric_limits<double>::epsilon())
                key.TangentOut(0);
            else
                key.TangentOut((v1 - v0) * ((p1 - p) / pn));
            break;
        }
    }

    // Private
        // Members

    i32 Curve::GetNumberOfCycle(double position) {
        double cycle = (position - _keys.Get(0).Position())
            / (_keys.Get(_keys.Count() - 1).Position() - _keys.Get(0).Position());
        
        if (cycle < 0.) {
            cycle--;
        }
            
        return static_cast<i32>(cycle);
    }

    double Curve::GetCurvePosition(double position) {
        CurveKey prev = _keys.Get(0);
        CurveKey next;

        for (i32 i = 1; i < _keys.Count(); ++i) {
            next = _keys.Get(i);

            if (next.Position() >= position)
            {
                if (prev.Continuity() == CurveContinuity::Step)
                {
                    if (position >= 1.)
                    {
                        return next.Value();
                    }
                    return prev.Value();
                }
                double t = (position - prev.Position()) / (next.Position() - prev.Position());//to have t in [0,1]
                double ts = t * t;
                double tss = ts * t;
                
                return (2 * tss - 3 * ts + 1.) * prev.Value() + (tss - 2 * ts + t) * prev.TangentOut() + (3 * ts - 2 * tss) * next.Value() + (tss - ts) * next.TangentIn();
            }
            prev = next;
        }
        
        return 0.;
    }
}