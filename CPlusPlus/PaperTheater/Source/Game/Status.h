#pragma once

#include "Actor.h"
#include "Element.h"
#include "Level.h"
#include "Tag.h"



struct Status
{
	struct Slot
	{
		Element	element;
		Tag		tag;
	};


	Slot slots[TotalGrids];

	DynamicArray<Actor>	actors;
	SizeType			selectActorIndex;
	Actor*				selectedActor;


	Vector2Int	target; // destination
	Bool		isClear;
};