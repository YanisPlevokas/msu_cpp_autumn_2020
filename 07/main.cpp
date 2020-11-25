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
    assert(v.capacity() == 3);
    v.pop_back();
    assert(v.size() == 2);
    assert(v.capacity() == 3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v.empty() == false);
    v.clear();
    assert(v.empty() == true);
}

void test_2() //emplace_check
{
    Vector<pair<int, bool>> v;
    v.emplace_back(1, false);
    assert(v[0].first == 1);
    assert(v[0].second == false);
}

void test_3() //iter_check
{
    Vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }
    int sum = 0;
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


int main()
{
    test_1();
    test_2();
    test_3();
    cout << "Success!" << endl;
    return 0;
}