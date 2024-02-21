#pragma once

#include "Game/Actor.h"
#include "Game/Element.h"
#include "Game/Level.h"
#include "Game/Status.h"
#include "Game/Tag.h"



struct ActorDescriptor
{
	enum Index
	{
		GuoBa,
		YueGui,

		Count,
	};


	U8String		name;
	U8String		footprint;
	Console::Color	foreground;
	Console::Color	background;
};


struct ElementDescriptor
{
	U8String		name;
	Console::Color	foreground;
	Console::Color	background;
};


// Tips
struct Description
{
	U8String level;
	U8String move;
	U8String whenClear;
};


Tag GetTag(Element element);
Void SetStatus(Status* status, const Level& level);

Level LoadLevel(const U8String& path);
ActorDescriptor LoadActorDescriptor(const U8String& path);
ElementDescriptor LoadElementDescriptor(const U8String& path);
Description LoadDescription(const U8String& path);

Void TryMove(Status* status, Int32 xOffset, Int32 yOffset);