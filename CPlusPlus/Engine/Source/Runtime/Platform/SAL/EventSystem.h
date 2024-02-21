#pragma once

#include "../HAL/Keyboard.h"
#include "../HAL/Mouse.h"



namespace Engine
{
	struct Event
	{
		enum class Type
		{
			WindowResize,
			WindowFocus,
			WindowClose,

			Key,

			MouseButton,
			MouseMove,
			MouseScrollWheelScroll,
		};


		Type type;


		union
		{
			struct
			{
				SizeType width;
				SizeType height;
			} WindowResizeParameters;


			struct
			{
				Bool isFocused;
			} WindowFocusParameters;


			struct
			{
				Bool isClosed;
			} WindowCloseParameters;


			struct
			{
				Key			key;
				KeyState	keyState;
			} KeyParameters;


			struct
			{
				MouseButton			mouseButton;
				MouseButtonState	mouseButtonState;
			} MouseButtonParameters;


			struct
			{
				Int32 mousePositionX;
				Int32 mousePositionY;
			} MouseMoveParameters;


			struct
			{
				Int32 mouseScrollWheelScrolledDelta;
			} MouseScrollWheelScrollParameters;
		};
	};


	class ENGINE_API EventSystem
	{
	public:
		static constexpr auto KeyCount			= static_cast<EnumUnderlyingType<Key>>( Key::Count );
		static constexpr auto MouseButtonCount	= static_cast<EnumUnderlyingType<MouseButton>>( MouseButton::Count );


		KeyState			keys[KeyCount];
		MouseButtonState	mouseButtons[MouseButtonCount];

		Int32 mousePosition[2];
		Int32 mouseScrollWheelScrolledValue;

		DynamicArray<Event> eventQueue;
	public:
		NONCOPYABLE(EventSystem);


		EventSystem();
	

		Bool KeyPressed(Key key);
		Bool KeyReleased(Key key);
		Bool KeyClicked(Key key);

		Bool MouseButtonPressed(MouseButton mouseButton);
		Bool MouseButtonReleased(MouseButton mouseButton);
		Bool MouseButtonClicked(MouseButton mouseButton);


		Void AddWindowResizeEvent(SizeType width, SizeType height);
		Void AddWindowFocusEvent(Bool isFocused);
		Void AddWindowCloseEvent(Bool isClosed);

		Void AddKeyEvent(Key key, KeyState keyState);

		Void AddMouseButtonEvent(MouseButton mouseButton, MouseButtonState mouseButtonState);
		Void AddMouseMoveEvent(Int32 mousePositionX, Int32 mousePositionY);
		Void AddMouseScrollWheelScrollEvent(Int32 mouseScrollWheelScrolledDelta);

		Void Reset();
	};
}