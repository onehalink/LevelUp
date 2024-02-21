#pragma once

#include "../SAL/EventSystem.h"



namespace Engine::Windows
{
	class ENGINE_API Window
	{
	public:
		using ProcedureCallback = Function<Int64, Void*, UInt32, UInt64, Int64>;


		NONCOPYABLE(Window);


		Window();
		~Window();


		// Create a Windows window and display it on desktop
		Void Create(const Char16* title, SizeType width, SizeType height, Void* userParameter = nullptr, ProcedureCallback Fn = nullptr);
		// Poll events from OS
		Void Update();


		Void SetTitle(const Char16* title);


		Void SetWidth(SizeType width);
		Void SetHeight(SizeType height);

		Void* GetHandle() const;
		SizeType GetWidth() const;
		SizeType GetHeight() const;
	private:
		Void* handle;

		SizeType width;
		SizeType height;
	};
}