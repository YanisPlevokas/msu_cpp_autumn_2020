#include <iostream>
#include "Header.h"


Allocator::Allocator()
{
	memAllocated = false;
	offset = 0;
	currSize = 0;
	pointer = NULL;
}

void Allocator::makeAllocator(size_t maxSize)
{
	if (memAllocated == true)
	{
		throw "already allocated memory";
	}
	if (maxSize <= 0)
	{
		throw "makeAllocator problem\n";
	}
	pointer = new char[maxSize];
	if (pointer == 0x0)
	{
		std::cout << "Insufficient memory" << std::endl;
		throw "makeAllocator problem\n";
	}
	offset = 0;
	memAllocated = true;
	currSize = maxSize;
}

char* Allocator::alloc(size_t size)
{
	if ((size + offset <= currSize) && (size > 0))
	{
		offset += size;
		return pointer + offset - size;
	}
	else if (size <= 0)
	{
		throw "non-positive size allocation";
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

void Allocator::reset()
{
	if (memAllocated == false)
	{
		throw "Memory has not been allocated yet";
	}
	else
	{
		offset = 0;
	}

}
Allocator::~Allocator()
{
	if (pointer != NULL)
		delete pointer;
}