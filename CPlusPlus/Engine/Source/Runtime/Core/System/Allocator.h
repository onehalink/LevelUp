#pragma once

#include "../Template.h"



namespace Engine
{
	class Allocator
	{
	public:
		template<typename T> static T* Allocate(SizeType count);
		template<typename T> static Void Release(T* pointer);
	};


#pragma region Details
	template<typename T>
	T* Allocator::Allocate(SizeType count)
	{
		static_assert( IsConstructible<T>::Value );


		return new T[count];
	}

	template<typename T>
	Void Allocator::Release(T* pointer)
	{
		static_assert( !TypesAreSame<T, Void>::Value );


		delete[] pointer;
	}
#pragma endregion
}