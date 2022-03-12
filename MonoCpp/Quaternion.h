#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>

namespace Xna {
	struct Matrix;
	struct Vector3;
	struct Vector4;


	// An efficient mathematical representation for three dimensional rotations.
	// C#: struct Quaternion
	struct Quaternion {
		double X;
		double Y;
		double Z;
		double W;

		Quaternion();
		Quaternion(double x, double y, double z, double w);
		Quaternion(Vector3 value, double w);
		Quaternion(Vector4 value);

		friend std::ostream& operator<< (std::ostream& os, Quaternion const& obj);
		Quaternion operator -(Quaternion quaternion);
		friend Quaternion operator +(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator /(Quaternion quaternion1, Quaternion quaternion2);
		friend bool operator ==(Quaternion quaternion1, Quaternion quaternion2);
		friend bool operator !=(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator *(Quaternion quaternion1, Quaternion quaternion2);
		friend Quaternion operator -(Quaternion quaternion1, Quaternion quaternion2);

		static Quaternion Identity();
		static Quaternion Add(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Concatenate(Quaternion const& value1, Quaternion const& value2);
		static Quaternion Conjugate(Quaternion const& value);
		static Quaternion CreateFromAxisAngle(Vector3 const& axis, double angle);
		static Quaternion CreateFromRotationMatrix(Matrix const& matrix);
		static Quaternion CreateFromYawPitchRoll(double yaw, double pitch, double roll);
		static Quaternion Divide(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static double Dot(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Inverse(Quaternion const& quaternion);
		static Quaternion Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount);
		static Quaternion Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, double amount);
		static Quaternion Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, double scaleFactor);
		static Quaternion Negate(Quaternion const& quaternion);
		static Quaternion Normalize(Quaternion const& quaternion);

		void Conjugate();
		double Length() const;
		double LengthSquared() const;
		void Normalize();
		Vector4 ToVector4() const;
		bool Equals(Quaternion const& other) const;
	};
}

#endif