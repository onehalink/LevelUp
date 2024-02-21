#pragma once

#include "../../Core.h"



namespace Engine
{
	// Reference from https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	enum class Key
	{
		Backspace	= 0x08,
		Tab			= 0x09,
		Enter		= 0x0D,
		Shift		= 0x10,
		Control		= 0x11, // CTRL key
		Menu		= 0x12, // ALT key
		Escape		= 0x1B, // ESC key
		Space		= 0x20, // Spacebar key

		// arrow keys
		LeftArrow = 0x25,
		UpArrow,
		RightArrow,
		DownArrow,

		// 0 through 9 keys
		Alpha0 = 0x30,
		Alpha1,
		Alpha2,
		Alpha3,
		Alpha4,
		Alpha5,
		Alpha6,
		Alpha7,
		Alpha8,
		Alpha9,

		// A through Z keys
		A = 0x41,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		// 0 through 9 keys(numeric keypad)
		NumericKeypad0 = 0x60,
		NumericKeypad1,
		NumericKeypad2,
		NumericKeypad3,
		NumericKeypad4,
		NumericKeypad5,
		NumericKeypad6,
		NumericKeypad7,
		NumericKeypad8,
		NumericKeypad9,

		Count,
	};


	enum class KeyState
	{
		Press	= 1 << 0,
		Release	= 1 << 1,

		Click	= Press | Release,
	};
	ENABLE_BITWISE_OPERATORS(KeyState);
}