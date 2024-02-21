#pragma once

#include "../Template.h"



namespace Engine
{
	template<typename T> constexpr T Pi			= 3.14159265358979323846;	// The well-known 3.14159..
	template<typename T> constexpr T ToDegrees	= 180 / Pi<T>;				// Radians to degrees conversion constant
	template<typename T> constexpr T ToRadians	= 1 / ToDegrees<T>;			// Degrees to radians conversion constant

	constexpr RealType Epsilon = 1E-6; // A tiny value


	template<typename T> constexpr T Absolute(T value);
	template<typename T> constexpr T Clamp(T value, T minimum, T maximum);
	template<typename T> constexpr Bool IsPowerOfTwo(T value);
	template<typename T> constexpr T Lerp(T from, T to, RealType amount);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Maximum(First a, Second b, Parameters ...parameters);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Minimum(First a, Second b, Parameters ...parameters);
	template<typename First, typename Second, typename ...Parameters> constexpr auto Sum(First a, Second b, Parameters ...parameters);
	template<typename T> constexpr Int32 Sign(T value);
	template<typename T> Void Swap(T* a, T* b);


	ENGINE_API Bool Appropriate(RealType a, RealType b, RealType error = Epsilon);
	ENGINE_API RealType Clamp01(RealType value);
	ENGINE_API RealType Power(RealType base, RealType exponent);
	ENGINE_API RealType SquareRoot(RealType value);

	ENGINE_API RealType Sine(RealType radians);
	ENGINE_API RealType Cosine(RealType radians);
	ENGINE_API RealType Tangent(RealType radians);


#pragma region Details
	template<typename T>
	constexpr T Absolute(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < 0 ? -value : value;
	}

	template<typename T>
	constexpr T Clamp(T value, T minimum, T maximum)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < minimum ? minimum :
			value > maximum ? maximum : value;
	}

	template<typename T>
	constexpr Bool IsPowerOfTwo(T value)
	{
		static_assert( IsIntegral<T>::Value );

		
		if ( value == 0 )
			return false;

		return ( value & ( value - 1 ) ) == 0;
	}

	template<typename T>
	constexpr T Lerp(T from, T to, RealType amount)
	{
		static_assert( IsArithmetic<T>::Value );


		return from + static_cast<T>( ( to - from ) * amount );
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Maximum(First a, Second b, Parameters ...parameters)
	{
		static_assert( IsArithmetic<First>::Value && IsArithmetic<Second>::Value );


		auto ret = a > b ? a : b;
		if constexpr ( sizeof...(parameters) > 0 )
			return Maximum( ret, parameters... );

		return ret;
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Minimum(First a, Second b, Parameters ...parameters)
	{
		static_assert( IsArithmetic<First>::Value && IsArithmetic<Second>::Value );


		auto ret = a < b ? a : b;
		if constexpr ( sizeof...(parameters) > 0 )
			return Minimum( ret, parameters... );

		return ret;
	}

	template<typename First, typename Second, typename ...Parameters>
	constexpr auto Sum(First a, Second b, Parameters ...parameters)
	{
		static_assert( IsArithmetic<First>::Value && IsArithmetic<Second>::Value );


		auto ret = a + b;
		if constexpr ( sizeof...(parameters) > 0 )
			return Sum( ret, parameters... );

		return ret;
	}

	template<typename T>
	constexpr Int32 Sign(T value)
	{
		static_assert( IsArithmetic<T>::Value );


		return value < 0 ? -1 : 1;
	}

	template<typename T>
	Void Swap(T* a, T* b)
	{
		T temporary	= *a;
		*a			= *b;
		*b			= temporary;
	}
#pragma endregion
}