#include "Game.h"



static Element StringToElement(const U8String& text)
{
    SizeType count = text.GetCount();


    if ( count == 3 && Memory::Equal( text, "Box",          3 ) ) return Element::Box;
    if ( count == 3 && Memory::Equal( text, "Car",          3 ) ) return Element::Car;
    if ( count == 5 && Memory::Equal( text, "Grass",        5 ) ) return Element::Grass;
    if ( count == 4 && Memory::Equal( text, "Food",         4 ) ) return Element::Food;
    if ( count == 8 && Memory::Equal( text, "Mountain",     8 ) ) return Element::Mountain;
    if ( count == 4 && Memory::Equal( text, "Tree",         4 ) ) return Element::Tree;
    if ( count == 5 && Memory::Equal( text, "LockA",        5 ) ) return Element::LockA;
    if ( count == 4 && Memory::Equal( text, "KeyA",         4 ) ) return Element::KeyA;
    if ( count == 5 && Memory::Equal( text, "LockB",        5 ) ) return Element::LockB;
    if ( count == 4 && Memory::Equal( text, "KeyB",         4 ) ) return Element::KeyB;
    if ( count == 5 && Memory::Equal( text, "LockC",        5 ) ) return Element::LockC;
    if ( count == 4 && Memory::Equal( text, "KeyC",         4 ) ) return Element::KeyC;
    if ( count == 5 && Memory::Equal( text, "Actor",        5 ) ) return Element::Actor;
    if ( count == 9 && Memory::Equal( text, "Footprint",    9 ) ) return Element::Footprint;

    return Element::Empty;
}

static Console::Color StringToColor(const U8String& text)
{
    using Color = Console::Color;


    Color Red       = Color::Red;
    Color Green     = Color::Green;
    Color Blue      = Color::Blue;
    Color Yellow    = Red   | Green;
    Color Cyan      = Green | Blue;
    Color Magenta   = Red   | Blue;
    Color Black     = Color();
    Color White     = ~Black;


    SizeType count = text.GetCount();


    if ( count == 3 && Memory::Equal( text, "Red",      3 ) ) return Red;
    if ( count == 5 && Memory::Equal( text, "Green",    5 ) ) return Green;
    if ( count == 4 && Memory::Equal( text, "Blue",     4 ) ) return Blue;
    if ( count == 6 && Memory::Equal( text, "Yellow",   6 ) ) return Yellow;
    if ( count == 4 && Memory::Equal( text, "Cyan",     4 ) ) return Cyan;
    if ( count == 7 && Memory::Equal( text, "Magenta",  7 ) ) return Magenta;
    if ( count == 5 && Memory::Equal( text, "White",    5 ) ) return White;
    if ( count == 5 && Memory::Equal( text, "Black",    5 ) ) return Black;

    return Black;
}


Tag GetTag(Element element)
{
    switch (element)
    {
    case Element::Grass:
    case Element::Mountain:
    case Element::Tree:
    case Element::Footprint:
    case Element::LockA:
    case Element::LockB:
    case Element::LockC:
        return Tag::Barrier;
    case Element::Box:
    case Element::Car:
        return Tag::MovableObject;
    case Element::KeyA:
    case Element::KeyB:
    case Element::KeyC:
        return Tag::DestructibleObject;
    case Element::Food:
        return Tag::Target;
    default:
        return Tag::Unknown;
    }
}

Void SetStatus(Status* status, const Level& level)
{
    Memory::Clear( status, sizeof(Status) );


    {
        for ( auto& record : level.actorRecords )
            status->actors.Add( Actor( record.name, record.moveLimit, record.origin ) );

        SizeType index = 0;

        status->selectActorIndex    = index;
        status->selectedActor       = &status->actors[index];
    }

    {
        auto& slots     = status->slots;
        auto& records   = level.entityRecords;

        /*
        for( SizeType y = 0; y < GridsInY; y++ )
            for ( SizeType x = 0; x < GridsInX; x++ )
            {
                auto& slot = slots[ GridsInX * y + x ];

                slot.element    = Element::Empty;
                slot.tag        = Tag::Unknown;
            }
        */

        for ( auto& record : records )
        {
            SizeType x = record.position[0];
            SizeType y = record.position[1];
            auto& slot = slots[ GridsInX * y + x ];

            Element element = record.element;

            slot.element    = element;
            slot.tag        = GetTag(element);

            if ( element == Element::Food )
                status->target = { x, y };
        }
    }
}

