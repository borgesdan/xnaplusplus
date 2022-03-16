#ifndef GAMETIME_H
#define GAMETIME_H

#include "TimeSpan.h"

namespace Xna {

	// Holds the time state of a Game.
	// C#: GameTime is a reference type.
	class GameTime {

	public:

		TimeSpan TotalGameTime;
		TimeSpan ElapsedGameTime;
		bool IsRunningSlowly;

		GameTime();		
		GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, bool isRunningSlowly);	
	};

}

#endif