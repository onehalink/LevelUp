#include "Application.h"



#pragma region Local
static Runtime* runtime;

constexpr SizeType				FrameCount = 2;
static DynamicArray<Console*>	RenderTargets;
static SizeType					frameIndex;

static DynamicArray<Level>	levels;
static SizeType				selectLevelIndex;

static Status status;

static ActorDescriptor		ActorDescriptors[ ActorDescriptor::Count ];
static ElementDescriptor	ElementDescriptors[ static_cast<SizeType>( Element::Count ) ];

static Description description;


static Bool IsGuoBa(const Actor& actor)
{
	auto& descriptor = ActorDescriptors[ ActorDescriptor::GuoBa ];


	SizeType size = Minimum( actor.name.GetCount(), descriptor.name.GetCount() );
	if ( Memory::Equal( actor.name, descriptor.name, size ) )
		return true;

	return false;
}

static Bool IsYueGui(const Actor& actor)
{
	return !IsGuoBa(actor);
}

static Void WriteElement(Console* RenderTarget, Element element)
{
	auto& descriptor = ElementDescriptors[ static_cast<SizeType>(element) ];


	RenderTarget->SetColor( descriptor.foreground, descriptor.background );
	RenderTarget->Write( descriptor.name );

	RenderTarget->SetColor( Console::Color::White, Console::Color::Black );
}

static Void WriteActor(Console* RenderTarget, const Actor& actor)
{
	SizeType index		= IsGuoBa(actor) ? 0 : 1;
	auto& descriptor	= ActorDescriptors[index];
	
	RenderTarget->SetColor( descriptor.foreground, descriptor.background );

	for ( auto& footprint : actor.footprints )
	{
		RenderTarget->SetCursorPosition( footprint[0] * sizeof(Char16), footprint[1] );
		RenderTarget->Write( descriptor.footprint );
	}

	RenderTarget->SetCursorPosition( actor.position[0] * sizeof(Char16), actor.position[1] );
	RenderTarget->Write( descriptor.name );

	RenderTarget->SetColor( Console::Color::White, Console::Color::Black );
}
#pragma endregion


Void OnApplicationInitialize(Void* userParameter)
{
	{
		runtime = reinterpret_cast<Runtime*>(userParameter);
	}

	{
		for ( SizeType index = 0; index < FrameCount; index++ )
			RenderTargets.Add( new Console() );

		frameIndex = 0;
	}

	// load Assets
	{
		const Char8* ActorDescriptorDirectories[] =
		{
			"Asset/Actor/GuoBa.txt",
			"Asset/Actor/YueGui.txt",
		};

		const Char8* ElementDescriptorDirectories[] =
		{
			"Asset/Element/Empty.txt",
			"Asset/Element/Box.txt",
			"Asset/Element/Car.txt",
			"Asset/Element/Grass.txt",
			"Asset/Element/Food.txt",
			"Asset/Element/Mountain.txt",
			"Asset/Element/Tree.txt",
			"Asset/Element/LockA.txt",
			"Asset/Element/KeyA.txt",
			"Asset/Element/LockB.txt",
			"Asset/Element/KeyB.txt",
			"Asset/Element/LockC.txt",
			"Asset/Element/KeyC.txt",
			"Asset/Element/Actor.txt",
			"Asset/Element/Footprint.txt",
		};


		for ( SizeType index = 0; index < ActorDescriptor::Count; index++ )
		{
			auto directory = ActorDescriptorDirectories[index];

			ActorDescriptors[index] = LoadActorDescriptor(directory);
		}

		for ( SizeType index = 0; index < static_cast<SizeType>( Element::Count ); index++ )
		{
			auto directory = ElementDescriptorDirectories[index];

			ElementDescriptors[index] = LoadElementDescriptor(directory);
		}

		description = LoadDescription("Asset/Description.txt");
	}

	{
		const Char8* LevelDirectories[] =
		{
			"Asset/Level 1.txt",
			"Asset/Level 2.txt",
			"Asset/Level 3.txt",
			"Asset/Level 4.txt",
			"Asset/Level 5.txt",
			"Asset/Level 6.txt",
			"Asset/Level 7.txt",
			"Asset/Level 8.txt",
			"Asset/Level 9.txt",
		};

		for( auto directory : LevelDirectories )
			levels.Add( LoadLevel(directory) );

		selectLevelIndex = 0;
		SetStatus( &status, levels[selectLevelIndex] );
	}
}

