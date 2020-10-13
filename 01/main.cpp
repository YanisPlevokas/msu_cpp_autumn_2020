#include <iostream>
#include "allocator_header.hpp"


void DefaultWorkTest()
{
	Allocator test;
	test.makeAllocator(13);
	char* test_mem_1 = test.alloc(7);
	char* test_mem_2 = test.alloc(4);
	if (test_mem_1 == nullptr || test_mem_2 == nullptr)
	{
		std::cout << "Problem DefaultWorkTest\n";
	}
	test.reset();

	if (test.offset != 0)
	{
		std::cout << "Problem DefaultWorkTest\n";
	}
}

void DoubleMakeAlloc()
{
	Allocator test;
	test.makeAllocator(20);
	test.makeAllocator(30);
	if (test.maximumLength != 20)
	{
		std::cout << "Problem DoubleMakeAlloc\n";
	}
}

void RequiresMoreMemoryThanAllocated()
{
	Allocator test;
	test.makeAllocator(20);
	char* testing_mem = test.alloc(21);
	if (testing_mem != nullptr)
	{
		std::cout << "Problem RequiresMoreMemoryThanAllocated\n";
	}
}

void ResetBeforeAllocate()
{
	Allocator test;
	test.makeAllocator(5);
	test.reset();
	if (test.memAllocated != true)
	{
		std::cout << "Problem ResetBeforeAllocate\n";
	}
}



int main()
{
	try
	{
		DefaultWorkTest();
		DoubleMakeAlloc();
		RequiresMoreMemoryThanAllocated();
		ResetBeforeAllocate();
	}
	catch (std::bad_alloc& problem)
	{
		std::cerr << "bad_alloc caught\n";
	}
	catch (...)
	{
		std::cout << "unexpected problem occured\n";
	}
	std::cout << "Everything is fine!\n";

	return 0;
}
