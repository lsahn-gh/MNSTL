#pragma once

#include <iostream>
#include <cassert>

#include "vector.h"

namespace mnstl
{

template <typename T, size_t N, typename FixedAllocator = std::allocator<T> >
class fixed_vector : public vector<T, FixedAllocator>
{
    typedef vector<T, FixedAllocator>               base_type;
    typedef fixed_vector<T, N, FixedAllocator>      this_type;

public:
    typedef T                                       value_type;
    typedef T*                                      pointer;
    typedef const T*                                const_pointer;
    typedef T&                                      reference;
    typedef const T&                                const_reference;
    typedef T*                                      iterator;
    typedef const T*                                const_iterator;
    typedef mnstl_reverse_iterator<iterator>        reverse_iterator;
    typedef mnstl_reverse_iterator<const_iterator>  const_reverse_iterator;
    typedef typename base_type::allocator_type      allocator_type;
    typedef typename base_type::size_type           size_type;
    typedef typename base_type::difference_type     difference_type;

    using base_type::DoAllocate;
    using base_type::DoFree;
    using base_type::GetAllocatorRef;
    using base_type::GetCapacityPtrRef;
    using base_type::mBegin;
    using base_type::mCapacityAllocator;
    using base_type::mEnd;

public:
    fixed_vector();
    fixed_vector(const allocator_type& allocator);
    fixed_vector(const this_type& rhs);

    ~fixed_vector();

    virtual reference       operator[](size_type pos);
    virtual const_reference operator[](size_type pos) const;

    virtual void            push_back(const value_type& value);
};


/* -- fixed_vector -- */
template <typename T, size_t N, typename FixedAllocator>
fixed_vector<T, N, FixedAllocator>::fixed_vector()
    : base_type()
{
    this->reserve(N);
}

template <typename T, size_t N, typename FixedAllocator>
fixed_vector<T, N, FixedAllocator>::fixed_vector(const allocator_type& allocator)
    : base_type(N, allocator)
{
    // empty
}

template <typename T, size_t N, typename FixedAllocator>
fixed_vector<T, N, FixedAllocator>::fixed_vector(const this_type& rhs)
    : base_type(rhs.size(), rhs.GetAllocatorRef())
{
    // empty
}

template <typename T, size_t N, typename FixedAllocator>
fixed_vector<T, N, FixedAllocator>::~fixed_vector()
{
    // empty
}

template <typename T, size_t N, typename FixedAllocator>
typename fixed_vector<T, N, FixedAllocator>::reference
fixed_vector<T, N, FixedAllocator>::operator[](size_type pos)
{
    if (pos >= this->capacity())
        throw std::out_of_range("vector::operator[] -- out of range");

    return *(mBegin + pos);
}

template <typename T, size_t N, typename FixedAllocator>
typename fixed_vector<T, N, FixedAllocator>::const_reference
fixed_vector<T, N, FixedAllocator>::operator[](size_type pos) const
{
    if (pos >= this->capacity())
        throw std::out_of_range("vector::operator[] -- out of range");

    return *(mBegin + pos);
}

template <typename T, size_t N, typename FixedAllocator>
void fixed_vector<T, N, FixedAllocator>::push_back(const value_type& value)
{
    if (mEnd >= GetCapacityPtrRef())
        throw std::out_of_range("vector::push_back -- no empty!");

    *(mEnd) = value;
    (mEnd)++;
}
/* -- fixed_vector -- */

} /* namespace mnstl */