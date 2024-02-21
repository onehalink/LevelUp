#pragma once

#include "PixelFormat.h"



namespace Engine
{
	struct RenderTarget
	{
		Void*		buffer;
		SizeType	width;
		SizeType	height;
		PixelFormat	format;
	};
}