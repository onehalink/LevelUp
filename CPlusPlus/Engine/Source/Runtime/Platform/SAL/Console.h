#pragma once

#include "../HAL/Keyboard.h"



namespace Engine
{
	class Console;


	extern ENGINE_API Console StandardInput;
	extern ENGINE_API Console StandardOutput;
	extern ENGINE_API Console StandardError;


	class ENGINE_API Console
	{
	public:
		enum class Color
		{
			Red		= 1 << 2,
			Green	= 1 << 1,
			Blue	= 1 << 0,

			Black	= 0,
			White	= Red | Green | Blue,
		};
		CLASS_ENUMCLASS_FLAGS(Color);


		NONCOPYABLE(Console);


		Console();
		Console(Void* handle);
		~Console();

		
		Void SetCursorPosition(SizeType x, SizeType y);
		Void SetAsActive();
		Void SetColor(Color foreground, Color background);

		DynamicArray<Key> ReadInputKeys();

		Void Clear();
		Void Write(const U8String& text);


		SizeType GetWidth() const;
		SizeType GetHeight() const;
	private:
		Void* handle;

		SizeType width;		// Characters in row
		SizeType height;	// Characters in column
	};
}