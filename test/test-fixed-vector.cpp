#include "test.h"
#include <mnstl/fixed-vector.h>

using namespace std;
using namespace mnstl;

int main()
{
    FixedVector<int, 5> scores;

    assert(scores.GetSize() == 0);
    assert(scores.GetCapacity() == 5);

    scores.Add(100);
    scores.Add(93);
    scores.Add(99);
    scores.Add(55);
    scores.Add(33);

    assert(scores.Add(23) == false);
    assert(scores.GetSize() == 5);

    scores.Clear();

    assert(scores.GetSize() == 0);
    assert(scores.GetCapacity() == 5);

    scores[0] = 99;
    scores[1] = 88;

    assert(scores[0] == 99);
    assert(scores[1] == 88);

    return 0;
}