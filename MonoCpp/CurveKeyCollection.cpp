#include "Curve.h"

namespace Xna {
	CurveKeyCollection::CurveKeyCollection(){}

	// Members
	size_t CurveKeyCollection::Count() const {
		return _keys.size();
	}

	bool CurveKeyCollection::IsReadOnly() const {
		return false;
	}

	CurveKey& CurveKeyCollection::Get(size_t index) {
		return _keys[index];
	}

	void CurveKeyCollection::Set(size_t index, CurveKey value) {
		if (index >= _keys.size())
			return;

		if (_keys[index].Position() == value.Position()) {
			_keys[index] = value;
		}			
		else {
			std::vector<CurveKey>::iterator it = _keys.begin();
			_keys.erase(it + index);			
			_keys.insert(it + index, value);
		}
	}

	void CurveKeyCollection::Add(CurveKey const& item) {
		
		if (_keys.size() == 0)
		{
			_keys.push_back(item);
			return;
		}

		for (i32 i = 0; i < _keys.size(); i++)
		{
			if (item.Position() < _keys[i].Position())
			{
				std::vector<CurveKey>::iterator it = _keys.begin();
				_keys.insert(it + i, item);
				return;
			}
		}

		_keys.push_back(item);
	}

	void CurveKeyCollection::Clear() {
		_keys.clear();
	}

	CurveKeyCollection CurveKeyCollection::Clone() const {
		return CurveKeyCollection((*this));
	}

	bool CurveKeyCollection::Contains(CurveKey item) {
		return std::find(_keys.begin(), _keys.end(), item) != _keys.end();
		//return false;
	}

	void CurveKeyCollection::CopyTo(std::vector<CurveKey>& vec, i32 vecIndex) const {
		for ( ; vecIndex < _keys.size(); vecIndex++) {
			vec.push_back(_keys[vecIndex]);
		}
	}

	i32 CurveKeyCollection::IndexOf(CurveKey item) {
		for (size_t i = 0; i < _keys.size(); i++) {
			if (item == _keys[i]) {
				return static_cast<i32>(i);
			}
		}

		return -1;
	}

	void CurveKeyCollection::RemoveAt(i32 index) {
		std::vector<CurveKey>::iterator it = _keys.begin();
		_keys.erase(it + index);
	}

	bool CurveKeyCollection::Remove(CurveKey item) {
		for (size_t i = 0; i < _keys.size(); i++) {
			if (item == _keys[i]) {
				RemoveAt(static_cast<i32>(i));
				return true;
			}
		}

		return false;
	}

	std::vector<CurveKey>::const_iterator CurveKeyCollection::Begin() const {
		return _keys.begin();
	}
	std::vector<CurveKey>::const_iterator CurveKeyCollection::End() const {
		return _keys.end();
	}
}