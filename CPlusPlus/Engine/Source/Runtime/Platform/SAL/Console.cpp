#include "Console.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	#if defined(PLATFORM_WINDOWS)
	extern Console StandardInput	= { GetStdHandle(STD_INPUT_HANDLE) };
	extern Console StandardOutput	= { GetStdHandle(STD_OUTPUT_HANDLE) };
	extern Console StandardError	= { GetStdHandle(STD_ERROR_HANDLE) };
	#else
	#error StandardInput, StandardOutput and StandardError are undefined
	#endif


	static Void GetConsoleSize(Void* handle, SizeType& width, SizeType& height)
	{
	#if defined(PLATFORM_WINDOWS)
		CONSOLE_SCREEN_BUFFER_INFO descriptor;
		GetConsoleScreenBufferInfo(
			reinterpret_cast<HANDLE>(handle),
			&descriptor
		);

		auto& size	= descriptor.dwSize;
		width		= size.X;
		height		= size.Y;
	#else
	#error No implementation
	#endif
	}


	Console::Console()
	{
	#if defined(PLATFORM_WINDOWS)
		handle = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);

		GetConsoleSize(handle, width, height);
	#else
	#error No implementation
	#endif
	}

	Console::Console(Void* handle)
		: handle(handle)
	{
		GetConsoleSize(handle, width, height);
	}

	Console::~Console()
	{
	#if defined(PLATFORM_WINDOWS)
		CloseHandle( reinterpret_cast<HANDLE>(handle) );
	#else
	#error No implementation
	#endif
	}

	Void Console::SetCursorPosition(SizeType x, SizeType y)
	{
	#if defined(PLATFORM_WINDOWS)
		COORD coord = { x, height - 1 - y };
		SetConsoleCursorPosition(
			reinterpret_cast<HANDLE>(handle),
			coord
		);
	#else
	#error No implementation
	#endif
	}

	Void Console::SetAsActive()
	{
	#if defined(PLATFORM_WINDOWS)
		SetConsoleActiveScreenBuffer( reinterpret_cast<HANDLE>(handle) );
	#else
	#error No implementation
	#endif
	}

	Void Console::SetColor(Color foreground, Color background)
	{
#if defined(PLATFORM_WINDOWS)
		SetConsoleTextAttribute(
			reinterpret_cast<HANDLE>(handle),
			( static_cast<WORD>(foreground) << 0 ) | ( static_cast<WORD>(background) << 4 )
		);
#else
#error No implementation
#endif
	}

	DynamicArray<Key> Console::ReadInputKeys()
	{
		DynamicArray<Key> ret;

	#if defined(PLATFORM_WINDOWS)
		constexpr SizeType Limit = 64;


		static INPUT_RECORD records[Limit];
		
		DWORD read;
		ReadConsoleInputW(
			reinterpret_cast<HANDLE>(handle),
			records,
			Limit,
			&read
		);

		for ( SizeType index = 0; index < read; index++ )
		{
			auto type = records[index].EventType;
			if ( type == KEY_EVENT )
			{
				auto& key = records[index].Event.KeyEvent;
				if ( key.bKeyDown )
					ret.Add(
						static_cast<Key>( key.wVirtualKeyCode )
					);
			}
		}
	#else
	#error No implementation
	#endif

		return ret;
	}

	Void Console::Clear()
	{
	#if defined(PLATFORM_WINDOWS)
		COORD coord = { 0, 0 };
		DWORD written;
		FillConsoleOutputCharacterW(
			reinterpret_cast<HANDLE>(handle),
			L' ',
			width * height,
			coord,
			&written
		);

		SetCursorPosition(0, 0);
	#else
	#error No implementation
	#endif
	}

	Void Console::Write(const U8String& text)
	{
	#if defined(PLATFORM_WINDOWS)
		U16String u16 = text;
		WriteConsoleW(
			reinterpret_cast<HANDLE>(handle),
			u16,
			u16.GetCount(),
			nullptr,
			nullptr
		);
	#else
	#error No implementation
	#endif
	}

	SizeType Console::GetWidth() const
	{
		return width;
	}

	SizeType Console::GetHeight() const
	{
		return height;
	}
}