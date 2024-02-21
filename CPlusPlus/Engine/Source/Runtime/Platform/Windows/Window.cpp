#include "Window.h"

#include "Windows.h"



namespace Engine::Windows
{
	static LRESULT WINAPI WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		static Void* userParameter;


		EventSystem* eventSystem = reinterpret_cast<EventSystem*>(userParameter);
		switch (message)
		{
		case WM_CREATE:
			userParameter = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
			break;
		case WM_SIZE:
		{
			SizeType width	= ( lParam >>  0 ) & 0xFFFF;
			SizeType height = ( lParam >> 16 ) & 0xFFFF;

			eventSystem->AddWindowResizeEvent(width, height);
		}
			break;
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			eventSystem->AddWindowFocusEvent( message == WM_SETFOCUS );
			break;
		case WM_CLOSE:
			eventSystem->AddWindowCloseEvent(true);
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
			eventSystem->AddKeyEvent(
				static_cast<Key>(wParam),
				message == WM_KEYDOWN ? KeyState::Press : KeyState::Release
			);
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			// index of the last mouse button
			static WPARAM lastWParam;


			// the last mouse button had been release if isZero
			Bool isZero = wParam == 0 ? true : false;

			eventSystem->AddMouseButtonEvent(
				!isZero ? static_cast<MouseButton>(wParam) : static_cast<MouseButton>(lastWParam),
				!isZero ? MouseButtonState::Press : MouseButtonState::Release
			);

			lastWParam = wParam;
		}
			break;
		case WM_MOUSEMOVE:
		{
			SizeType height;
			{
				RECT rect;
				GetClientRect( handle, &rect );

				height = rect.bottom - rect.top;
			}

			Int32 x = ( lParam >>  0 ) & 0xFFFF;
			Int32 y = ( lParam >> 16 ) & 0xFFFF;
			
			eventSystem->AddMouseMoveEvent( x, height - 1 - y );
		}
			break;
		case WM_MOUSEWHEEL:
		{
			constexpr auto Delta = WHEEL_DELTA;


			Int32 value = ( wParam >> 16 ) & 0xFFFF;

			eventSystem->AddMouseScrollWheelScrollEvent( value / Delta );
		}
			break;
		default:
			return DefWindowProcW(handle, message, wParam, lParam);
		}

		return LRESULT(1);
	}

	Window::Window()
	{
		Memory::Clear( this, sizeof(Window) );
	}

	Window::~Window()
	{

	}

	Void Window::Create(const Char16* title, SizeType width, SizeType height, Void* userParameter, ProcedureCallback Fn)
	{
		HINSTANCE hInstance		= GetModuleHandleW(nullptr);
		const Char16* className	= L"Class Entry";


		// window style
		UInt32 style		= WS_OVERLAPPEDWINDOW;
		UInt32 extendStyle	= 0;


		// register window class
		{
			WNDCLASSEXW descriptor;
			Memory::Clear( &descriptor, sizeof(WNDCLASSEXW) );
			descriptor.cbSize			= sizeof(WNDCLASSEXW);
			descriptor.hInstance		= hInstance;
			descriptor.lpfnWndProc		= Fn ? reinterpret_cast<WNDPROC>(Fn) : WindowProcedure;
			descriptor.lpszClassName	= className;

			RegisterClassExW( &descriptor );
		}

		// resized to expected size
		SizeType realWidth;
		SizeType realHeight;
		{
			RECT rect = { 0, 0, width, height };
			AdjustWindowRectEx( &rect, style, false, extendStyle );

			realWidth	= rect.right - rect.left;
			realHeight	= rect.bottom - rect.top;
		}

		HWND handle = CreateWindowExW(
			extendStyle,
			className,
			title,
			style,
			CW_USEDEFAULT, CW_USEDEFAULT, realWidth, realHeight,
			nullptr, nullptr, hInstance, userParameter
		);
		ShowWindow(handle, SW_SHOWDEFAULT);


		this->handle	= handle;
		this->width		= width;
		this->height	= height;
	}

	Void Window::Update()
	{
		MSG message;
		while ( PeekMessageW( &message, reinterpret_cast<HWND>(handle), 0, 0, PM_REMOVE ) )
			DispatchMessageW(&message);
	}

	Void Window::SetTitle(const Char16* title)
	{
		SetWindowTextW( reinterpret_cast<HWND>(handle), title );
	}

	Void Window::SetWidth(SizeType width)
	{
		this->width = width;
	}

	Void Window::SetHeight(SizeType height)
	{
		this->height = height;
	}

	Void* Window::GetHandle() const
	{
		return handle;
	}

	SizeType Window::GetWidth() const
	{
		return width;
	}

	SizeType Window::GetHeight() const
	{
		return height;
	}
}