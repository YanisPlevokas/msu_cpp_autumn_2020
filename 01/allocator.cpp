#include <iostream>
#include "allocator_header.hpp"

Allocator::Allocator()
{
	memAllocated = false;
	offset = 0;
	maximumLength = 0;
	pointer = nullptr;
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (memAllocated != true) 
	{
		pointer = new char[maxSize];
		offset = 0;
		memAllocated = true;
		maximumLength = maxSize;
	}
}

char* Allocator::alloc(size_t size)
{
	if ((size + offset <= maximumLength) && (size != 0))
	{
		offset += size;
		return pointer + offset - size;
	}
	else
	{
		return nullptr;
	}
}

void Allocator::reset()
{
	if (memAllocated == true)
	{
		offset = 0;
	}

}

Allocator::~Allocator()
{
	if (pointer != nullptr)
		delete pointer;
}
