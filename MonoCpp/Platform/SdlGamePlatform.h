#ifndef SDLGAMEPLATFORM_H
#define SDLGAMEPLATFORM_H

#include <vector>
#include <string>
#include "../CSharp.h"
#include "../GameRunBehavior.h"
#include "../GameTime.h"
#include "../Input/Keys.h"

namespace Xna {

	class Game;
	class GameWindow;
	class SdlGameWindow;
	class PresentationParameters;

	class GamePlatform {

	private:
		bool _isActive;
		bool _isMouseVisible;
		GameWindow _window;

		const Game _game;
		const std::vector<Keys> _keys;
		i32 _isExiting;
		SdlGameWindow _view;

		void SdlRunLoop();

	public:
		GamePlatform(Game game);

		static GamePlatform PlatformCreate(Game _game);

		GameRunBehavior DefaultRunBehavior();
		Game Game();
		bool IsActive();
		bool IsMouseVisible();
		GameWindow Window();
		void BeforeInitialize();
		void BeforeRun();
		void Exit();
		void RunLoop();
		void StartRunLoop();
		bool BeforeUpdate(GameTime gameTime);
		bool BeforeDraw(GameTime gameTime);
		void EnterFullScreen();
		void ExitFullScreen();
		TimeSpan TargetElapsedTimeChanging(TimeSpan value);
		void BeginScreenDeviceChange(bool willBeFullScreen);
		void EndScreenDeviceChange(string screenDeviceName, i32 clientWidth, i32 clientHeight);
		void TargetElapsedTimeChanged();
		void ResetElapsedTime();
		void Present();
		void OnPresentationChanged(PresentationParameters pp);

	protected:
		constexpr TimeSpan _inactiveSleepTime = TimeSpan::FromMilliseconds(20.0);
		constexpr bool _needsToResetElapsedTime = false;
		constexpr bool InFullScreenMode = false;

		void RaiseAsyncRunLoopEnded();
		void OnIsMouseVisibleChanged();
	};
}

#endif