Level LoadLevel(const U8String& path)
{
    Level ret;

    DynamicArray<U8String> lines = File::ReadAllLines(path);

    //for (auto& line : lines)
    //{
    //    StandardOutput.Write(line);
    //    StandardOutput.Write("\n");
    //}

    //int breakpoint = -1;

    {
        constexpr auto AnotationCount = 2;

        constexpr auto ActorAnotation   = "[A";
        constexpr auto EntityAnotation  = "[E";


        auto ParseActorRecord = [](const U8String& text)
            {
                using Record = Level::ActorRecord;


                enum Index
                {
                    Name,
                    OriginX,
                    OriginY,
                    MoveLimit,
                };


                constexpr auto Separator = ',';


                auto splits = text.Split(Separator);

                U8String name = splits[Name];

                Int32 x, y;
                TryParseInt32( &x, splits[OriginX] );
                TryParseInt32( &y, splits[OriginY] );

                Int32 moveLimit;
                TryParseInt32( &moveLimit, splits[MoveLimit] );

                Record ret;
                ret.name        = name;
                ret.origin      = { x, y };
                ret.moveLimit   = moveLimit;

                return ret;
            };


        auto ParseEntityRecord = [](const U8String& text)
            {
                using Record = Level::EntityRecord;


                enum Index
                {
                    ElementName,
                    PositionX,
                    PositionY,
                };


                constexpr auto Separator = ',';


                auto splits = text.Split(Separator);

                Element element = StringToElement( splits[ElementName] );

                Int32 x, y;
                TryParseInt32( &x, splits[PositionX] );
                TryParseInt32( &y, splits[PositionY] );

                Record ret;
                ret.element     = element;
                ret.position    = { x, y };

                return ret;
            };


        for ( SizeType index = 0; index < lines.GetCount(); index++ )
        {
            U8String& line = lines[index];

            // empty line
            if ( line.GetCount() == 0 )
                continue;

            if ( Memory::Equal(line, ActorAnotation, AnotationCount) )
            {
                ++index;

                while (true)
                {
                    line = lines[ ++index ];

                    // empty line
                    if ( line.GetCount() == 0 )
                        break;

                    ret.actorRecords.Add( ParseActorRecord(line) );
                }
            }

            if ( Memory::Equal(line, EntityAnotation, AnotationCount) )
            {
                ++index;

                while ( index < lines.GetCount() )
                {
                    line = lines[ ++index ];

                    // empty line
                    if ( line.GetCount() == 0 )
                        break;

                    ret.entityRecords.Add( ParseEntityRecord(line) );
                }
            }
        }
    }

    return ret;
}

ActorDescriptor LoadActorDescriptor(const U8String& path)
{
    enum Index
    {
        Name,
        Footprint,
        Foreground,
        Background,
    };


    DynamicArray<U8String> lines = File::ReadAllLines(path);

    ActorDescriptor ret;
    ret.name        = lines[Name];
    ret.footprint   = lines[Footprint];
    ret.foreground  = StringToColor( lines[Foreground] );
    ret.background  = StringToColor( lines[Background] );

    return ret;
}

ElementDescriptor LoadElementDescriptor(const U8String& path)
{
    enum Index
    {
        Name,
        Foreground,
        Background,
    };


    DynamicArray<U8String> lines = File::ReadAllLines(path);

    ElementDescriptor ret;
    ret.name        = lines[Name];
    ret.foreground  = StringToColor( lines[Foreground] );
    ret.background  = StringToColor( lines[Background] );

    return ret;
}

