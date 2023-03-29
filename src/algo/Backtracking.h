
#ifndef __BACKTRACKING_H__
#define __BACKTRACKING_H__

#include <vector>
#include <queue>

#include "UnionFind.h"

using namespace std;


/* 47. Permutations II
https://leetcode.com/problems/permutations-ii/description/
*/

bool _IsB4Duplicated(int st, int end, vector<int> &nums)
{
    for (int k = st; k < end; k++)
    {
        if (nums[k] == nums[end])
        {
            return true;
        }
    }

    return false;
}
void _PermuteUniqueHelper(vector<vector<int>> &ans, vector<int> &candidates, const int &i)
{
    if (i == candidates.size())
    {
        ans.push_back(candidates);

        return;
    }

    for (int j = i; j < candidates.size(); ++j)
    {
        if ((j == i || candidates[i] != candidates[j]) && !_IsB4Duplicated(i, j, candidates))
        {
            swap(candidates[i], candidates[j]);
            _PermuteUniqueHelper(ans, candidates, i + 1);
            swap(candidates[i], candidates[j]);
        }
    }
}
vector<vector<int>> PermuteUnique(vector<int> &nums)
{
    vector<vector<int>> out;
    vector<int> subOut;
    // sort(nums.begin(), nums.end());
    _PermuteUniqueHelper(out, nums, 0);

    return out;
}

#endif