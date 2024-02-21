#include "File.h"

#if defined(PLATFORM_WINDOWS)
#include "../Windows/Windows.h"
#endif



namespace Engine
{
	File::File(const U8String& path, OpenOption option)
	{
	#if defined(PLATFORM_WINDOWS)
		DWORD desiredAccess;
		DWORD creationDisposition;
		switch (option)
		{
		case OpenOption::Read:
			desiredAccess		= GENERIC_READ;
			creationDisposition = OPEN_EXISTING;
			break;
		case OpenOption::Write:
			desiredAccess		= GENERIC_WRITE;
			creationDisposition	= CREATE_NEW;
			break;
		}

		handle = CreateFileW(
			static_cast<U16String>(path),
			desiredAccess,
			0,
			nullptr,
			creationDisposition,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);
	#else
	#error No implementation
	#endif
	}

	File::~File()
	{
	#if defined(PLATFORM_WINDOWS)
		CloseHandle( reinterpret_cast<HANDLE>(handle) );
	#else
	#error No implementation
	#endif
	}

	Void File::Seek(SeekOption option, Int64 offset)
	{
	#if defined(PLATFORM_WINDOWS)
		DWORD method;
		switch (option)
		{
		case SeekOption::Begin:
			method = FILE_BEGIN;
			break;
		case SeekOption::Current:
			method = FILE_CURRENT;
			break;
		case SeekOption::End:
			method = FILE_END;
			break;
		}

		LARGE_INTEGER distance;
		distance.QuadPart = offset;

		SetFilePointerEx(
			reinterpret_cast<HANDLE>(handle),
			distance,
			nullptr,
			method
		);
	#else
	#error No implementation
	#endif
	}

	Void File::Read(Void* buffer, SizeType byteCount)
	{
	#if defined(PLATFORM_WINDOWS)
		ReadFile(
			reinterpret_cast<HANDLE>(handle),
			buffer,
			byteCount,
			nullptr,
			nullptr
		);
	#else
	#error No implementation
	#endif
	}

	Void File::Write(const Void* buffer, SizeType byteCount)
	{
	#if defined(PLATFORM_WINDOWS)
		WriteFile(
			reinterpret_cast<HANDLE>(handle),
			buffer,
			byteCount,
			nullptr,
			nullptr
		);
	#else
	#error No implementation
	#endif
	}

	Void File::Copy(const U8String& from, const U8String& to)
	{
		HeapMemory loaded = ReadAllBytes(from);
		WriteAllBytes(
			to,
			loaded.GetBuffer(),
			loaded.GetByteCount()
		);
	}

	Void File::Delete(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		DeleteFileW( static_cast<U16String>(path) );
	#else
	#error No implementation
	#endif
	}

	Bool File::Exist(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		{
			File file( path, OpenOption::Read );

			if ( GetLastError() == ERROR_FILE_NOT_FOUND )
				return false;
		}

		Bool isDirectory = GetFileAttributesW( static_cast<U16String>(path) ) & FILE_ATTRIBUTE_DIRECTORY;
		if (isDirectory)
			return false;

		return true;
	#else
	#error No implementation
	#endif
	}

	SizeType File::GetSize(const U8String& path)
	{
	#if defined(PLATFORM_WINDOWS)
		File file( path, OpenOption::Read );

		LARGE_INTEGER ret;
		GetFileSizeEx(
			reinterpret_cast<HANDLE>( file.handle ),
			&ret
		);

		return ret.QuadPart;
	#else
	#error No implementation
	#endif
	}

	Void File::Move(const U8String& from, const U8String& to)
	{
		/**
		* Copy(from, to);
		* Delete(from);
		*/
	#if defined(PLATFORM_WINDOWS)
		MoveFileW( static_cast<U16String>(from), static_cast<U16String>(to) );
	#else
	#error No implementation
	#endif
	}

	HeapMemory File::ReadAllBytes(const U8String& path)
	{
		HeapMemory ret( GetSize(path) );


		File file( path, OpenOption::Read );
		file.Read(
			ret.GetBuffer(),
			ret.GetByteCount()
		);

		return ret;
	}

	Void File::WriteAllBytes(const U8String& path, const Void* buffer, SizeType byteCount)
	{
		File file( path, OpenOption::Write );
		file.Write(
			buffer,
			byteCount
		);
	}

	DynamicArray<U8String> File::ReadAllLines(const U8String& path)
	{
		DynamicArray<U8String> ret;
		{
			Char8*		buffer;
			SizeType    size;
			{
				HeapMemory loaded = File::ReadAllBytes(path);

				buffer	= reinterpret_cast<Char8*>( loaded.GetBuffer() );
				size	= loaded.GetByteCount() - 1;

				Memory::Clear( &loaded, sizeof(HeapMemory) );

				buffer[size] = '\0';
			}

			// Parse lines in the input string as terminated by any of CRLF, CR, LF
			SizeType startIndex = 0;
			for (SizeType index = 0; index < size; index++)
				if (
					buffer[index] == '\n' ||
					buffer[index] == '\r'
					)
				{
					auto length = index - startIndex;
					auto realLength = length + 1;

					auto p = new Char8[realLength];
					p[length] = '\0';

					Memory::Copy(buffer + startIndex, p, length);

					ret.Add(U8String(p, length));

					startIndex = index + 1;

					if (
						index < size - 1 &&
						buffer[index + 1] == '\n'
						)
					{
						index++;
						startIndex++;
					}
				}

			{
				auto length = size - startIndex;
				auto realLength = length + 1;

				auto p = new Char8[realLength];
				p[length] = '\0';

				Memory::Copy(buffer + startIndex, p, length);

				ret.Add(U8String(p, length));
			}
		}

		return ret;
	}

	Void File::WriteAllLines(const U8String& path, const DynamicArray<U8String>& lines)
	{
		constexpr auto LineFeed = '\n';


		File file( path, OpenOption::Write );
		for ( auto& line : lines )
		{
			file.Write( line.GetBuffer(), line.GetCount() );
			file.Write( &LineFeed, 1 );
		}
	}
}