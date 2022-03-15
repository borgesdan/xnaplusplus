#include "KeyboardState.h"

namespace Xna {

	KeyboardState::KeyboardState() {}

	KeyboardState::KeyboardState(std::vector<Keys>& keys, bool capsLock = false, bool numLock = false) {
		_modifiers = static_cast<byte>(0 | (capsLock ? CapsLockModifier : 0) | (numLock ? NumLockModifier : 0));

		for (Keys const& k : keys) {
			InternalSetKey(k);
		}
	}

	bool KeyboardState::CapsLock() const {
		return (_modifiers & CapsLockModifier) > 0;
	}

	bool KeyboardState::NumLock() const {
		return (_modifiers & NumLockModifier) > 0;
	}

	KeyState KeyboardState::operator[] (Keys key) {
		return InternalGetKey(key) ? KeyState::Down : KeyState::Up;
	}

	bool operator ==(KeyboardState a, KeyboardState b) {
		return a.Equals(b);
	}

	bool operator !=(KeyboardState a, KeyboardState b) {
		return !a.Equals(b);
	}

	bool KeyboardState::IsKeyDown(Keys key) {
		return InternalGetKey(key);
	}

	bool KeyboardState::IsKeyUp(Keys key) {
		return !InternalGetKey(key);
	}

	int KeyboardState::GetPressedKeyCount() {
		u32 count = CountBits(_keys0) + CountBits(_keys1)
			+ CountBits(_keys2) + CountBits(_keys3)
			+ CountBits(_keys4) + CountBits(_keys5)
			+ CountBits(_keys6) + CountBits(_keys7);

		return (i32)count;
	}

	std::vector<Keys> KeyboardState::GetPressedKeys() {
		u32 count = CountBits(_keys0) + CountBits(_keys1)
			+ CountBits(_keys2) + CountBits(_keys3)
			+ CountBits(_keys4) + CountBits(_keys5)
			+ CountBits(_keys6) + CountBits(_keys7);

		if (count == 0) {
			return empty;
		}

		std::vector<Keys> keys(count);

		i32 index = 0;
		if (_keys0 != 0)
			index = AddKeysToArray(_keys0, 0 * 32, keys, index);

		if (_keys1 != 0)
			index = AddKeysToArray(_keys1, 1 * 32, keys, index);

		if (_keys2 != 0)
			index = AddKeysToArray(_keys2, 2 * 32, keys, index);

		if (_keys3 != 0)
			index = AddKeysToArray(_keys3, 3 * 32, keys, index);

		if (_keys4 != 0)
			index = AddKeysToArray(_keys4, 4 * 32, keys, index);

		if (_keys5 != 0)
			index = AddKeysToArray(_keys5, 5 * 32, keys, index);

		if (_keys6 != 0)
			index = AddKeysToArray(_keys6, 6 * 32, keys, index);

		if (_keys7 != 0)
			index = AddKeysToArray(_keys7, 7 * 32, keys, index);

		return keys;
	}

	void KeyboardState::GetPressedKeys(std::vector<Keys> keys) {

		u32 count = CountBits(_keys0) + CountBits(_keys1)
			+ CountBits(_keys2) + CountBits(_keys3)
			+ CountBits(_keys4) + CountBits(_keys5)
			+ CountBits(_keys6) + CountBits(_keys7);

		if (count > keys.size()) {
			return;
		}

		i32 index = 0;
		size_t size = keys.size();

		if (_keys0 != 0 && index < size)
			index = AddKeysToArray(_keys0, 0 * 32, keys, index);

		if (_keys1 != 0 && index < size)
			index = AddKeysToArray(_keys1, 1 * 32, keys, index);

		if (_keys2 != 0 && index < size)
			index = AddKeysToArray(_keys2, 2 * 32, keys, index);

		if (_keys3 != 0 && index < size)
			index = AddKeysToArray(_keys3, 3 * 32, keys, index);

		if (_keys4 != 0 && index < size)
			index = AddKeysToArray(_keys4, 4 * 32, keys, index);

		if (_keys5 != 0 && index < size)
			index = AddKeysToArray(_keys5, 5 * 32, keys, index);

		if (_keys6 != 0 && index < size)
			index = AddKeysToArray(_keys6, 6 * 32, keys, index);

		if (_keys7 != 0 && index < size)
			index = AddKeysToArray(_keys7, 7 * 32, keys, index);
	}

