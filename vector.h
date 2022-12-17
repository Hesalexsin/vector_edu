#ifndef VECTOR_H
#define VECTOR_H

#pragma once
#include <initializer_list>
#include <iterator>
#include <memory>

template <typename T, typename A = std::allocator<T>>
class new_vector
{
    A alloc;
    int sz;
    T* elem;
    int space;

public:
    new_vector();

    explicit new_vector(int s);
    new_vector(std::initializer_list<T> lst);

    new_vector(const new_vector& a);
    new_vector& operator=(const new_vector& a);

    new_vector(new_vector&& a);

    new_vector operator=(new_vector&& a);

    ~new_vector() { delete[] elem; }

    T& operator[ ](int i) { return elem[i]; }

    int capacity() const { return space; }
    int size() const { return sz; }

    void reserve(int newalloc);

    void resize(int newsize, const T& val = T())
    {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i)
            alloc.construct(&elem[i], val);
        for (int i = sz; i < newsize; ++i)
            alloc.destroy(&elem[i]);
        sz = newsize;
    }
    void push_back(const T& d);
};

template <typename T, typename A>
new_vector<T,A>::new_vector():
        sz{0}, elem{nullptr}, space{0} {}

template <typename T, typename A>
new_vector<T,A>::new_vector(int s):
        sz{s}, space{s},
        elem{new T[s]}
{
        for(int i=0; i<s; ++i)
            elem[i]=0;
}

template <typename T, typename A>
new_vector<T,A>::new_vector(std::initializer_list<T> lst):
        sz{ static_cast<int>(lst.size())},
        elem{new T[lst.size()]},
        space{sz}
{
        std::copy(lst.begin(), lst.end(), elem);
}

template <typename T, typename A>
new_vector<T,A>::new_vector(const new_vector& a):
        sz{a.sz},
        elem{new T[a.sz]},
        space{sz}
{
        std::copy(a.elem, a.elem + a.sz, elem);
}

template <typename T, typename A>
new_vector<T,A>& new_vector<T,A>::operator=(const new_vector& a)
{
        if (this == &a)
            return *this;
        if (a.sz <= space)
        {
            std::copy(a.elem, a.elem + a.sz, elem);
            sz = a.sz;
            return *this;
        }
        T* p = new T[a.size()];
        std::copy(a.elem, a.elem + a.sz, p);
        delete[] elem;
        elem = p;
        space = sz = a.sz;
        return *this;
}

template <typename T, typename A>
new_vector<T,A>::new_vector(new_vector&& a):
        sz{a.sz}, elem{a.elem}, space{sz}
{
        a.sz = 0;
        a.elem = nullptr;
}

template <typename T, typename A>
new_vector<T,A> new_vector<T,A>::operator=(new_vector&& a)
{
        delete[] elem;
        elem = a.elem;
        a.elem = nullptr;
        sz = a.sz;
        a.sz = 0;
        return *this;
}


template<typename T, typename A>
void new_vector<T,A>::reserve(int newalloc)
{
        if (newalloc <= space) return;
        T* p = alloc.allocate(newalloc);
        for (int i = 0; i < sz; ++i)
            alloc.construct(&p[i], elem[i]);
        for (int i = 0; i < sz; ++i)
            alloc.destroy(&elem[i]);
        alloc.deallocate(elem, space);
        elem = p;
        space = newalloc;
}


template<typename T, typename A>
void new_vector<T,A>::push_back(const T& d)
{
        if (!space)
            reserve(8);
        else if (sz == space)
            reserve(2*space);
        elem[sz] = d;
        ++sz;
}

#endif // VECTOR_H
