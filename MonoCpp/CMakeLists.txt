# CMakeList.txt : CMake project for MonoGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (MonoGame 
				 
				"CSharp.h" 
				"Curve.h" 
				"Structs.h" 
				"Space3d.h"
				"BoundingBox.cpp" 
				"BoundingFrustum.cpp" 
				"BoundingSphere.cpp" 
				"Color.h" 
				"Color.cpp" 				 
				"CSharp.cpp" 
				"Curve.cpp" 
				"CurveKey.cpp" 				 
				"CurveKeyCollection.cpp" 
				"DisplayOrientation.h" 
				"Game.h" 
				"GameRunBehavior.h" 
				"GameTime.h" 
				"GameTime.cpp" 
				"Main.cpp" 
				"Main.h" 
				"MathHelper.h" 
				"MathHelper.cpp" 
				"Matrix.cpp"
				"Plane.cpp" 
				"PlayerIndex.h" 				
				"Point.cpp" 				
				"Quaternion.cpp" 				
				"Ray.cpp"		
				"Rectangle.cpp" 				 
				"Vector2.cpp" 
				"Vector3.cpp" 
				"Vector4.cpp" 
				"Input/Buttons.h" 
				"Input/ButtonState.h" 
				"Input/Keys.h" 
				"Input/KeyState.h" 
				"Input/KeyboardState.h" 
				"Input/KeyboardState.cpp" 
				"Input/MouseState.h" 
				"Input/MouseState.cpp"				
				"Platform/SdlGamePlatform.h"				
				"Platform/SdlGamePlatform.cpp" 
				"Platform/SdlGameWindow.h" 
				"Platform/SdlGameWindow.cpp" 
				"Graphics/GraphicsDevice.h" 
				"Graphics/GraphicsDevice.cpp")

# TODO: Add tests and install targets if needed.
target_link_libraries(MonoGame ${SDL2_LIBRARIES})