#include "pool.h"
#include <iostream>

struct A {};

void foo(const A&) {}

void test_1()
{
	ThreadPool pool(8);
	auto task1 = pool.exec(foo, A());
	task1.get();
	auto task2 = pool.exec([]() { return 1; });
	assert( task2.get() == 1);
}
void test_2()
{
	ThreadPool pool(3);
	bool IsItHard = true;
	auto task1 = [IsItHard](bool VeryHardQuestion)
	{
		return (IsItHard == VeryHardQuestion);
	};
	auto result_1 = pool.exec(task1, true);
    assert(result_1.get() == true);
}
void test_3()
{
	ThreadPool pool(3);
	for (int i = 0; i < 3; i++)
	{
		auto result = pool.exec([](){return 44;});
		assert(result.get() == 44);
	}
}

int main()
{
	test_1();
	test_2();
	test_3();
	std::cout << "OK\n";
	return 0;
}