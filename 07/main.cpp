#include "vector.hpp"
#include <iostream>
using namespace std;

void test_1() //common_clear_check
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    assert(v.size() == 3);
    assert(v.capacity() == 7); // 3 * 2 + 1
    v.pop_back();
    assert(v.size() == 2);
    assert(v.capacity() == 7);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v.empty() == false);
    v.clear();
    assert(v.empty() == true);
}

void test_2() //iter_check both ways
{
    Vector<int> v;
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }
    for (auto i = v.begin(); i < v.end(); i++)
    {
        sum += *i;
    }
    assert(sum == 10);
    v.clear();
    sum = 0;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
        sum += i;
    }
    for (auto i = v.rbegin(); i != v.rend(); i++)
    {
        sum -= *i;
    }
    assert(sum == 0);

}

void test_3()
{
    Vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }
    v.resize(2);
    assert(v.size() == 2);
    assert(v.capacity() == 7);
    v.resize(10);
    assert(v.size() == 2);
    assert(v.capacity() == 21); // 21 because 10 * 2 + 1
}

void test_4()
{
	Vector<int> v;
	for (int i = 0; i < 6; i++)
    {
        v.push_back(i);
    }
    // capacity = 15, 7 * 2 + 1
    assert(v.size() == 6);
    assert(v.capacity() == 15);
    v.reserve(20);
    assert(v.size() == 6);
    assert(v.capacity() == 20);
}

void test_5() //emplace_check
{
    Vector<pair<int, bool>> v;
    v.emplace_back(1, false);
    assert(v[0].first == 1);
    assert(v[0].second == false);
}


int main()
{
	try
	{
		cout << "Start\n";
		test_1();
	    test_2();
	    test_3();
	    test_4();
	    test_5();
	}
	catch (runtime_error& e)
	{
		cout << "runtime_error\n";
	}
	catch (...)
	{
		cout << "Kinda problem\n";
		exit(-1);
	}
	cout << "Everything is ok\n";
    return 0;
}