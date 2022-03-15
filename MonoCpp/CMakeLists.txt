# CMakeList.txt : CMake project for MonoGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (MonoGame "Main.cpp" "Main.h" "Rectangle.h" "Rectangle.cpp" "Point.h" "Point.cpp" "Vector2.h" "Vector2.cpp" "Matrix.h" "Matrix.cpp" "Quaternion.h" "Quaternion.cpp" "MathHelper.h" "MathHelper.cpp"  "Vector4.h" "Vector4.cpp" "Vector3.h" "Vector3.cpp" "Plane.h" "Plane.cpp" "PlaneIntersectionType.h" "BoundingBox.h" "BoundingBox.cpp" "ContainmentType.h"  "BoundingFrustum.h" "BoundingFrustum.cpp" "BoundingSphere.h" "BoundingSphere.cpp" "Ray.h" "Ray.cpp" "Color.h" "Color.cpp" "CSharp.h" "CurveTangent.h" "CurveLoopType.h" "CurveContinuity.h" "ICurveEvaluator.h" "CurveKey.h" "CurveKey.cpp" "CurveKeyCollection.h" "CurveKeyCollection.cpp" "Curve.h" "Curve.cpp" "DisplayOrientation.h" "PlayerIndex.h" "GameTime.h" "TimeSpan.h" "TimeSpan.cpp" "Input/Buttons.h" "Input/Keys.h" "Input/KeyboardState.h" "Input/KeyState.h" "Input/KeyboardState.cpp")

# TODO: Add tests and install targets if needed.
