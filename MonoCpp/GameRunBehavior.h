#ifndef GAMERUNBEHAVIOR_H
#define GAMERUNBEHAVIOR_H

namespace Xna {

    // Defines how Game should be runned.
	enum class GameRunBehavior {
        
        // The game loop will be runned asynchronous.
        Asynchronous,
        
        // The game loop will be runned synchronous.
        Synchronous
	};
}

#endif