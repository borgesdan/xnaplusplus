#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <limits>
#include "CSharp.h" // unsigned char as byte

namespace Xna {

	struct Vector4;
	struct Vector3;

	struct Color {		

		Color(unsigned long packedValue);
		Color(Vector4 color);
		Color(Vector3 color);
		Color(Color color, long alpha);
		Color(Color color, double alpha);
		Color(double r, double g, double b);
		Color(double r, double g, double b, double alpha);
		Color(long r, long g, long b);
		Color(long r, long g, long b, long alpha);
		Color(byte r, byte g, byte b, byte alpha);

		friend std::ostream& operator<< (std::ostream& os, Color const& cl);
		friend bool operator ==(Color const& a, Color const& b);
		friend bool operator !=(Color const& a, Color const& b);
		friend Color operator *(Color const& value, double scale);
		friend Color operator *(double scale, Color value);		

		static Color Lerp(Color const& value1, Color const& value2, short amount);
		static Color LerpPrecise(Color const& value1, Color const& value2, short amount);
		static Color Multiply(Color const& value, double const& scale);
		static Color FromNonPremultiplied(Vector4 const& vector);
		static Color FromNonPremultiplied(long r, long g, long b, long a);

		byte R() const;
		byte R(byte value);
		byte G() const;
		byte G(byte value);
		byte B() const;
		byte B(byte value);
		byte A() const;
		byte A(byte value);

		Vector3 ToVector3() const;
		Vector4 ToVector4() const;
		long PackedValue() const;
		long PackedValue(long value);
		void Deconstruct(byte& r, byte& g, byte& b) const;
		void Deconstruct(byte& r, byte& g, byte& b, byte& a) const;
		void Deconstruct(double& r, double& g, double& b) const;
		void Deconstruct(double& r, double& g, double& b, double& a) const;
		bool Equals(Color const& other) const;

		static const Color Transparent;
		static const Color AliceBlue;
		static const Color AntiqueWhite;
		static const Color Aqua;
		static const Color Aquamarine;
		static const Color Azure;
		static const Color Beige;
		static const Color Bisque;
		static const Color Black;
		static const Color BlanchedAlmond;
		static const Color Blue;
		static const Color BlueViolet;
		static const Color Brown;
		static const Color BurlyWood;
		static const Color CadetBlue;
		static const Color Chartreuse;
		static const Color Chocolate;
		static const Color Coral;
		static const Color CornflowerBlue;
		static const Color Cornsilk;
		static const Color Crimson;
		static const Color Cyan;
		static const Color DarkBlue;
		static const Color DarkCyan;
		static const Color DarkGoldenrod;
		static const Color DarkGray;
		static const Color DarkGreen;
		static const Color DarkKhaki;
		static const Color DarkMagenta;
		static const Color DarkOliveGreen;
		static const Color DarkOrange;
		static const Color DarkOrchid;
		static const Color DarkRed;
		static const Color DarkSalmon;
		static const Color DarkSeaGreen;
		static const Color DarkSlateBlue;
		static const Color DarkSlateGray;
		static const Color DarkTurquoise;
		static const Color DarkViolet;
		static const Color DeepPink;
		static const Color DeepSkyBlue;
		static const Color DimGray;
		static const Color DodgerBlue;
		static const Color Firebrick;
		static const Color FloralWhite;
		static const Color ForestGreen;
		static const Color Fuchsia;
		static const Color Gainsboro;
		static const Color GhostWhite;
		static const Color Gold;
		static const Color Goldenrod;
		static const Color Gray;
		static const Color Green;
		static const Color GreenYellow;
		static const Color Honeydew;
		static const Color HotPink;
		static const Color IndianRed;
		static const Color Indigo;
		static const Color Ivory;
		static const Color Khaki;
		static const Color Lavender;
		static const Color LavenderBlush;
		static const Color LawnGreen;
		static const Color LemonChiffon;
		static const Color LightBlue;
		static const Color LightCoral;
		static const Color LightCyan;
		static const Color LightGoldenrodYellow;
		static const Color LightGray;
		static const Color LightGreen;
		static const Color LightPink;
		static const Color LightSalmon;
		static const Color LightSeaGreen;
		static const Color LightSkyBlue;
		static const Color LightSlateGray;
		static const Color LightSteelBlue;
		static const Color LightYellow;
		static const Color Lime;
		static const Color LimeGreen;
		static const Color Linen;
		static const Color Magenta;
		static const Color Maroon;
		static const Color MediumAquamarine;
		static const Color MediumBlue;
		static const Color MediumOrchid;
		static const Color MediumPurple;
		static const Color MediumSeaGreen;
		static const Color MediumSlateBlue;
		static const Color MediumSpringGreen;
		static const Color MediumTurquoise;
		static const Color MediumVioletRed;
		static const Color MidnightBlue;
		static const Color MintCream;
		static const Color MistyRose;
		static const Color Moccasin;
		static const Color MonoGameOrange;
		static const Color NavajoWhite;
		static const Color Navy;
		static const Color OldLace;
		static const Color Olive;
		static const Color OliveDrab;
		static const Color Orange;
		static const Color OrangeRed;
		static const Color Orchid;
		static const Color PaleGoldenrod;
		static const Color PaleGreen;
		static const Color PaleTurquoise;
		static const Color PaleVioletRed;
		static const Color PapayaWhip;
		static const Color PeachPuff;
		static const Color Peru;
		static const Color Pink;
		static const Color Plum;
		static const Color PowderBlue;
		static const Color Purple;
		static const Color Red;
		static const Color RosyBrown;
		static const Color RoyalBlue;
		static const Color SaddleBrown;
		static const Color Salmon;
		static const Color SandyBrown;
		static const Color SeaGreen;
		static const Color SeaShell;
		static const Color Sienna;
		static const Color Silver;
		static const Color SkyBlue;
		static const Color SlateBlue;
		static const Color SlateGray;
		static const Color Snow;
		static const Color SpringGreen;
		static const Color SteelBlue;
		static const Color Tan;
		static const Color Teal;
		static const Color Thistle;
		static const Color Tomato;
		static const Color Turquoise;
		static const Color Violet;
		static const Color Wheat;
		static const Color White;
		static const Color WhiteSmoke;
		static const Color Yellow;
		static const Color YellowGreen;

