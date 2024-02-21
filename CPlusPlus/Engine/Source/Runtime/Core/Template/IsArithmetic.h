#pragma once

#include "ContainedFromParameterPack.h"



namespace Engine
{
	template<typename T>
	struct IsSignedIntegral : BoolConstant<ContainedFromParameterPack<T, Int8, Int16, Int32, Int64>::Value> { };


	template<typename T>
	struct IsUnsignedIntegral : BoolConstant<ContainedFromParameterPack<T, UInt8, UInt16, UInt32, UInt64>::Value> { };


	template<typename T>
	struct IsIntegral : BoolConstant<IsSignedIntegral<T>::Value || IsUnsignedIntegral<T>::Value> { };


	template<typename T>
	struct IsFloatPoint : BoolConstant<ContainedFromParameterPack<T, Float32, Float64>::Value> { };


	template<typename T>
	struct IsArithmetic : BoolConstant<IsIntegral<T>::Value || IsFloatPoint<T>::Value> { };
}