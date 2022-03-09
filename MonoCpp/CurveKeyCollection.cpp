#include <algorithm>
#include "CurveKeyCollection.h"

namespace Xna {
	CurveKeyCollection::CurveKeyCollection(){}

	// Members
	size_t CurveKeyCollection::Count() const {
		return _keys.size();
	}

	bool CurveKeyCollection::IsReadOnly() const {
		return false;
	}

	CurveKey CurveKeyCollection::Get(int index) const {
		return _keys[index];
	}

	void CurveKeyCollection::Set(int index, CurveKey value) {
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

		for (int i = 0; i < _keys.size(); i++)
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
		//https://www.techiedelight.com/check-vector-contains-given-element-cpp/
		return std::find(_keys.begin(), _keys.end(), _keys.size()) != _keys.end();
	}

	void CurveKeyCollection::CopyTo(std::vector<CurveKey>& vec, int vecIndex) const {
		for ( ; vecIndex < _keys.size(); vecIndex++) {
			vec.push_back(_keys[vecIndex]);
		}
	}

	int CurveKeyCollection::IndexOf(CurveKey item) {
		for (int i = 0; i < _keys.size(); i++) {
			if (item == _keys[i]) {
				return i;
			}
		}
	}

	void CurveKeyCollection::RemoveAt(int index) {
		std::vector<CurveKey>::iterator it = _keys.begin();
		_keys.erase(it + index);
	}

	bool CurveKeyCollection::Remove(CurveKey item) {
		for (int i = 0; i < _keys.size(); i++) {
			if (item == _keys[i]) {
				RemoveAt(i);
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