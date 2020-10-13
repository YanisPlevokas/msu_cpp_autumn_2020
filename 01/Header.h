#pragma once
#include <iostream>


class Allocator
{
private:
	char* pointer;
	bool memAllocated;
public:
	size_t currSize;
	size_t offset;
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};