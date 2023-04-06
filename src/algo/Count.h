#pragma once

#include <string>
#include <vector>

using namespace std;

/*
count subarray

[0,0,0,2,0,0]
1 -> 1 = 1
2 -> 3 = 2+1
3 -> 6 = 3+2+1
*/
int64_t zeroFilledSubarray(vector<int32_t> &nums) {
    int64_t res = 0;
    int32_t cur = 1;
    for (uint64_t i = 0; i < nums.size(); ++i) {
        if (nums[i] != 0)
            cur = 1;
        else {
            res += cur;
            ++cur;
        }
    }
    return res;
}

/*
https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/

*/
int32_t findTheLongestBalancedSubstring(string s) {
    uint64_t res = 0;
    char check = '0';
    size_t prev_idx = 0, zero_cnt = 0;
    size_t i = 0;
    for (; i < s.size(); ++i) {
        if (s[i] == check) {
            if (check == '0')
                res = max(res, 2 * min(zero_cnt, (i - prev_idx)));
            else if (check == '1')
                zero_cnt = i - prev_idx;
            prev_idx = i;
            check = check == '0' ? '1' : '0';
        }
    }
    if (check == '0')
        res = max(res, 2 * min(zero_cnt, (i - prev_idx)));

    return res;
}