#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

#include <vector>
#include "../CSharp.h"
#include "Keys.h"
#include "KeyState.h"

namespace Xna {

	struct KeyboardState {

		KeyboardState();
		KeyboardState(std::vector<Keys>& keys, bool capsLock = false, bool numLock = false);

		bool CapsLock() const;
		bool NumLock() const;

		KeyState operator[] (Keys key);
		friend bool operator ==(KeyboardState a, KeyboardState b);
		friend bool operator !=(KeyboardState a, KeyboardState b);

		bool IsKeyDown(Keys key);
		bool IsKeyUp(Keys key);
		int GetPressedKeyCount();
		std::vector<Keys> GetPressedKeys();
		void GetPressedKeys(std::vector<Keys> keys);

		void InternalSetKey(Keys const& key);
		void InternalClearKey(Keys const& key);
		void InternalClearAllKeys();
		bool Equals(KeyboardState const& other) const;

	private:
		static constexpr byte CapsLockModifier = 1;
		static constexpr byte NumLockModifier = 2;

		u32 _keys0{ 0 };
		u32 _keys1{ 0 };
		u32 _keys2{ 0 };
		u32 _keys3{ 0 };
		u32 _keys4{ 0 };
		u32 _keys5{ 0 };
		u32 _keys6{ 0 };
		u32 _keys7{ 0 };

		byte _modifiers;

		static u32 CountBits(u32 v);
		static i32 AddKeysToArray(u32 keys, i32 offset, std::vector<Keys>& pressedKeys, size_t index);

		bool InternalGetKey(Keys key);
	};
}

#endif