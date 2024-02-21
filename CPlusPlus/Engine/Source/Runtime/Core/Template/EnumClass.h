#pragma once

#include "EnumUnderlyingType.h"



namespace Engine
{
	#define ENABLE_BITWISE_OPERATORS(EnumClass)		template<> struct EnableBitwiseOperators<EnumClass> : TrueType { }


	/**
	* As a flag to disable/enable bitwise operators(&, |, ^ and ~) for enum class
	* 
	* 
	* @remark
	* default is disable, and use macro ENABLE_BITWISE_OPERATORS to enable
	*/
	template<typename EnumClass>
	struct EnableBitwiseOperators : FalseType { };


	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator&(EnumClass leftHandSide, EnumClass rightHandSide);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator|(EnumClass leftHandSide, EnumClass rightHandSide);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator^(EnumClass leftHandSide, EnumClass rightHandSide);
	template<typename EnumClass> constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator~(EnumClass instance);

	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator&=(EnumClass& leftHandSide, EnumClass rightHandSide);
	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator|=(EnumClass& leftHandSide, EnumClass rightHandSide);
	template<typename EnumClass> typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator^=(EnumClass& leftHandSide, EnumClass rightHandSide);


#pragma region Details
	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator&(EnumClass leftHandSide, EnumClass rightHandSide)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(leftHandSide) & static_cast<UnderlyingType>(rightHandSide) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator|(EnumClass leftHandSide, EnumClass rightHandSide)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(leftHandSide) | static_cast<UnderlyingType>(rightHandSide) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator^(EnumClass leftHandSide, EnumClass rightHandSide)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( static_cast<UnderlyingType>(leftHandSide) ^ static_cast<UnderlyingType>(rightHandSide) );
	}

	template<typename EnumClass>
	constexpr typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type operator~(EnumClass instance)
	{
		using UnderlyingType = EnumUnderlyingType<EnumClass>;


		return EnumClass( ~static_cast<UnderlyingType>(instance) );
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator&=(EnumClass& leftHandSide, EnumClass rightHandSide)
	{
		leftHandSide = leftHandSide & rightHandSide;

		return leftHandSide;
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator|=(EnumClass& leftHandSide, EnumClass rightHandSide)
	{
		leftHandSide = leftHandSide | rightHandSide;

		return leftHandSide;
	}

	template<typename EnumClass>
	typename EnableIf<EnableBitwiseOperators<EnumClass>::Value, EnumClass>::Type& operator^=(EnumClass& leftHandSide, EnumClass rightHandSide)
	{
		leftHandSide = leftHandSide ^ rightHandSide;

		return leftHandSide;
	}
#pragma endregion
}