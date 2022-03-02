#include "test.h"
#include <mnstl/vector.h>

int main()
{
    // Initialize
    {
        using namespace mnstl;

        vector<int> vec1;
        assert(vec1.capacity() == 0);

        vector<int> vec2(5);
        assert(vec2.capacity() == 8);

        vector<float> vec3(25);
        assert(vec3.capacity() == 25);

        vector<float> vec4 = vec3;
        assert(vec4.capacity() == 25);
    }

    // overflow through 'push_back'
    {
        using namespace mnstl;

        const size_t MAX_ITEMS = 20;

        vector<int> vec1(10);
        assert(vec1.size() == 0);
        assert(vec1.capacity() == 10);

        for (size_t n = 0; n < MAX_ITEMS; n++)
        {
            vec1.push_back(n);
        }
        assert(vec1.size() == MAX_ITEMS);
        assert(vec1.capacity() == 20);

        vec1.push_back(MAX_ITEMS);
        assert(vec1.size() == MAX_ITEMS + 1);
        assert(vec1.capacity() == 40);
    }

    return 0;
}