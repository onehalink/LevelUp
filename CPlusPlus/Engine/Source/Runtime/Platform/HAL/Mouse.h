#pragma once

#include "Keyboard.h"



namespace Engine
{
	enum class MouseButton
	{
		Left	= 0x01,
		Right	= 0x02,
		Middle	= 0x10,

		Count,
	};


	using MouseButtonState = KeyState;
}