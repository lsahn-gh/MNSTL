#pragma once

#if !defined(USE_MNSTL_ITERATOR_IMPL)

# include <iterator>
# define mnstl_reverse_iterator std::reverse_iterator

#else /* USE_MNSTL_ITERATOR_IMPL */

# define mnstl_reverse_iterator mnstl::reverse_iterator

namespace mnstl
{

template <typename Iterator>
class reverse_iterator
{
public:
    typedef Iterator        iterator_type;

protected:
    Iterator mIterator;

public:
    reverse_iterator()
        : mIterator() { }

    reverse_iterator(iterator_type i)
        : mIterator(i) { }

    reverse_iterator(const reverse_iterator& ri)
        : mIterator(ri.mIterator) { }

    iterator_type base() const
        { return mIterator; }
};

} /* namespace mnstl */

#endif /* USE_MNSTL_ITERATOR_IMPL */