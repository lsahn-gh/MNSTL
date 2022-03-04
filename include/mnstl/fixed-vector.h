#pragma once

#include <iostream>
#include <cassert>

namespace mnstl
{

template <typename T, size_t N>
class FixedVector
{
public:
    FixedVector();
    ~FixedVector();

    bool Add(const T& value);
    void Clear();
    size_t GetSize() const;
    size_t GetCapacity() const;

    T& operator[](const int index);

private:
    size_t mSize;
    size_t mCapacity;
    T* mBuffer;
};

// Implementations
template <typename T, size_t N>
FixedVector<T, N>::FixedVector()
    : mSize(0)
    , mCapacity(N)
{
    mBuffer = new T[N];
}

template <typename T, size_t N>
FixedVector<T, N>::~FixedVector()
{
    delete[] mBuffer;
}

template <typename T, size_t N>
bool FixedVector<T, N>::Add(const T& value)
{
    if (mSize >= mCapacity)
    {
        return false;
    }

    mBuffer[mSize++] = value;
    return true;
}

template <typename T, size_t N>
void FixedVector<T, N>::Clear()
{
    mSize = 0;
}

template <typename T, size_t N>
size_t FixedVector<T, N>::GetSize() const
{
    return mSize;
}

template <typename T, size_t N>
size_t FixedVector<T, N>::GetCapacity() const
{
    return mCapacity;
}

template <typename T, size_t N>
T& FixedVector<T, N>::operator[](const int index)
{
    assert((0 <= index) && (index < mCapacity));
    /* should we deal with 'mSize == 0' case? */

    return mBuffer[index];
}

} /* namespace mnstl */