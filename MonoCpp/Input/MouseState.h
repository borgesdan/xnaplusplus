#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include "../CSharp.h"
#include "../Point.h"
#include "ButtonState.h"

namespace Xna {
	struct MouseState {

        MouseState();       

        MouseState(i32 x, i32 y, i32 scrollWheel, ButtonState leftButton, ButtonState middleButton,
            ButtonState rightButton, ButtonState xButton1, ButtonState xButton2, i32 horizontalScroolWheel = 0);
        
        friend bool operator ==(MouseState left, MouseState right);
        friend bool operator !=(MouseState left, MouseState right);       

        i32 X() const;
        i32 Y() const;
        Point Position() const;
        ButtonState LeftButton() const;
        ButtonState MiddleButton() const;
        ButtonState RightButton() const;
        ButtonState X1() const;
        ButtonState X2() const;
        i32 ScrollWheelValue() const;
        i32 HorizontalScrollWheelValue() const;
        void X(i32 value);
        void Y(i32 value);
        void LeftButton(ButtonState value);
        void MiddleButton(ButtonState value);
        void RightButton(ButtonState value);
        void X1(ButtonState value);
        void X2(ButtonState value);
        void ScrollWheelValue(i32 value);
        void HorizontalScrollWheelValue(i32 value);
        bool Equals(MouseState other) const;

	private:
         static constexpr byte LeftButtonFlag = 1;
         static constexpr byte RightButtonFlag = 2;
         static constexpr byte MiddleButtonFlag = 4;
         static constexpr byte XButton1Flag = 8;
         static constexpr byte XButton2Flag = 16;

         i32 _x;
         i32 _y;
         i32 _scrollWheelValue;
         i32 _horizontalScrollWheelValue;
         byte _buttons;
	};
}

#endif