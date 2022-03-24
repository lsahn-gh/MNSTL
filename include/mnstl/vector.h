#pragma once

#include <cassert>
#include <iostream>
#include <algorithm>

#include "iterator.h"
#include "memory.h"

namespace mnstl
{

template <typename T, typename Allocator>
class VectorBase
{
public:
    typedef Allocator               allocator_type;
    typedef std::size_t             size_type;
    typedef std::ptrdiff_t          difference_type;

protected:
    T*                              mBegin;
    T*                              mEnd;
    std::pair<T*, allocator_type>   mCapacityAllocator;

    T* & GetCapacityPtrRef()
        { return mCapacityAllocator.first; }

    allocator_type& GetAllocatorRef()
        { return mCapacityAllocator.second; }

    const allocator_type& GetAllocatorRef() const
        { return mCapacityAllocator.second; }

public:
    VectorBase();
    VectorBase(const allocator_type& allocator);
    VectorBase(size_type n, const allocator_type& allocator);

    ~VectorBase();

    allocator_type&         get_allocator();
    const allocator_type&   get_allocator() const;

protected:
    T*      DoAllocate(size_type n);
    void    DoFree(T* p, size_type n);
};


template <typename T, typename Allocator = std::allocator<T> >
class vector : public VectorBase<T, Allocator>
{
    typedef VectorBase<T, Allocator>                base_type;
    typedef vector<T, Allocator>                    this_type;

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

    using base_type::mBegin;
    using base_type::mEnd;
    using base_type::mCapacityAllocator;
    using base_type::GetCapacityPtrRef;
    using base_type::GetAllocatorRef;
    using base_type::DoAllocate;
    using base_type::DoFree;

public:
    enum { MIN_CAPACITY = 8 };

    vector();
    vector(const allocator_type& allocator);
    vector(size_type n, const allocator_type& allocator);
    vector(const this_type& rhs);

    ~vector();

    reference       at(size_type pos);
    const_reference at(size_type pos) const;

    virtual reference       operator[](size_type pos);
    virtual const_reference operator[](size_type pos) const;

    reference       front();
    const_reference front() const;

    reference       back();
    const_reference back() const;

    pointer         data();
    const_pointer   data() const;

    virtual void            push_back(const value_type& value);

    iterator                begin();
    const_iterator          begin() const;
    iterator                end();
    const_iterator          end() const;

    reverse_iterator        rbegin();
    const_reverse_iterator  rbegin() const;
    reverse_iterator        rend();
    const_reverse_iterator  rend() const;

    bool        empty() const;
    size_type   capacity() const;
    size_type   size() const;

