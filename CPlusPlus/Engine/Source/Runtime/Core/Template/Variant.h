#pragma once

#include "SelectNthFromParameterPack.h"



namespace Engine
{
	template<typename ...Ts>
	struct Variant;


	template<>
	struct Variant<> { };


	template<typename First, typename ...Ts>
	struct Variant<First, Ts ...>
	{
		union
		{
			First			head;
			Variant<Ts ...>	tail;
		};


		First& Get();
	};


	template<SizeType Index, typename ...Ts>
	typename SelectNthFromParameterPack<Index, Ts...>::Type& Visit(Variant<Ts ...>& instance);


#pragma region Details
	template<typename First, typename ...Ts>
	First& Variant<First, Ts...>::Get()
	{
		return head;
	}

	template<SizeType Index, typename ...Ts>
	typename SelectNthFromParameterPack<Index, Ts...>::Type& Visit(Variant<Ts...>& instance)
	{
		static_assert( Index < sizeof...(Ts) );
		static_assert( Index < 16 );


		if constexpr ( Index == 0 )
			return instance.Get();
		else if constexpr ( Index == 1 )
			return instance.tail.Get();
		else if constexpr ( Index == 2 )
			return instance.tail.tail.Get();
		else if constexpr ( Index == 3 )
			return instance.tail.tail.tail.Get();
		else if constexpr ( Index == 4 )
			return instance.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 5 )
			return instance.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 6 )
			return instance.tail.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index == 7 )
			return instance.tail.tail.tail.tail.tail.tail.tail.Get();
		else if constexpr ( Index < 16 )
			return Visit<Index - 8>( instance.tail.tail.tail.tail.tail.tail.tail.tail );
	}
#pragma endregion
}