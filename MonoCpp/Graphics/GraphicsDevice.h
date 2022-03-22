#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

class Viewport;

namespace Xna {
	class GraphicsDevice {

	private:
		Viewport _viewport;

	public:
		bool UseHalfPixelOffset;
	};
}

#endif
