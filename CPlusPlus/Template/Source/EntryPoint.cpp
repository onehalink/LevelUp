#include "Application.h"



Int32 EntryPoint()
{
	Runtime runtime;
	runtime.wantToQuit = false;

	EventSystem& eventSystem = runtime.eventSystem;

	Window& window = runtime.window;
	window.Create( L"Template", 1600, 900, &eventSystem );

	GraphicDeviceInterface gdi( window.GetHandle() );

	OnApplicationInitialize( &runtime );

	Timer timer;
	RealType timestep = 0;
	while ( !runtime.wantToQuit )
	{
		timestep = timer.Elapsed();
		timer.Reset();

		window.Update();
		for( auto& event : eventSystem.eventQueue )
			switch ( event.type )
			{
			case Event::Type::WindowResize:
			{
				SizeType width	= event.WindowResizeParameters.width;
				SizeType height	= event.WindowResizeParameters.height;


				window.SetWidth(width);
				window.SetHeight(height);

				OnApplicationResize(width, height);
			}
				break;
			case Event::Type::WindowFocus:
				OnApplicationFocus( event.WindowFocusParameters.isFocused );
				break;
			case Event::Type::WindowClose:
				OnApplicationQuit( event.WindowCloseParameters.isClosed );
				break;
			case Event::Type::Key:
			{
				Key key			= event.KeyParameters.key;
				KeyState state	= event.KeyParameters.keyState;


				eventSystem.keys[ static_cast<EnumUnderlyingType<Key>>(key) ] |= state;
			}
				break;
			case Event::Type::MouseButton:
			{
				MouseButton button		= event.MouseButtonParameters.mouseButton;
				MouseButtonState state	= event.MouseButtonParameters.mouseButtonState;


				eventSystem.mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(button) ] |= state;
			}
				break;
			case Event::Type::MouseMove:
			{
				Int32 x = event.MouseMoveParameters.mousePositionX;
				Int32 y = event.MouseMoveParameters.mousePositionY;


				eventSystem.mousePosition[0] = x;
				eventSystem.mousePosition[1] = y;
			}
				break;
			case Event::Type::MouseScrollWheelScroll:
				eventSystem.mouseScrollWheelScrolledValue += event.MouseScrollWheelScrollParameters.mouseScrollWheelScrolledDelta;
				break;
			}
		
		OnUpdate(timestep);
		gdi.Present( window.GetWidth(), window.GetHeight(), OnRender );

		eventSystem.Reset();
	}

	return 0;
}


int main(int count, char** parameters)
{
	return EntryPoint();
}


#if defined(PLATFORM_WINDOWS)
#include <Windows.h>



int WINAPI wWinMain(HINSTANCE current, HINSTANCE previous, PWSTR commandLine, int commandShow)
{
	return EntryPoint();
}
#endif