#include "Actor.h"



Actor::Actor()
{
	Memory::Clear( this, sizeof(Actor) );
}

Actor::Actor(const U8String& name, SizeType moveLimit, const Vector2Int& origin)
{
	this->name		= name;
	this->move		= moveLimit;
	this->moveLimit	= moveLimit;
	this->origin	= origin;
	this->position	= origin;
}

Void Actor::Advance(SizeType xOffset, SizeType yOffset)
{
	if ( move == 0 )
		return;

	position += { xOffset, yOffset };
	footprints.Add(position);

	move--;
}

Void Actor::GoBack()
{
	move++;

	SizeType count = footprints.GetCount();
	if ( count == 1 )
	{
		footprints.Clear();
		position = origin;

		return;
	}

	footprints.RemoveAt( count - 1 );
	position = footprints[ count - 1 - 1 ];
}

Bool Actor::IsUndoOperation(SizeType xOffset, SizeType yOffset)
{
	auto Fn = [=](const Vector2Int& from, const Vector2Int& to)
		{
			Vector2Int direction = to - from;

			return direction[0] == xOffset && direction[1] == yOffset;
		};


	SizeType size = footprints.GetCount();

	if ( size == 0 )
		return false;

	if ( size == 1 )
		return Fn(position, origin);

	auto& previous	= footprints[ size - 2 ];
	auto& next		= footprints[ size - 1 ];

	return Fn(next, previous);
}