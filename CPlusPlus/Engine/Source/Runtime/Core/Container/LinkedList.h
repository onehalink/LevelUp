#pragma once

#include "../Mathematics/Math.h"

#include "../System/Allocator.h"



namespace Engine
{
	template<typename T>
	class LinkedList
	{
	public:
		struct Node
		{
			Node*	next;
			T		element;


			Node();
		};


		LinkedList();
		LinkedList(const LinkedList<T>& other);
		LinkedList(LinkedList<T>&& other);
		~LinkedList();
		

		Void Add(Node* node);
		Void InsertAt(SizeType index, Node* node);
		Void RemoveAt(SizeType index);

		Void Clear();


		Node* GetHead();
		const Node* GetHead() const;
		SizeType GetCount() const;


		LinkedList<T>& operator=(const LinkedList<T>& other);
		LinkedList<T>& operator=(LinkedList<T>&& other);

		Node* operator[](SizeType index);
		const Node* operator[](SizeType index) const;
	public:
		class Iterator
		{
		public:
			Iterator();
			Iterator(Node* node);


			Node* operator->();
			Node& operator*();

			Iterator& operator++();
			Iterator operator++(Int32);

			Bool operator==(const Iterator& other) const;
			Bool operator!=(const Iterator& other) const;
		private:
			Node* node;
		};
		

		Iterator begin();
		Iterator end();

		const Iterator begin() const;
		const Iterator end() const;
	private:
		Void CopyFrom(const LinkedList<T>& instance);
	private:
		Node* head;

		SizeType count;
	};


#pragma region Details
	template<typename T>
	LinkedList<T>::Node::Node()
		: next(nullptr), element( T() )
	{

	}

	template<typename T>
	LinkedList<T>::LinkedList()
		: head(nullptr), count(0)
	{

	}

	template<typename T>
	LinkedList<T>::LinkedList(const LinkedList<T>& other)
	{
		CopyFrom(other);
	}

	template<typename T>
	LinkedList<T>::LinkedList(LinkedList<T>&& other)
	{
		head	= other.head;
		count	= other.count;

		other.head = nullptr;
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		Node* node = head;
		while (node)
		{
			Node* next = node->next;

			Allocator::Release(node);
			node = next;
		}
	}

	template<typename T>
	Void LinkedList<T>::Add(Node* node)
	{
		if ( count == 0 )
			head = node;
		else
			( *this )[ count - 1 ]->next = node;

		count++;
	}

	template<typename T>
	Void LinkedList<T>::InsertAt(SizeType index, Node* node)
	{
		if ( index == 0 )
		{
			node->next = head;

			head = node;
		}
		else
		{
			Node* previous = ( *this )[ index - 1 ];

			node->next		= previous->next;
			previous->next	= node;
		}
	
		count++;
	}

	template<typename T>
	Void LinkedList<T>::RemoveAt(SizeType index)
	{
		Node* removed;
		if ( index == 0 )
		{
			removed = head;

			head = removed->next;
		}
		else
		{
			Node* previous = ( *this )[ index - 1 ];

			removed			= previous->next;
			previous->next	= removed->next;
		}

		Allocator::Release(removed);
		count--;
	}

	template<typename T>
	Void LinkedList<T>::Clear()
	{
		this->~LinkedList();
		count = 0;
	}

	template<typename T>
	typename LinkedList<T>::Node* LinkedList<T>::GetHead()
	{
		return head;
	}

	template<typename T>
	const typename LinkedList<T>::Node* LinkedList<T>::GetHead() const
	{
		return head;
	}

	template<typename T>
	SizeType LinkedList<T>::GetCount() const
	{
		return count;
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
	{
		this->~LinkedList();
		CopyFrom(other);

		return *this;
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other)
	{
		Swap( &head,		&other.head		);
		Swap( &other.count,	&other.count	);

		return *this;
	}

	template<typename T>
	typename LinkedList<T>::Node* LinkedList<T>::operator[](SizeType index)
	{
		Node* ret = head;

		SizeType begin	= 1;
		SizeType end	= index + 1;
		for ( SizeType iteration = begin; iteration < end; iteration++ )
			ret = ret->next;

		return ret;
	}

	template<typename T>
	const typename LinkedList<T>::Node* LinkedList<T>::operator[](SizeType index) const
	{
		Node* ret = head;

		SizeType begin	= 1;
		SizeType end	= index + 1;
		for ( SizeType iteration = begin; iteration < end; iteration++ )
			ret = ret->next;

		return ret;
	}

	template<typename T>
	LinkedList<T>::Iterator::Iterator()
		: node(nullptr)
	{

	}

	template<typename T>
	LinkedList<T>::Iterator::Iterator(Node* node)
		: node(node)
	{

	}

	template<typename T>
	typename LinkedList<T>::Node* LinkedList<T>::Iterator::operator->()
	{
		return node;
	}

	template<typename T>
	typename LinkedList<T>::Node& LinkedList<T>::Iterator::operator*()
	{
		return *node;
	}

	template<typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
	{
		node = node->next;

		return *this;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(Int32)
	{
		Node* ret = node;

		++( *this );

		return ret;
	}

	template<typename T>
	Bool LinkedList<T>::Iterator::operator==(const Iterator& other) const
	{
		return node == other.node;
	}

	template<typename T>
	Bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::begin()
	{
		return head;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::end()
	{
		return nullptr;
	}

	template<typename T>
	const typename LinkedList<T>::Iterator LinkedList<T>::begin() const
	{
		return head;
	}

	template<typename T>
	const typename LinkedList<T>::Iterator LinkedList<T>::end() const
	{
		return nullptr;
	}

	template<typename T>
	Void LinkedList<T>::CopyFrom(const LinkedList<T>& instance)
	{
		count = 0;
		for (auto node : instance)
		{
			Node* temporary		= Allocator::Allocate<Node>(1);
			temporary->element	= node->element;

			Add(temporary);
		}
	}
#pragma endregion
}