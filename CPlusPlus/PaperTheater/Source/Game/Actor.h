#pragma once

#include "Engine.h"



using namespace Engine;


struct Actor
{
	U8String name;

	SizeType move;
	SizeType moveLimit;

	Vector2Int					origin;
	Vector2Int					position;
	DynamicArray<Vector2Int>	footprints;


	Actor();
	Actor(const U8String& name, SizeType moveLimit, const Vector2Int& origin);


	Void Advance(SizeType xOffset, SizeType yOffset);
	Void GoBack();
	Bool IsUndoOperation(SizeType xOffset, SizeType yOffset);
};