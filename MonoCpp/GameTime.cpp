#include "GameTime.h"

namespace Xna {
	GameTime::GameTime() :
		ElapsedGameTime(TimeSpan()),
		TotalGameTime(TimeSpan()),
		IsRunningSlowly(false) {}

	GameTime::GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, bool isRunningSlowly = false) :
		ElapsedGameTime(elapsedRealTime),
		TotalGameTime(totalRealTime),
		IsRunningSlowly(isRunningSlowly) {}
}