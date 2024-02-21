#include "EventSystem.h"



namespace Engine
{
	EventSystem::EventSystem()
	{
		Memory::Clear( this, sizeof(EventSystem) );
	}

	Bool EventSystem::KeyPressed(Key key)
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Press ) == KeyState::Press;
	}

	Bool EventSystem::KeyReleased(Key key)
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Release ) == KeyState::Release;
	}

	Bool EventSystem::KeyClicked(Key key)
	{
		return ( keys[ static_cast<EnumUnderlyingType<Key>>(key) ] & KeyState::Click ) == KeyState::Click;
	}

	Bool EventSystem::MouseButtonPressed(MouseButton mouseButton)
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Press ) == MouseButtonState::Press;
	}

	Bool EventSystem::MouseButtonReleased(MouseButton mouseButton)
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Release ) == MouseButtonState::Release;
	}

	Bool EventSystem::MouseButtonClicked(MouseButton mouseButton)
	{
		return ( mouseButtons[ static_cast<EnumUnderlyingType<MouseButton>>(mouseButton) ] & MouseButtonState::Click ) == MouseButtonState::Click;
	}

	Void EventSystem::AddWindowResizeEvent(SizeType width, SizeType height)
	{
		Event event;
		event.type							= Event::Type::WindowResize;
		event.WindowResizeParameters.width	= width;
		event.WindowResizeParameters.height = height;

		eventQueue.Add(event);
	}

	Void EventSystem::AddWindowFocusEvent(Bool isFocused)
	{
		Event event;
		event.type								= Event::Type::WindowFocus;
		event.WindowFocusParameters.isFocused	= isFocused;

		eventQueue.Add(event);
	}

	Void EventSystem::AddWindowCloseEvent(Bool isClosed)
	{
		Event event;
		event.type								= Event::Type::WindowClose;
		event.WindowCloseParameters.isClosed	= isClosed;

		eventQueue.Add(event);
	}

	Void EventSystem::AddKeyEvent(Key key, KeyState keyState)
	{
		Event event;
		event.type						= Event::Type::Key;
		event.KeyParameters.key			= key;
		event.KeyParameters.keyState	= keyState;

		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseButtonEvent(MouseButton mouseButton, MouseButtonState mouseButtonState)
	{
		Event event;
		event.type										= Event::Type::MouseButton;
		event.MouseButtonParameters.mouseButton			= mouseButton;
		event.MouseButtonParameters.mouseButtonState	= mouseButtonState;

		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseMoveEvent(Int32 mousePositionX, Int32 mousePositionY)
	{
		Event event;
		event.type									= Event::Type::MouseMove;
		event.MouseMoveParameters.mousePositionX	= mousePositionX;
		event.MouseMoveParameters.mousePositionY	= mousePositionY;

		eventQueue.Add(event);
	}

	Void EventSystem::AddMouseScrollWheelScrollEvent(Int32 mouseScrollWheelScrolledDelta)
	{
		Event event;
		event.type																= Event::Type::MouseScrollWheelScroll;
		event.MouseScrollWheelScrollParameters.mouseScrollWheelScrolledDelta	= mouseScrollWheelScrolledDelta;

		eventQueue.Add(event);
	}

	Void EventSystem::Reset()
	{
		for ( SizeType index = 0; index < KeyCount; index++ )
		{
			auto& key = keys[index];
			if ( ( key & KeyState::Click ) == KeyState::Click )
				key &= ~KeyState::Click;
		}

		for ( SizeType index = 0; index < MouseButtonCount; index++ )
		{
			auto mouseButton = mouseButtons[index];
			if ( ( mouseButton & MouseButtonState::Click ) == MouseButtonState::Click )
				mouseButton &= ~MouseButtonState::Click;
		}

		eventQueue.Clear();
	}
}