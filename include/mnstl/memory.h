#pragma once

#include <iterator>

namespace mnstl
{

template <typename ForwardIterator>
void destruct(ForwardIterator first, ForwardIterator last)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    
    for(; first != last; ++first)
    {
        first->~value_type();
    }
}

} /* mnstl namespace */