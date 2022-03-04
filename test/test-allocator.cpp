#include "test.h"
#include <mnstl/allocator.h>

using namespace std;
using namespace mnstl;

int main()
{
    {
        const size_t N_ITEMS = 10;

        malloc_allocator<int> alloc;

        int *arr = alloc.allocate(N_ITEMS);

        for (int i = 0; i < N_ITEMS; i++)
        {
            arr[i] = i;
        }

        alloc.deallocate(arr, N_ITEMS);
    }

    return 0;
}