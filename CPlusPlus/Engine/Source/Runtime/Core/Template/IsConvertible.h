#pragma once

#include "IntegralConstant.h"



namespace Engine
{
	// Test if a type(From) could be converted to the other(To)
	template<typename From, typename To>
	struct IsConvertible : BoolConstant<__is_convertible_to(From, To)> { };
}