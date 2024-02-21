#include "Application.h"



#pragma region Local
static Runtime*		runtime;
static Window*		window;
static EventSystem*	eventSystem;

static Bitmap	bitmap;
static Bool		isLoaded = false;
#pragma endregion


Void OnApplicationInitialize(Void* userParameter)
{
	{
		runtime		= reinterpret_cast<Runtime*>(userParameter);
		window		= &runtime->window;
		eventSystem	= &runtime->eventSystem;
	}

	{
		eventSystem->AddKeyEvent( Key::O, KeyState::Click );
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

	if ( eventSystem->KeyClicked( Key::O ) )
	{
		constexpr SizeType Limit = 256;


		static Char16 buffer[Limit];
		if ( FileDialog::Open( buffer, Limit, L"(*.bmp)\0*.bmp\0" ) )
		{
			HeapMemory loaded	= File::ReadAllBytes( U16String(buffer) );
			bitmap				= Bitmap::Decode( loaded.GetBuffer(), loaded.GetByteCount() );

			isLoaded = true;
		}
		else
		{
			isLoaded = false;
		}
	}
}

Void OnRender(Void* RenderTarget)
{
	if ( !isLoaded )
		return;


	SizeType width	= window->GetWidth();
	SizeType height	= window->GetHeight();

	SizeType imageWidth		= bitmap.GetWidth();
	SizeType imageHeight	= bitmap.GetHeight();

	RealType scale;
	{
		RealType horizontalScale	= static_cast<RealType>(width) / imageWidth;
		RealType verticalScale		= static_cast<RealType>(height) / imageHeight;

		scale = Minimum(horizontalScale, verticalScale);
	}

	imageWidth	*= scale;
	imageHeight *= scale;

	SizeType xBegin = width / 2 - imageWidth / 2;
	SizeType xEnd	= xBegin + imageWidth;
	SizeType yBegin	= height / 2 - imageHeight / 2;
	SizeType yEnd	= yBegin + imageHeight;
	for( SizeType y = yBegin; y < yEnd; y++ )
		for ( SizeType x = xBegin; x < xEnd; x++ )
		{
			RealType u = static_cast<RealType>( x - xBegin ) / ( imageWidth - 1 );
			RealType v = static_cast<RealType>( y - yBegin ) / ( imageHeight - 1 );

			reinterpret_cast<UInt32*>(RenderTarget)[ width * y + x ] = bitmap.GetPixel(
				( bitmap.GetWidth() - 1 ) * u,
				( bitmap.GetHeight() - 1 ) * v
			);
		}
}