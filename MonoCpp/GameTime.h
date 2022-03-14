#ifndef GAMETIME_H
#define GAMETIME_H

#include "TimeSpan.h"

namespace Xna {

	// Holds the time state of a Game.
	// C#: GameTime is a reference type.
	class GameTime {

	public:

		GameTime();
		GameTime(TimeSpan totalGameTime, TimeSpan elapsedGameTime);
		GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, bool isRunningSlowly);

		TimeSpan TotalGameTime();
		TimeSpan TotalGameTime(TimeSpan const& value);

		TimeSpan ElapsedGameTime();
		TimeSpan ElapsedGameTime(TimeSpan const& value);

		bool IsRunningSlowly();
		bool IsRunningSlowly(bool value);
	};

}

#endif