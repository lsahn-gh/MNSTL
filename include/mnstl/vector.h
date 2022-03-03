#pragma once

#include <cassert>
#include <iostream>
#include <algorithm>

#define TRY_INCLUDING_INTERNAL_H
#include "internal.h"
#undef TRY_INCLUDING_INTERNAL_H

MNSTL_NAMESPACE_BEGIN

// VectorBase has the following characteristics
// 1. [mBegin, mEnd) type.
// 2. 
template <typename T>
class VectorBase
{
public:
    enum { MIN_CAPACITY = 8 };

    size_t capacity() const;
    size_t size() const;

protected:
    T*                      mBegin;
    T*                      mEnd;
    std::pair<T*, void*>    mCapacity;

    VectorBase();
    VectorBase(size_t n);

    ~VectorBase();

    T*& GetCapacityPtrRef();
};


// 'vector' has the following characteristics,
// 1. ...
template <typename T>
class vector : public VectorBase<T>
{
    typedef VectorBase<T>   base_type;
    typedef vector<T>       this_type;

public:
    typedef T               value_type;

    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef T*              reverse_iterator;
    typedef const T*        const_reverse_iterator;

public:
    vector();
    vector(const size_t n);
    vector(const this_type& rhs);

    ~vector();

    // extra operators
    T&          at(const size_t index);
    const T&    at(const size_t index) const;

    T&          front();
    const T&    front() const;

    T&          back();
    const T&    back() const;

    void        push_back(const value_type& value);

    iterator                begin();
    const_iterator          begin() const;
    reverse_iterator        rbegin();
    const_reverse_iterator  rbegin() const;

    iterator                end();
    const_iterator          end() const;
    reverse_iterator        rend();
    const_reverse_iterator  rend() const;

    bool        empty() const;

    void        resize(const size_t n);
    void        resize(const size_t n, const value_type& value);
    void        reserve(const size_t n);

private:
};

/* -- VectorBase -- */
template <typename T>
VectorBase<T>::VectorBase()
    : mBegin(nullptr)
    , mEnd(nullptr)
    , mCapacity(nullptr, nullptr)
{
}

template <typename T>
VectorBase<T>::VectorBase(size_t n)
    : mCapacity(nullptr, nullptr)
{
    if (n < MIN_CAPACITY)
    {
        n = MIN_CAPACITY;
    }

    mBegin = reinterpret_cast<T*>(malloc(sizeof(T) * n));
    mEnd = mBegin;
    GetCapacityPtrRef() = mBegin + n;
}

template <typename T>
VectorBase<T>::~VectorBase()
{
    if (mBegin != nullptr)
    {
        free(mBegin);
    }

    mBegin = nullptr;
    mEnd = nullptr;
    GetCapacityPtrRef() = nullptr;
}

template <typename T>
T*& VectorBase<T>::GetCapacityPtrRef()
{
    return mCapacity.first;
}

template <typename T>
size_t VectorBase<T>::capacity() const
{
    return static_cast<size_t>(mCapacity.first - mBegin);
}

template <typename T>
size_t VectorBase<T>::size() const
{
    return static_cast<size_t>(mEnd - mBegin);
}


/* -- vector -- */
template <typename T>
vector<T>::vector()
    : base_type()
{
    // empty
}

template <typename T>
vector<T>::vector(const size_t n)
    : base_type(n)
{
    // empty
}

template <typename T>
vector<T>::vector(const this_type& rhs)
    : base_type(rhs.capacity())
{
    this->mEnd = std::copy(rhs.mBegin, rhs.mEnd, this->mBegin);
}

template <typename T>
vector<T>::~vector()
{
    // empty
}

template <typename T>
inline T& vector<T>::at(const size_t index)
{
    return *(this->mBegin + index);
}

template <typename T>
inline const T& vector<T>::at(const size_t index) const
{
    return *(this->mBegin + index);
}

template <typename T>
T& vector<T>::front()
{
    return *(this->mBegin);
}

template <typename T>
const T& vector<T>::front() const
{
    return *(this->mBegin);
}

template <typename T>
T& vector<T>::back()
{
    return *(this->mEnd - 1);
}

template <typename T>
const T& vector<T>::back() const
{
    return *(this->mEnd - 1);
}

// TODO must be called under lock!
template <typename T>
void vector<T>::push_back(const T& value)
{
    if (this->mEnd >= this->GetCapacityPtrRef())
    {
        const size_t NEW_CAPACITY = (this->capacity() * 2);
        T* newBegin = reinterpret_cast<T*>(malloc(sizeof(T) * NEW_CAPACITY));
        T* newEnd = std::copy(this->mBegin, this->mEnd, newBegin);

        free(this->mBegin);

        // NOT SAFE for multi-threaded program!

        this->mBegin = newBegin;
        this->mEnd = newEnd;
        this->GetCapacityPtrRef() = (this->mBegin + NEW_CAPACITY);
    }

    *(this->mEnd) = value;
    (this->mEnd)++;
}

template <typename T>
typename vector<T>::iterator
vector<T>::begin()
{
    return this->mBegin;
}

template <typename T>
typename vector<T>::const_iterator
vector<T>::begin() const
{
    return this->mBegin;
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rbegin()
{
    // TODO
    return this->mBegin;
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::rbegin() const
{
    // TODO
    return this->mBegin;
}

template <typename T>
typename vector<T>::iterator
vector<T>::end()
{
    return this->mEnd;
}

template <typename T>
typename vector<T>::const_iterator
vector<T>::end() const
{
    return this->mEnd;
}

template <typename T>
typename vector<T>::reverse_iterator
vector<T>::rend()
{
    return this->mEnd;
}

template <typename T>
typename vector<T>::const_reverse_iterator
vector<T>::rend() const
{
    return this->mEnd;
}

template <typename T>
bool vector<T>::empty() const
{
    return (this->size() == 0);
}

template <typename T>
void vector<T>::resize(const size_t n)
{
    T *newBegin = reinterpret_cast<T*>(malloc(sizeof(T) * n));
    T *newEnd = std::copy(this->mBegin, (n >= this->size()) ? this->mEnd : (this->mBegin + n), newBegin);

    free(this->mBegin);

    // NOT SAFE for multi-threaded program!

    this->mBegin = newBegin;
    this->mEnd = newEnd;
    this->GetCapacityPtrRef() = (this->mBegin + n);
}

template <typename T>
void vector<T>::reserve(const size_t n)
{
    if (this->mBegin != nullptr)
    {
        free(this->mBegin);

        this->mBegin = nullptr;
        this->mEnd = nullptr;
        this->GetCapacityPtrRef() = nullptr;
    }

    this->mBegin = reinterpret_cast<T*>(malloc(sizeof(T) * n));
    this->mEnd = this->mBegin;
    this->GetCapacityPtrRef() = this->mBegin + n;
}

MNSTL_NAMESPACE_END