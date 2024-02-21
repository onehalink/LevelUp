#include "Math.h"

#include <cmath>



namespace Engine
{
	Bool Appropriate(RealType a, RealType b, RealType error)
	{
		return Absolute( a - b ) < error;
	}

	RealType Clamp01(RealType value)
	{
		return Clamp<RealType>(value, 0, 1);
	}

	RealType Power(RealType base, RealType exponent)
	{
		return std::pow(base, exponent);
	}

	RealType SquareRoot(RealType value)
	{
		//return std::sqrt(value);

		/**
		* F(x)	= x^2 - y
		* F'(x) = 2x
		* 
		* F(x)'s tangential equation about point(x0, F(x0)):
		* y - y0 = k(x - x0)
		* 
		* x0: initial value(user defined)
		* 
		* y0	= F(x0)
		* k		= F'(x0)
		* 
		* Required:
		* x == ?? when y = 0
		* 
		* Iteration Formula:
		* x = x0 - y0 / k
		*/


		constexpr RealType x0 = 1;


		RealType x		= x0;
		RealType last	= 0;
		while (true)
		{
			x = x - ( x * x - value ) / ( 2 * x );

			if ( Absolute( x - last ) < Epsilon )
				return x;

			last = x;
		}
	}

	RealType Sine(RealType radians)
	{
		return std::sin(radians);
	}

	RealType Cosine(RealType radians)
	{
		return std::cos(radians);
	}

	RealType Tangent(RealType radians)
	{
		return std::tan(radians);
	}
}