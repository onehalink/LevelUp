#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	class ENGINE_API FileDialog
	{
	public:
		/**
		* Open a file dialog and selected/saved filename(absolute path) will be placed in [inBuffer]
		* 
		* 
		* @param inBuffer	A pointer point to allocated heap/stack memory
		* @param inSize		Indicate how many Char16s could be used
		*/
		static Bool Open(Char16* inBuffer, SizeType inSize, const Char16* filters = L"(*.*)\0*.*\0", const Char16* initialDirectory = L"./", const Char16* title = L"Open file", Void* owner = nullptr /** A native Windows window handle */);
		static Bool Save(Char16* inBuffer, SizeType inSize, const Char16* filters = L"(*.*)\0*.*\0", const Char16* initialDirectory = L"./", const Char16* title = L"Save as..", Void* owner = nullptr /** A native Windows window handle */);
	};
}