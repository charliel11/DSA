#ifndef __DP_H__
#define __DP_H__

#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

/*
https://leetcode.com/problems/minimum-cost-for-tickets/description/
*/
// int32_t mincostTickets(vector<int32_t>& days, vector<int32_t>& costs) {
//     int32_t dp[3];
//     int32_t n = days.size();
//     for (int32_t i = 0; i < n; ++i)
//     {
        
//     }
//     return 0;
// }

/*
https://leetcode.com/problems/minimum-cost-to-split-an-array/description/

[1,2,1,2,1]

{[1]} -> root
{[1][2],                [1,2]}              
{[1][2][1], [1][2,1]}, {[1,2][1], [1,2,1]}

if cost([1][2]) < cost([1,2]), then cost([1][2][1]) < cost([1,2][1])
but cost([1][2,1]) < cost([1,2,1]) do not sure

*/
int32_t minCost(vector<int32_t>& nums, int32_t k) {
    int32_t dp[1001]{INT32_MAX};
    int32_t n = nums.size();

    vector<vector<int32_t>> trim_table(n, vector<int32_t>(n, 0));
    vector<int32_t> cnt(n, 0);
    for (int32_t i = 0; i < n; ++i)
    {
        int32_t len = 0;
        for (int32_t j = i; j < n; ++j)
        {
            len += cnt[nums[j]] == 1 ? 2 : cnt[nums[j]] == 2 ? 1 : 0;
            ++cnt[nums[j]];
            trim_table[i][j] = len;
        }
        fill(cnt.begin(), cnt.end(), 0);
    }

    for (int32_t i = 0; i < n; ++i)
    {
        for (int32_t j = 0; j < i; ++j)
        {
            dp[i] = min(dp[i], dp[j] + trim_table[j][i] + k);
        }
    }
    return dp[n-1];
}

#endif