#pragma once

#include <memory>

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

    void* allocate(std::size_t n)
        { malloc(sizeof(T) * n); }

    void deallocate(T* p, std::size_t n)
        { if (p) free(p); }

private:
    malloc_allocator(const malloc_allocator& allocator) = delete;
    ~malloc_allocator() = delete;
};

MNSTL_NAMESPACE_END