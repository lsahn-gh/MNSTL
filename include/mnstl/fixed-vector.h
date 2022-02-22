#pragma once

#include <iostream>
#include <cassert>

#define TRY_INCLUDING_INTERNAL_H
#include "internal.h"
#undef TRY_INCLUDING_INTERNAL_H

MNSTL_NAMESPACE_BEGIN

template <typename T, size_t N>
class FixedVector
{
public:
    FixedVector();

    bool Add(const T& value);
    void Clear();
    size_t GetSize() const;
    size_t GetCapacity() const;

    T& operator[](const int index);

private:
    size_t mSize;
    T mArray[N];
};

// Implementations
template <typename T, size_t N>
FixedVector<T, N>::FixedVector()
    : mSize(0)
{
}

template <typename T, size_t N>
bool FixedVector<T, N>::Add(const T& value)
{
    if (mSize >= N)
    {
        return false;
    }

    mArray[mSize++] = value;
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
    return N;
}

template <typename T, size_t N>
T& FixedVector<T, N>::operator[](const int index)
{
    assert((0 <= index) && (index < N));
    /* should we deal with 'mSize == 0' case? */

    return mArray[index];
}

MNSTL_NAMESPACE_END