	void KeyboardState::InternalSetKey(Keys const& key) {
		u32 mask = static_cast<u32>(1) << (static_cast<i32>(key) & 0x1f);

		switch ((static_cast<i32>(key)) >> 5)
		{
		case 0:
			_keys0 |= mask;
			break;
		case 1:
			_keys1 |= mask;
			break;
		case 2:
			_keys2 |= mask;
			break;
		case 3:
			_keys3 |= mask;
			break;
		case 4:
			_keys4 |= mask;
			break;
		case 5:
			_keys5 |= mask;
			break;
		case 6:
			_keys6 |= mask;
			break;
		case 7:
			_keys7 |= mask;
			break;
		}
	}

	void KeyboardState::InternalClearKey(Keys const& key) {
		u32 mask = static_cast<u32>(1) << (static_cast<i32>(key) & 0x1f);
		
		switch (static_cast<i32>(key) >> 5)
		{
		case 0:
			_keys0 &= ~mask; 
			break;
		case 1:
			_keys1 &= ~mask;
			break;
		case 2: 
			_keys2 &= ~mask;
			break;
		case 3:
			_keys3 &= ~mask;
			break;
		case 4: 
			_keys4 &= ~mask;
			break;
		case 5: 
			_keys5 &= ~mask;
			break;
		case 6:
			_keys6 &= ~mask;
			break;
		case 7:
			_keys7 &= ~mask;
			break;
		}
	}

	void KeyboardState::InternalClearAllKeys() {
		_keys0 = 0;
		_keys1 = 0;
		_keys2 = 0;
		_keys3 = 0;
		_keys4 = 0;
		_keys5 = 0;
		_keys6 = 0;
		_keys7 = 0;
	}

	bool KeyboardState::Equals(KeyboardState const& other) const {
		return _keys0 == other._keys0
			&& _keys1 == other._keys1
			&& _keys2 == other._keys2
			&& _keys3 == other._keys3
			&& _keys4 == other._keys4
			&& _keys5 == other._keys5
			&& _keys6 == other._keys6
			&& _keys7 == other._keys7;
	}

	//----- Private
	u32 KeyboardState::CountBits(u32 v) {
		v = v - ((v >> 1) & 0x55555555);                    
		v = (v & 0x33333333) + ((v >> 2) & 0x33333333);     
		return ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
	}

	i32 KeyboardState::AddKeysToArray(u32 keys, i32 offset, std::vector<Keys>& pressedKeys, size_t index) {
		for (size_t i = 0; i < 32; i++)
		{
			if ((keys & (1 << i)) != 0) {
				pressedKeys[index++] = (Keys)(offset + i);
			}				
		}

		return index;
	}

	bool KeyboardState::InternalGetKey(Keys key) {
		u32 mask = static_cast<u32>(1) << (static_cast<i32>(key) & 0x1f);

		u32 element;
		switch (static_cast<i32>(key) >> 5)
		{
		case 0: 
			element = _keys0;
			break;
		case 1:
			element = _keys1;
			break;
		case 2:
			element = _keys2;
			break;
		case 3:
			element = _keys3; 
			break;
		case 4:
			element = _keys4; 
			break;
		case 5:
			element = _keys5; 
			break;
		case 6:
			element = _keys6; 
			break;
		case 7:
			element = _keys7; 
			break;
		default:
			element = 0; 
			break;
		}

		return (element & mask) != 0;
	}
}