Description LoadDescription(const U8String& path)
{
    enum Index
    {
        Level,
        Move,
        WhenClear,
    };


    DynamicArray<U8String> lines = File::ReadAllLines(path);

    Description ret;
    ret.level       = lines[Level];
    ret.move        = lines[Move];
    ret.whenClear   = lines[WhenClear];

    return ret;
}

Void TryMove(Status* status, Int32 xOffset, Int32 yOffset)
{
    auto Equal = [](const Vector2Int& leftHandSide, const Vector2Int& rightHandSide)
        {
            return leftHandSide[0] == rightHandSide[0] && leftHandSide[1] == rightHandSide[1];
        };

    auto IsInside = [](Int32 x, Int32 y)
        {
            if ( x < 0 || x >= GridsInX ) return false;
            if ( y < 0 || y >= GridsInY ) return false;

            return true;
        };

    auto DestructLock = [](Status* status, Element element)
        {
            if ( element != Element::KeyA && element != Element::KeyB && element != Element::KeyC )
                return;

            for ( auto& slot : status->slots )
                if (
                    ( element == Element::KeyA && slot.element == Element::LockA ) ||
                    ( element == Element::KeyB && slot.element == Element::LockB ) ||
                    ( element == Element::KeyC && slot.element == Element::LockC )
                    )
                {
                    Memory::Clear( &slot, sizeof(slot) );

                    break;
                }
        };

    auto GetOtherActor = [](Status* status) -> Actor*
        {
            SizeType count = status->actors.GetCount();
            if ( count == 1 )
                return nullptr;

            return &status->actors[ ( status->selectActorIndex + 1 ) % count ];
        };


    if ( xOffset == 0 && yOffset == 0 )
        return;

    auto& actor = *status->selectedActor;
    auto& slots = status->slots;

    Vector2Int previousPosition = actor.position;
    Vector2Int nextPosition     = previousPosition + Vector2Int{ xOffset, yOffset };

    auto& priviousSlot  = slots[ GridsInX * previousPosition[1] + previousPosition[0] ];
    auto& nextSlot      = slots[ GridsInX * nextPosition[1] + nextPosition[0] ];

    if ( actor.IsUndoOperation(xOffset, yOffset) )
    {
        actor.GoBack();

        if ( priviousSlot.element == Element::Footprint )
            Memory::Clear( &priviousSlot, sizeof(priviousSlot) );

        return;
    }

    if ( actor.move == 0 )
        return;

    if ( !IsInside( nextPosition[0], nextPosition[1] ) )
        return;

    switch (nextSlot.tag)
    {
    case Tag::Barrier:
        return;
    case Tag::DestructibleObject:
    {
        DestructLock( status, nextSlot.element );
        Memory::Clear( &nextSlot, sizeof(nextSlot) );
    }
        break;
    case Tag::MovableObject:
    {
        Int32 x = nextPosition[0] + xOffset;
        Int32 y = nextPosition[1] + yOffset;
        if ( IsInside(x, y) )
        {
            auto& selected = slots[ GridsInX * y + x ];
            if ( selected.tag == Tag::Barrier || selected.tag == Tag::MovableObject )
                return;

            Actor* other = GetOtherActor(status);
            if ( nextSlot.element == Element::Car && other )
            {
                if (
                    Equal( other->origin, nextPosition      ) &&
                    Equal( other->origin, other->position   )
                    )
                    other->position = other->origin = { x, y };
                else
                    return;
            }

            if (
                ( selected.element == Element::KeyA ) ||
                ( selected.element == Element::KeyB ) ||
                ( selected.element == Element::KeyC )
                )
                DestructLock( status, selected.element );

            // copy
            selected = nextSlot;
            Memory::Clear( &nextSlot, sizeof(nextSlot) );
        }
        else
            return;
    }
        break;
    case Tag::Target:
        break;
    }

    actor.Advance(xOffset, yOffset);

    if ( nextSlot.element == Element::Empty )
    {
        nextSlot.element    = Element::Footprint;
        nextSlot.tag        = GetTag( nextSlot.element );
    }
}