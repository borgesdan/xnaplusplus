#ifndef CURVEKEY_COLLECTION_H
#define CURVEKEY_COLLECTION_H

#include <vector>
#include "CurveKey.h"
#include "CSharp.h"

namespace Xna {
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
}

#endif