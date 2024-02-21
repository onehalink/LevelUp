#include "Application.h"



#pragma region Local
static Runtime*		runtime;
static Window*		window;
static EventSystem*	eventSystem;
#pragma endregion


Void OnApplicationInitialize(Void* userParameter)
{
	{
		runtime		= reinterpret_cast<Runtime*>(userParameter);
		window		= &runtime->window;
		eventSystem	= &runtime->eventSystem;
	}
}

Void OnApplicationResize(SizeType width, SizeType height)
{

}

Void OnApplicationFocus(Bool isFocused)
{
	runtime->isFocused = isFocused;
}

Void OnApplicationQuit(Bool wantToQuit)
{
	runtime->wantToQuit = wantToQuit;
}

Void OnUpdate(RealType deltaTime)
{
	if ( eventSystem->KeyPressed( Key::Escape ) )
		runtime->wantToQuit = true;
}

Void OnRender(Void* RenderTarget)
{
	SizeType width	= window->GetWidth();
	SizeType height	= window->GetHeight();


	// frame begin
	{
		for ( SizeType y = 0; y < height; y++ )
			for ( SizeType x = 0; x < width; x++ )
				reinterpret_cast<UInt32*>(RenderTarget)[ width * y + x ] = 0;
	}

	// render
	{
		for ( SizeType y = 0; y < height; y++ )
			for ( SizeType x = 0; x < width; x++ )
			{
				auto& pixel = reinterpret_cast<UInt32*>(RenderTarget)[ width * y + x ];

				Byte r = 0;
				Byte g = 0;
				Byte b = 0;
				Byte a = 0;

				//r = 255;

				pixel = ( b << 0 ) | ( g << 8 ) | ( r << 16 ) | ( a << 24 );
			}
	}

	// frame end
	{

	}
}