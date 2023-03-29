#ifndef __DP_H__
#define __DP_H__

#include <vector>
#include <Utility.h>

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

#endif