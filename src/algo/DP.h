#ifndef __DP_H__
#define __DP_H__

#include <vector>
#include <algorithm>

#include <math.h>

using namespace std;

/*
https://leetcode.com/problems/jump-game-ii/
*/
int32_t jump(vector<int32_t> &nums)
{
    
}

/*
https://leetcode.com/problems/minimum-path-sum/
*/
int32_t minPathSum(vector<vector<int32_t>> &grid)
{
    int32_t m = grid.size(), n = grid[0].size();
    for (int32_t i = 1; i < n; i++)
        grid[0][i] += grid[0][i - 1];

    for (int32_t i = 1; i < m; i++)
    {
        grid[i][0] += grid[i - 1][0];
        for (int32_t j = 1; j < n; j++)
        {
            grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
        }
    }
    return grid[m - 1][n - 1];
}

/*
https://leetcode.com/problems/minimum-cost-for-tickets/description/
*/
int32_t mincostTickets(vector<int32_t>& days, vector<int32_t>& costs) {
    int32_t dp[3];
    int32_t n = days.size();
    for (int32_t i = 0; i < n; ++i)
    {
        
    }
    return 0;
}

/*
https://leetcode.com/problems/minimum-cost-to-split-an-array/description/

[1,2,1,2,1]

dp[0] <=  {[1]}
dp[1] <=  {[1][2],                [1,2]}              
dp[2] <=  {[1][2][1], [1][2,1]}, {[1,2][1], [1,2,1]}

* if cost([1][2]) < cost([1,2]), then cost([1][2][1]) < cost([1,2][1])
* but cost([1][2,1]) < cost([1,2,1]) do not sure
* 

*/
int32_t minCost(vector<int32_t>& nums, int32_t k) {
    int32_t dp[1001]{0};
    int32_t n = nums.size();

    vector<vector<int32_t>> trim_table(n, vector<int32_t>(n, 0));
    vector<int32_t> cnt(n, 0);
    for (int32_t i = 0; i < n; ++i)
    {
        int32_t len = 0;
        for (int32_t j = i; j < n; ++j)
        {
            len += cnt[nums[j]] == 1 ? 2 : cnt[nums[j]] > 1 ? 1 : 0;
            ++cnt[nums[j]];
            trim_table[i][j] = len;
        }
        fill(cnt.begin(), cnt.end(), 0);
    }

    for (int32_t i = 0; i < n; ++i)
    {
        dp[i] = trim_table[0][i] + k;
        for (int32_t j = 0; j < i; ++j)
        {
            dp[i] = min(dp[i], dp[j] + trim_table[j+1][i] + k);
        }
    }
    return dp[n-1];
}

#endif