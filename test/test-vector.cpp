#include "test.h"
#include <mnstl/vector.h>

using namespace mnstl;

int main()
{
    // constructor and capacity
    {
        vector<int> vec1;
        assert(vec1.capacity() == 0);

        vector<int> vec2;
        vec2.reserve(5);
        assert(vec2.capacity() == 5);

        vector<float> vec3;
        vec3.reserve(25);
        assert(vec3.capacity() == 25);

        vector<float> vec4 = vec3;
        assert(vec4.capacity() == 0);
    }

    // size, capacity and growing feature if full
    {
        const size_t MAX_ITEMS = 20;

        vector<int> vec1;
        vec1.reserve(10);
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

    // empty, resize and reserve
    {
        vector<int> vec1;
        vec1.reserve(11);
        assert(vec1.empty() == true);
        assert(vec1.size() == 0);
        assert(vec1.capacity() == 11);

        vec1.push_back(3);
        assert(vec1.empty() == false);
        assert(vec1.size() == 1);

        vec1.resize(1);
        assert(vec1.size() == 1);
        assert(vec1.capacity() == 1);
    }

    // at, front and back
    {
        vector<int> vec1;
        vec1.reserve(20);

        for (size_t n = 0; n < 11; n++)
        {
            vec1.push_back(n);
        }
        assert(vec1.size() == 11);

        assert(vec1.front() == 0);
        assert(vec1.at(1) == 1);
        assert(vec1.at(9) == 9);
        assert(vec1.back() == 10);
    }

    // iterator
    {
        size_t n;
        vector<int> vec1;
        vec1.reserve(10);

        for (n = 0; n < vec1.capacity(); ++n)
        {
            vec1.push_back(n);
        }

        n = 0;
        for (auto iter = vec1.begin(); iter != vec1.end(); ++iter, ++n)
        {
            assert(*iter == n);
        }
    }

    return 0;
}