	private:
		unsigned long _packedValue;		

		long constructsColor(Color color, long alpha) {
			
			long cA = MathHelper::Clamp(alpha, std::numeric_limits<byte>::min(),
				std::numeric_limits<byte>::max());
			
			unsigned long clampedA = static_cast<long>(cA);

			if ((alpha & 0xFFFFFF00) != 0) {								

				_packedValue = (color._packedValue & 0x00FFFFFF) | (clampedA << 24);
			}
			else
			{
				_packedValue = (color._packedValue & 0x00FFFFFF) | (clampedA << 24);
			}
		}

		long constructsRGB(long r, long g, long b) {
			if (((r | g | b) & 0xFFFFFF00) != 0) {
				long _cr = MathHelper::Clamp(r, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());
				long _cg = MathHelper::Clamp(g, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());
				long _cb = MathHelper::Clamp(b, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());

				unsigned long clampedR = static_cast<unsigned long>(_cr);
				unsigned long clampedG = static_cast<unsigned long>(_cg);
				unsigned long clampedB = static_cast<unsigned long>(_cb);

				_packedValue |= (clampedB << 16) | (clampedG << 8) | (clampedR);
			}
			else
			{
				_packedValue = static_cast<unsigned long>(b << 16)
					| static_cast<unsigned long>(g << 8)
					| static_cast<unsigned long>(r);
			}
		}
		
		long constructsRGBA(long r, long g, long b, long alpha) {
			if (((r | g | b | alpha) & 0xFFFFFF00) != 0) {
				long _cr = MathHelper::Clamp(r, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());
				long _cg = MathHelper::Clamp(g, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());
				long _cb = MathHelper::Clamp(b, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());
				long _ca = MathHelper::Clamp(alpha, std::numeric_limits<byte>::min(), std::numeric_limits<byte>::max());

				unsigned long clampedR = static_cast<unsigned long>(_cr);
				unsigned long clampedG = static_cast<unsigned long>(_cg);
				unsigned long clampedB = static_cast<unsigned long>(_cb);
				unsigned long clampedA = static_cast<unsigned long>(_ca);

				_packedValue = (clampedA <<24)
					| (clampedB << 16)
					| (clampedG << 8)
					| (clampedR);
			}
			else
			{
				_packedValue = static_cast<unsigned long>(alpha << 24)
					| static_cast<unsigned long>(b << 16)
					| static_cast<unsigned long>(g << 8)
					| static_cast<unsigned long>(r);
			}
		}
	};
}

#endif