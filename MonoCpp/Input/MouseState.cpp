#include "MouseState.h"

namespace Xna {
	MouseState::MouseState() :
		_x(0), _y(0), _scrollWheelValue(0), _horizontalScrollWheelValue(0), _buttons(0) {}

	MouseState::MouseState(i32 x, i32 y, i32 scrollWheel, ButtonState leftButton, ButtonState middleButton,
		ButtonState rightButton, ButtonState xButton1, ButtonState xButton2, i32 horizontalScroolWheel) :
		_x(0),
		_y(0),
		_scrollWheelValue(scrollWheel),
		_horizontalScrollWheelValue(horizontalScroolWheel) {

		_buttons = static_cast<byte>(
			(leftButton == ButtonState::Pressed ? LeftButtonFlag : 0) |
			(rightButton == ButtonState::Pressed ? RightButtonFlag : 0) |
			(middleButton == ButtonState::Pressed ? MiddleButtonFlag : 0) |
			(xButton1 == ButtonState::Pressed ? XButton1Flag : 0) |
			(xButton2 == ButtonState::Pressed ? XButton2Flag : 0)
			);
	}

	bool operator ==(MouseState left, MouseState right) {
		return left.Equals(right);
	}

	bool operator !=(MouseState left, MouseState right) {
		return !left.Equals(right);
	}

	i32 MouseState::X() const { return _x; }
	
	i32 MouseState::Y() const { return _y; }
	
	Point MouseState::Position() const { return Point(_x, _y); }
	
	ButtonState MouseState::LeftButton() const {
		return ((_buttons & LeftButtonFlag) > 0) ? ButtonState::Pressed : ButtonState::Released; 
	}

	ButtonState MouseState::MiddleButton() const {
		return ((_buttons & MiddleButtonFlag) > 0) ? ButtonState::Pressed : ButtonState::Released;
	}

	ButtonState MouseState::RightButton() const {
		return ((_buttons & RightButtonFlag) > 0) ? ButtonState::Pressed : ButtonState::Released;
	}

	ButtonState MouseState::X1() const {
		return ((_buttons & XButton1Flag) > 0) ? ButtonState::Pressed : ButtonState::Released;
	}
	ButtonState MouseState::X2() const {
		return ((_buttons & XButton2Flag) > 0) ? ButtonState::Pressed : ButtonState::Released;
	}
	
	i32 MouseState::ScrollWheelValue() const { return _scrollWheelValue; }

	i32 MouseState::HorizontalScrollWheelValue() const { return _horizontalScrollWheelValue; }

	void MouseState::X(i32 value) {
		_x = value;
	}

	void MouseState::Y(i32 value) {
		_y = value;
	}

	void MouseState::LeftButton(ButtonState value) {
		if (value == ButtonState::Pressed) {
			_buttons = (byte)(_buttons | LeftButtonFlag);
		}
		else {
			_buttons = (byte)(_buttons & (~LeftButtonFlag));
		}
	}

	void MouseState::MiddleButton(ButtonState value) {
		if (value == ButtonState::Pressed) {
			_buttons = (byte)(_buttons | MiddleButtonFlag);
		}
		else {
			_buttons = (byte)(_buttons & (~MiddleButtonFlag));
		}
	}

	void MouseState::RightButton(ButtonState value) {
		if (value == ButtonState::Pressed) {
			_buttons = (byte)(_buttons | RightButtonFlag);
		}
		else {
			_buttons = (byte)(_buttons & (~RightButtonFlag));
		}
	}

	void MouseState::X1(ButtonState value) {
		if (value == ButtonState::Pressed) {
			_buttons = (byte)(_buttons | XButton1Flag);
		}
		else
		{
			_buttons = (byte)(_buttons & (~XButton1Flag));
		}
	}

	void MouseState::X2(ButtonState value) {
		if (value == ButtonState::Pressed) {
			_buttons = (byte)(_buttons | XButton2Flag);
		}
		else
		{
			_buttons = (byte)(_buttons & (~XButton2Flag));
		}
	}

	void MouseState::ScrollWheelValue(i32 value) {
		_scrollWheelValue = value;
	}

	void MouseState::HorizontalScrollWheelValue(i32 value) {
		_horizontalScrollWheelValue = value;
	}

	bool MouseState::Equals(MouseState other) const {
		return 
			_x == other._x &&
			_y == other._y &&
			_buttons == other._buttons &&
			_scrollWheelValue == other._scrollWheelValue &&
			_horizontalScrollWheelValue == other._horizontalScrollWheelValue;
	}
}