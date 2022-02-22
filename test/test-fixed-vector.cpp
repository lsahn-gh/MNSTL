#include "test.h"
#include <mnstl/fixed-vector.h>

using namespace std;
using namespace mnstl;

int main()
{
    FixedVector<int, 10> scores;

    assert(scores.GetSize() == 0);
    assert(scores.GetCapacity() == 10);

    scores.Add(100);
    scores.Add(93);
    scores.Add(99);

    assert(scores.GetSize() == 3);

    scores.Clear();

    assert(scores.GetSize() == 0);
    assert(scores.GetCapacity() == 10);

    scores[0] = 99;
    scores[1] = 88;

    assert(scores[0] == 99);
    assert(scores[1] == 88);

    return 0;
}