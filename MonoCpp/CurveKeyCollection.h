#ifndef CURVEKEY_COLLECTION_H
#define CURVEKEY_COLLECTION_H

#include <vector>
#include "CurveKey.h"

namespace Xna {
	class CurveKeyCollection {

		std::vector<CurveKey> _keys;		

	public:
		CurveKeyCollection();		

		size_t Count() const;
		bool IsReadOnly() const;

		//IEnumerator IEnumerable.GetEnumerator()		
		CurveKey Get(int index) const;
		void Set(int index, CurveKey value);
		void Add(CurveKey const& item);
		void Clear();
		CurveKeyCollection Clone() const;
		bool Contains(CurveKey item);
		void CopyTo(std::vector<CurveKey>& vec, int vecIndex) const;
		//IEnumerator<CurveKey> GetEnumerator()
		int IndexOf(CurveKey item);
		void RemoveAt(int index);
		bool Remove(CurveKey item);

		//std::vector<CurveKey>& GetList();
		std::vector<CurveKey>::const_iterator Begin() const;
		std::vector<CurveKey>::const_iterator End() const;
	};
}

#endif