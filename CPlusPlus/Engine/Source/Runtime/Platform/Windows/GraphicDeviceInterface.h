#pragma once

#include "../../Core.h"



namespace Engine::Windows
{
	class ENGINE_API GraphicDeviceInterface
	{
	public:
		using RenderCallback = Action<Void*>;


		NONCOPYABLE(GraphicDeviceInterface);


		GraphicDeviceInterface(Void* nativeWindowsWindowHandle);
		~GraphicDeviceInterface();


		/**
		* Overwrite RenderTarget by a function pointer(Fn) to update the client area of Windows window
		* 
		* 
		* @remark
		* A pointer(RenderTarget) point to heap memory's size in bytes defined by width * height * 4
		* RenderTarget's pixel format is B8G8R8A8(use 32-bit to represent a pixel's color)
		*/
		Void Present(SizeType width, SizeType height, RenderCallback Fn);
	private:
		Void* handle;

		Void* targetDC;
		Void* memoryDC;
	};
}