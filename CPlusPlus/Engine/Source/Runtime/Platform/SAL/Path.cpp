#include "Path.h"



namespace Engine
{
	U8String Path::Combine(const U8String& A, const U8String& B)
	{
		auto IsNormalized = [](const U8String& path)
			{
				Char8 last = path[ path.GetCount() - 1 ];

				return last == '/' || last == '\\';
			};


		if ( !IsNormalized(A) )
			return A + '/' + B;

		return A + B;
	}
}