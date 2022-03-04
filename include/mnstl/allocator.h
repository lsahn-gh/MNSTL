#pragma once

#include <memory>
#include <cstdlib>

#define TRY_INCLUDING_INTERNAL_H
#include "internal.h"
#undef TRY_INCLUDING_INTERNAL_H

MNSTL_NAMESPACE_BEGIN

// malloc/free wrapping allocator class for 'Allocator' of Containers.
template <typename T>
class malloc_allocator
{
public:
    malloc_allocator() = default;
    ~malloc_allocator() = default;

    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(malloc(sizeof(T) * n));
    }

    void deallocate(T* p, std::size_t n)
    {
        if (p != nullptr)
            free(reinterpret_cast<void*>(p));
    }

private:
    malloc_allocator(const malloc_allocator& allocator) = delete;
};

MNSTL_NAMESPACE_END