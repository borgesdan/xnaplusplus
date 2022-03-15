#ifndef BUTTONS_H
#define BUTTONS_H

#include "../CSharp.h"

namespace Xna {

	enum class Buttons : u32 {
        
        // Directional pad up.        
        DPadUp = 1,
        
        // Directional pad down.        
        DPadDown = 2,
        
        // Directional pad left.        
        DPadLeft = 4,
        
        // Directional pad right.        
        DPadRight = 8,
        
        // START button.        
        Start = 16,
        
        // BACK button.        
        Back = 32,
        
        // Left stick button (pressing the left stick).        
        LeftStick = 64,
        
        // Right stick button (pressing the right stick).        
        RightStick = 128,
        
        // Left bumper (shoulder) button.        
        LeftShoulder = 256,
        
        // Right bumper (shoulder) button.        
        RightShoulder = 512,
        
        // Big button.            
        BigButton = 2048,
        
        // A button.        
        A = 4096,
        
        // B button.        
        B = 8192,
        
        // X button.        
        X = 16384,
        
        // Y button.        
        Y = 32768,
        
        // Left stick is towards the left.        
        LeftThumbstickLeft = 2097152,
        
        // Right trigger.        
        RightTrigger = 4194304,
        
        // Left trigger.        
        LeftTrigger = 8388608,

        
        // Right stick is towards up.           
        RightThumbstickUp = 16777216,
        
        // Right stick is towards down.           
        RightThumbstickDown = 33554432,

        
        // Right stick is towards the right.        
        RightThumbstickRight = 67108864,
        
        // Right stick is towards the left.        
        RightThumbstickLeft = 134217728,

        
        // Left stick is towards up.          
        LeftThumbstickUp = 268435456,
        
        // Left stick is towards down.          
        LeftThumbstickDown = 536870912,

        
        // Left stick is towards the right.        
        LeftThumbstickRight = 1073741824
	};
}

#endif