    void        clear();
    void        resize(const size_type n);
    void        resize(const size_type n, const value_type& value);
    void        reserve(const size_type n);
};


/* -- VectorBase -- */
template <typename T, typename Allocator>
VectorBase<T, Allocator>::VectorBase()
    : mBegin(nullptr)
    , mEnd(nullptr)
    /* , mCapacityAllocator(nullptr, allocator_type()) -> TODO */
{
    // empty
}

template <typename T, typename Allocator>
VectorBase<T, Allocator>::VectorBase(const allocator_type& allocator)
    : mBegin(nullptr)
    , mEnd(nullptr)
    , mCapacityAllocator(nullptr, allocator)
{
    // empty
}

template <typename T, typename Allocator>
VectorBase<T, Allocator>::VectorBase(size_type n, const allocator_type& allocator)
    : mCapacityAllocator(nullptr, allocator)
{
    mBegin = DoAllocate(n);
    mEnd = mBegin;
    GetCapacityPtrRef() = mBegin + n;
}

template <typename T, typename Allocator>
VectorBase<T, Allocator>::~VectorBase()
{
    if (mBegin != nullptr)
    {
        DoFree(mBegin, static_cast<size_type>(GetCapacityPtrRef() - mBegin));
    }

    mBegin = nullptr;
    mEnd = nullptr;
    GetCapacityPtrRef() = nullptr;
}

template <typename T, typename Allocator>
typename VectorBase<T, Allocator>::allocator_type&
VectorBase<T, Allocator>::get_allocator()
{
    return GetAllocatorRef();
}

template <typename T, typename Allocator>
const typename VectorBase<T, Allocator>::allocator_type&
VectorBase<T, Allocator>::get_allocator() const
{
    return GetAllocatorRef();
}

template <typename T, typename Allocator>
T* VectorBase<T, Allocator>::DoAllocate(size_type n)
{
    auto alloc = GetAllocatorRef();

    return alloc.allocate(n);
}

template <typename T, typename Allocator>
void VectorBase<T, Allocator>::DoFree(T* p, size_type n)
{
    auto alloc = GetAllocatorRef();

    alloc.deallocate(p, n);
}


/* -- vector -- */
template <typename T, typename Allocator>
vector<T, Allocator>::vector()
    : base_type()
{
    // empty
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const allocator_type& allocator)
    : base_type(allocator)
{
    // empty
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n, const allocator_type& allocator)
    : base_type(n, allocator)
{
    // empty
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const this_type& rhs)
    : base_type(rhs.size(), rhs.GetAllocatorRef())
{
    mEnd = std::copy(rhs.mBegin, rhs.mEnd, mBegin);
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    // empty
}

/* -- element access -- */
template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::at(size_type pos)
{
    if (pos >= size())
        throw std::out_of_range("vector::at() -- out of range");

    return *(mBegin + pos);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at(size_type pos) const
{
    if (pos >= size())
        throw std::out_of_range("vector::at() -- out of range");

    return *(mBegin + pos);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::operator[](size_type pos)
{
    return *(mBegin + pos);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::operator[](size_type pos) const
{
    return *(mBegin + pos);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::front()
{
    return *(mBegin);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::front() const
{
    return *(mBegin);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::back()
{
    return *(mEnd - 1);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::back() const
{
    return *(mEnd - 1);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::pointer
vector<T, Allocator>::data()
{
    return mBegin;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_pointer
vector<T, Allocator>::data() const
{
    return mBegin;
}
/* -- element access -- */

// TODO must be called under lock!
template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(const value_type& value)
{
    if (mEnd >= GetCapacityPtrRef())
    {
        const size_type NEW_CAPACITY = (capacity() * 2);
        T* newBegin = DoAllocate(NEW_CAPACITY);
        T* newEnd = std::copy(mBegin, mEnd, newBegin);

        DoFree(mBegin, capacity());

        // NOT SAFE for multi-threaded program!

        mBegin = newBegin;
        mEnd = newEnd;
        GetCapacityPtrRef() = (mBegin + NEW_CAPACITY);
    }

    *(mEnd) = value;
    (mEnd)++;
}

/* -- iterators -- */
template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::begin()
{
    return mBegin;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::begin() const
{
    return mBegin;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::end()
{
    return mEnd;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator
vector<T, Allocator>::end() const
{
    return mEnd;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rbegin()
{
    return reverse_iterator(mEnd);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rbegin() const
{
    return const_reverse_iterator(mEnd);
}
template <typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator
vector<T, Allocator>::rend()
{
    return reverse_iterator(mBegin);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rend() const
{
    return const_reverse_iterator(mBegin);
}
/* -- iterators -- */

/* -- capacity -- */
template <typename T, typename Allocator>
bool vector<T, Allocator>::empty() const
{
    return (size() == 0);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::size() const
{
    return static_cast<size_type>(mEnd - mBegin);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(const size_type n)
{
    if (mBegin != nullptr)
    {
        DoFree(mBegin, capacity());

        mBegin = nullptr;
        mEnd = nullptr;
        GetCapacityPtrRef() = nullptr;
    }

    mBegin = DoAllocate(n);
    mEnd = mBegin;
    GetCapacityPtrRef() = mBegin + n;
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::size_type
vector<T, Allocator>::capacity() const
{
    return static_cast<size_type>(mCapacityAllocator.first - mBegin);
}
/* -- capacity -- */

/* -- modifiers -- */
template <typename T, typename Allocator>
void vector<T, Allocator>::clear()
{
    mnstl::destruct(mBegin, mEnd);
    mEnd = mBegin;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::resize(const size_type n)
{
    T *newBegin = DoAllocate(n);
    T *newEnd = std::copy(mBegin, (n >= size()) ? mEnd : (mBegin + n), newBegin);

    DoFree(mBegin, capacity());

    // NOT SAFE for multi-threaded program!

    mBegin = newBegin;
    mEnd = newEnd;
    GetCapacityPtrRef() = (mBegin + n);
}
/* -- modifiers -- */

} /* namespace mnstl */