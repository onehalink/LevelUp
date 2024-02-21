#pragma once

#include "Element.h"

#include "Engine.h"



using namespace Engine;


constexpr SizeType GridsInX		= 10;
constexpr SizeType GridsInY		= 8;
constexpr SizeType TotalGrids	= GridsInX * GridsInY;


struct Level
{
	struct ActorRecord
	{
		U8String	name;
		Vector2Int	origin;
		SizeType	moveLimit;
	};


	struct EntityRecord
	{
		Element		element;
		Vector2Int	position;
	};


	DynamicArray<ActorRecord>	actorRecords;
	DynamicArray<EntityRecord>	entityRecords;
};