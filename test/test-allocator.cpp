#include "test.h"
#include <mnstl/allocator.h>

int main()
{
    {
        const size_t N_ITEMS = 10;

        mnstl::malloc_allocator<int> alloc;

        int *arr = alloc.allocate(N_ITEMS);

        for (int i = 0; i < N_ITEMS; i++)
        {
            arr[i] = i;
        }

        alloc.deallocate(arr, N_ITEMS);
    }

    return 0;
}