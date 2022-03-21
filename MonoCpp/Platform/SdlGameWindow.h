#ifndef SDLGAMEWINDOW_H
#define SDLGAMEWINDOW_H

#include <string>
#include "../CSharp.h"
#include "../Rectangle.h"
#include "../Point.h"
#include "../DisplayOrientation.h"
#include "../Input/MouseState.h"

namespace Xna {

	class Game;

	class GameWindow {
		string _title;

	public:
		bool AllowUserResizing;
		bool AllowAltF4;
		Point Position;

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

		string Title();
		void Title(string value);

	protected:
		void OnActivated();
		void OnDeactivated();
		void OnDeactivated();
		void OnOrientationChanged();
		void OnScreenDeviceNameChanged();
		void SetSupportedOrientations(DisplayOrientation orientations);
		void SetTitle(string title);
	};
}

#endif // !GAMEWINDOW_H
