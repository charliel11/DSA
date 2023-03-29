#ifndef __COUNT_H__
#define __COUNT_H__

#include <vector>

/*
count subarray

[0,0,0,2,0,0]
1 -> 1 = 1
2 -> 3 = 2+1
3 -> 6 = 3+2+1
*/
int64_t zeroFilledSubarray(std::vector<int32_t> &nums)
{
    int64_t res = 0;
    int32_t cur = 1;
    for (uint64_t i = 0; i < nums.size(); ++i)
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