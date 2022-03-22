#ifndef SDLGAMEWINDOW_H
#define SDLGAMEWINDOW_H

#include <string>
#include "../CSharp.h"
#include "../Rectangle.h"
#include <memory>
#include "../Point.h"
#include "../DisplayOrientation.h"
#include "../Input/MouseState.h"
#include "SDL.h"

namespace Xna {

	class Game;

	class GameWindow {

	private:
		std::string title;
		bool allowUserResizing;		
		std::unique_ptr<SDL_Window> window;

		void OnActivated();
		void OnDeactivated();
		void OnDeactivated();
		void OnOrientationChanged();
		void OnScreenDeviceNameChanged();
		void SetSupportedOrientations(DisplayOrientation orientations);
		void SetTitle(std::string title);

	public:

		GameWindow(Game game);

		bool AllowUserResizing();
		bool AllowUserResizing(bool value);
		bool AllowAltF4();
		Point Position();

		static GameWindow Create(Game game, i32 width, i32 height);

		Rectangle ClientBounds();
		DisplayOrientation CurrentOrientation();
		std::string ScreenDeviceName();
		//IntPtr Handle; //TO DO
		bool IsBorderless;
		MouseState MouseState;
		bool IsTextInputHandled();
		void BeginScreenDeviceChange(bool willBeFullScreen);
		void EndScreenDeviceChange(std::string screenDeviceName, i32 clientWidth, i32 clientHeight);
		void EndScreenDeviceChange(std::string screenDeviceName);
		void OnClientSizeChanged();
		//void OnTextInput(TextInputEventArgs e);
		//void OnKeyDown(InputKeyEventArgs e);
		//void OnKeyUp(InputKeyEventArgs e);
		//void OnFileDrop(FileDropEventArgs e);

		std::string Title();
		void Title(std::string value);		
	};
}

#endif // !GAMEWINDOW_H
