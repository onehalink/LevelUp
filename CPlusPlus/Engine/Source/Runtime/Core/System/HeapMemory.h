#pragma once

#include "../Mathematics/Math.h"

#include "Allocator.h"
#include "Memory.h"



namespace Engine
{
	class ENGINE_API HeapMemory
	{
	public:
		HeapMemory();
		HeapMemory(Void* buffer, SizeType byteCount);
		HeapMemory(SizeType preallocated /** in bytes */);
		HeapMemory(const HeapMemory& other);
		HeapMemory(HeapMemory&& other);
		~HeapMemory();


		Void* GetBuffer();
		const Void* GetBuffer() const;
		SizeType GetByteCount() const;


		HeapMemory& operator=(const HeapMemory& other);
		HeapMemory& operator=(HeapMemory&& other);
	private:
		Void CopyFrom(const HeapMemory& instance);
	private:
		Void*		buffer;
		SizeType	byteCount;
	};
}