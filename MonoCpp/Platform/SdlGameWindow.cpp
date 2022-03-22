#include "SdlGameWindow.h"

namespace Xna {
	
	GameWindow::GameWindow() {
		window = std::unique_ptr< SDL_Window>(SDL_CreateWindow("", 0, 0, 0, 0, 0));
	}

	bool GameWindow::AllowUserResizing() {
		return allowUserResizing;
	}

	bool GameWindow::AllowUserResizing(bool value) {
		if (SDL_PATCHLEVEL > 4) {
			
		}
	}
}