Void OnUpdate()
{
	Bool isEscDown	= false;
	Bool isRDown	= false;
	Bool isSDown	= false;

	Bool isLeftArrowDown	= false;
	Bool isRightArrowDown	= false;
	Bool isDownArrowDown	= false;
	Bool isUpArrowDown		= false;
	{
		auto keys = StandardInput.ReadInputKeys();
		for (auto key : keys)
		{
			{
				Int32 value = static_cast<Int32>(key);

				Int32 begin	= static_cast<Int32>( Key::Alpha1 );
				Int32 end	= static_cast<Int32>( Key::Alpha9 );
				if ( value >= begin && value <= end )
				{
					selectLevelIndex	= value - begin;
					isRDown				= true;

					continue;
				}
			}

			switch (key)
			{
			case Key::Escape:		isEscDown			= true; break;
			case Key::R:			isRDown				= true; break;
			case Key::S:			isSDown				= true; break;
			case Key::LeftArrow:	isLeftArrowDown		= true; break;
			case Key::UpArrow:		isUpArrowDown		= true; break;
			case Key::RightArrow:	isRightArrowDown	= true; break;
			case Key::DownArrow:	isDownArrowDown		= true; break;
			}
		}
	}

	if (isEscDown)
		runtime->wantToQuit = true;

	if (isRDown)
	{
		SetStatus( &status, levels[selectLevelIndex] );
		return;
	}

	if ( status.isClear )
		return;

	if (isSDown)
	{
		status.selectActorIndex++;
		status.selectActorIndex %= status.actors.GetCount();

		status.selectedActor = &status.actors[ status.selectActorIndex ];
	}

	{
		Vector2Int offset = { 0, 0 };
		if (isLeftArrowDown)	offset = { -1,  0 };
		if (isRightArrowDown)	offset = {  1,  0 };
		if (isDownArrowDown)	offset = {  0, -1 };
		if (isUpArrowDown)		offset = {  0,  1 };

		TryMove( &status, offset[0], offset[1] );
	}

	{
		Bool isClear = true;
		for ( auto& actor : status.actors )
		{
			auto Equal = [](const Vector2Int& leftHandSide, const Vector2Int& rightHandSide)
				{
					return leftHandSide[0] == rightHandSide[0] && leftHandSide[1] == rightHandSide[1];
				};

			isClear &= Equal( actor.position, status.target );
		}

		status.isClear = isClear;
	}
}

Void OnRender()
{
	auto RenderTarget = RenderTargets[frameIndex];

	// frame begin
	RenderTarget->Clear();

	// render
	{
		for ( SizeType y = 0; y < GridsInY; y++ )
		{
			RenderTarget->SetCursorPosition(0, y);
			for ( SizeType x = 0; x < GridsInX; x++ )
			{
				Element element = status.slots[ GridsInX * y + x ].element;
				WriteElement(RenderTarget, element);
			}
		}

		for ( SizeType index = 0; index < status.actors.GetCount(); index++ )
		{
			auto& actors	= status.actors;
			auto current	= &actors[index];
			auto selected	= status.selectedActor;

			
			// highlighted
			if ( current == selected && actors.GetCount() >= 2 )
				RenderTarget->SetColor( Console::Color::Green | Console::Color::Blue, Console::Color::Black );

			SizeType yOffset = actors.GetCount() == 2 ?
				( GridsInY + 2 * ( 2 - index )	) :
				( GridsInY + 2 * 1				);
			
			RenderTarget->SetCursorPosition(0, yOffset);
			RenderTarget->Write( current->name );

			RenderTarget->SetCursorPosition( 0, yOffset - 1 );
			RenderTarget->Write( description.move );

			Char8 buffer[16];
			TryConvertInt32( buffer, sizeof(buffer), current->move );
			RenderTarget->Write(buffer);

			RenderTarget->SetColor( Console::Color::White, Console::Color::Black );
		}

		{
			SizeType yOffset = GridsInY + status.actors.GetCount() * 2 + 2;
			{
				Int32 number = selectLevelIndex + 1;

				Char8 buffer[16];
				TryConvertInt32( buffer, sizeof(buffer), number );

				RenderTarget->SetCursorPosition(0, yOffset);
				RenderTarget->Write( description.level );
				RenderTarget->Write(buffer);
			}

			yOffset += 2;
			if ( status.isClear )
			{
				RenderTarget->SetCursorPosition(0, yOffset);

				RenderTarget->SetColor( Console::Color::Red, Console::Color::Black );
				RenderTarget->Write( description.whenClear );

				RenderTarget->SetColor( Console::Color::White, Console::Color::Black );
			}
		}

		for ( auto& actor : status.actors )
			WriteActor(RenderTarget, actor);
	}

	// frame end
	{
		RenderTarget->SetAsActive();

		frameIndex++;
		frameIndex %= FrameCount;
	}
}