#include <iostream>

#ifndef H_ALLOCATOR
#define H_ALLOCATOR

class Allocator
{
private:
	char* pointer;
public:
	bool memAllocated;
	size_t maximumLength;
	size_t offset;
	Allocator();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
	~Allocator();
};

#endif