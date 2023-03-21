#ifndef __COUNT_H__
#define __COUNT_H__

#include <vector>

using namespace std;

/*
[1,3,0,0,2,0,0,4]
1 -> 1 = 1
2 -> 3 = 2+1
3 -> 6 = 3+2+1
[0,0,0,2,0,0]
*/
long long zeroFilledSubarray(vector<int> &nums)
{
    int64_t res = 0;
    int cur = 1;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] != 0)
            cur = 1;
        else
        {
            res += cur;
            ++cur;
        }
    }
    return res;
}

#endif