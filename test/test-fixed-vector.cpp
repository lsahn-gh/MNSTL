#include "test.h"
#include <mnstl/fixed-vector.h>

int main()
{
    {
        mnstl::fixed_vector<int, 5> scores;

        assert(scores.size() == 0);
        assert(scores.capacity() == 5);

        scores.push_back(100);
        scores.push_back(93);
        scores.push_back(99);
        scores.push_back(55);
        scores.push_back(33);

        assert(scores.size() == 5);

        scores.clear();

        assert(scores.size() == 0);
        assert(scores.capacity() == 5);

        scores[0] = 99;
        assert(scores[0] == 99);
        scores[1] = 88;
        assert(scores[1] == 88);
    }

    return 0;
}