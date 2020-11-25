#pragma once
#include <iostream>
using namespace std;

template <class T>
class Allocator
{
public:

    T* allocate(size_t size)
    {
        return new T[size];
    }

    void deallocate(T* pointer)
    {
        delete[] pointer;
    }

    void del(T* pointer) 
    {
        pointer->~T();
    }
};



template <class T>
class Iterator
{
private:
    T* my_pointer;
    bool reverse_flag;
public:
    Iterator(T* pointer): my_pointer(pointer) {}

    Iterator(T* pointer, bool flag): my_pointer(pointer), reverse_flag(flag) {}

    T& operator*()
    {
        return *my_pointer;
    }

    const T& operator*() const
    {
        return *my_pointer;
    }

    T& operator[](const size_t i)
    {
    	if (reverse_flag)
        	return my_pointer[syzeof(my_pointer) - i - 1];
        else
        	return my_pointer[i];
    }

    const T& operator[](const size_t i) const
    {
        if (reverse_flag)
        	return my_pointer[syzeof(my_pointer) - i - 1];
        else
        	return my_pointer[i];
    }

    Iterator<T>& operator++()
    {
    	if (reverse_flag)
        	--my_pointer;
        else
        	++my_pointer;
        return * this;
    }

    Iterator<T>& operator--()
    {
        if (reverse_flag)
        	++my_pointer;
        else
        	--my_pointer;
        return * this;
    }

    Iterator<T> operator++(int)
    {
    	Iterator<T> tmp = *this;
    	if (reverse_flag)
    		--my_pointer;
    	else
    		++my_pointer;
        return tmp;
    }

    Iterator<T> operator--(int)
    {
    	Iterator<T> tmp = *this;
    	if (reverse_flag)
    		++my_pointer;
    	else
    		--my_pointer;
        return tmp;
    }

    bool operator>(const Iterator<T>& second_vec) const
    {
    	if (!(reverse_flag))
        	return my_pointer > second_vec.my_pointer;
        else
        	return my_pointer < second_vec.my_pointer;
    }

    bool operator==(const Iterator<T>& second_vec) const
    {
        return my_pointer == second_vec.my_pointer;
    }

    bool operator>=(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return my_pointer >= second_vec.my_pointer;
        else
        	return my_pointer <= second_vec.my_pointer;
    }

    bool operator<(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return !(*this >= second_vec);
        else
        	return !(*this <= second_vec);
    }

    bool operator<=(const Iterator<T>& second_vec) const
    {
        if (!(reverse_flag))
        	return !(*this > second_vec);
        else
        	return !(*this < second_vec);
    }

    bool operator!=(const Iterator<T>& second_vec) const
    {
        return (!(*this == second_vec));
    }

    Iterator<T>& operator+=(int value)
    {
    	if (!(reverse_flag))
        	my_pointer += value;
        else
        	my_pointer -= value;
        return * this;
    }

    Iterator<T>& operator-=(int value)
    {
        if (!(reverse_flag))
        	my_pointer -= value;
        else
        	my_pointer += value;
        return * this;
    }

    Iterator<T> operator+(int value)
    {
        Iterator<T> save = * this;
        if (!(reverse_flag))
        	return save + value;
        else
        	return save - value;
    }

    Iterator<T> operator-(int value)
    {
        Iterator<T> save = * this;
        if (!(reverse_flag))
        	return save - value;
        else
        	return save + value;
    }

};




template <class T, class Allocator = Allocator<T>>
class Vector
{
private:
    size_t max_size;
    size_t vec_size;
    T* my_pointer;
    Allocator alloc;
public:

	Vector(): max_size(0), vec_size(0), my_pointer(nullptr), alloc() {}

    Vector(const size_t new_size): max_size(new_size), vec_size(new_size), alloc()
    {
        if (new_size < 0)
            throw runtime_error("non-positive size");
        my_pointer = alloc.allocate(max_size);
    }

    Vector(const Vector& second_vector): max_size(second_vector.max_size), vec_size(second_vector.vec_size), alloc()
    {
        my_pointer = alloc.allocate(max_size);
        for (size_t i = 0; i < vec_size; i++)
        {
            my_pointer[i] = second_vector[i];
        }
    }

    Vector(Vector&& second_vector): max_size(second_vector.max_size), vec_size(second_vector.vec_size), alloc()
    {
        my_pointer = alloc.allocate(max_size);
        for (size_t i = 0; i < vec_size; i++)
        {
            my_pointer[i] = move(second_vector[i]);
        }
    }

    ~Vector()
    {
        vec_size = 0;
        max_size = 0;
        if (my_pointer != nullptr)
        {
            alloc.deallocate(my_pointer);
        }
    }

    Iterator<T> begin()
    {
        return Iterator<T>(my_pointer, false);
    }

    Iterator<T> rbegin()
    {
        return Iterator<T>(my_pointer + vec_size, true);
    }

    Iterator<T> end()
    {
        return Iterator<T>(my_pointer + vec_size, false);
    }

    Iterator<T> rend()
    {
        return Iterator<T>(my_pointer, true);
    }

    T& operator[](size_t i)
    {
        if (i > vec_size || i < 0)
        {
            throw runtime_error("index out of range");
        }
        return my_pointer[i];
    }

    const T& operator[](size_t i) const
    {
        if (i > vec_size || i < 0)
        {
            throw runtime_error("index out of range");
        }
        return my_pointer[i];
    }

    void push_back(const T& new_value)
    {
        if (vec_size >= max_size)
        {
            max_size = max_size * 2 + 1;
            reallocate();
        }
        my_pointer[vec_size] = new_value;
        vec_size++;;
    }

    void push_back(T && new_value)
    {
        if (vec_size >= max_size)
        {
            max_size = max_size * 2 + 1;
            reallocate();
        }
        my_pointer[vec_size] = move(new_value);
        vec_size++;
    }

    void reallocate()
    {
        T* new_pointer = alloc.allocate(max_size);
        for (size_t i = 0; i < vec_size; i++)
        {
            new_pointer[i] = my_pointer[i];
        }
        alloc.deallocate(my_pointer);
        my_pointer = new_pointer;
    }

    void pop_back()
    {
        if (vec_size <= 0)
        {
            throw runtime_error("negative size");
        }
        vec_size--;
        alloc.del(my_pointer + vec_size);
    }

    template <class... Args>
    void emplace_back(Args&& ... args)
    {
        this->push_back(T(forward<Args>(args)...));
    }

    void clear()
    {
        deleter(0);
        vec_size = 0;
        max_size = 0;
    }

    void deleter(size_t offset)
    {
        for (T* tmp = my_pointer + offset; tmp < my_pointer + vec_size; tmp++)
        {
            alloc.del(tmp);
        }
    }

    void resize(size_t new_size)
    {
        if (new_size < vec_size)
        {
            deleter(new_size);
            vec_size = new_size;
        }
        else
        {
            if (new_size > max_size)
            {
                max_size = new_size * 2 + 1;
                reallocate();
            }
            vec_size = new_size;
        }
    }

    void reserve(size_t new_size)
    {
        if (new_size > max_size)
        {
            max_size = new_size;
            reallocate();
        }
        vec_size = new_size;
    }

    size_t capacity() const
    {
        return max_size;
    }

    bool empty() const
    {
        return vec_size == 0;
    }

    size_t size() const
    {
        return vec_size;
    }

};