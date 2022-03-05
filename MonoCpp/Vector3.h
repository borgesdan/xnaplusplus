#include <iostream>

namespace Xna{	

	struct Vector3 {
		double X;
		double Y;
		double Z;

		Vector3();
		Vector3(double, double, double);
		Vector3(double value);

		Vector3 operator- ();
		Vector3 operator+ ();

		friend std::ostream& operator<< (std::ostream& os, Vector3 const& vec);
		friend Vector3 operator- (Vector3, Vector3);
		friend Vector3 operator+ (Vector3, Vector3);
		friend Vector3 operator* (Vector3, Vector3);
		friend bool operator< (double, Vector3);
		friend bool operator> (double, Vector3);
		friend bool operator>= (Vector3, Vector3);
		friend bool operator<= (Vector3, Vector3);
		friend bool operator&& (Vector3, Vector3);
		friend bool operator== (Vector3, Vector3);
		friend bool operator!= (Vector3, Vector3);

		static Vector3 Multiply(Vector3, Vector3);
		static Vector3 Multiply(Vector3, double);
		static Vector3 Cross(Vector3, Vector3);
		static double Dot(Vector3, Vector3);
		
		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Right();
		static Vector3 Left();
		static Vector3 Forward();
		static Vector3 Normalize(Vector3);

		void Normalize();
		double LengthSquared();
	};
}