#pragma once

#include <vector>

using namespace std;

/*
https://leetcode.com/problems/binary-search/
*/
int32_t search(vector<int32_t> &nums, int32_t target)
{
    int32_t l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        int32_t mid = l + (r - l) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int32_t firstGreatOrLeftMostEqual(vector<int32_t> &nums, int32_t target)
{
    int32_t left = 0, right = nums.size() - 1;
    while (left < right)
    {
        int32_t mid = left + (right - left) / 2;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return nums[left] >= target ? left : left + 1;
};

/*
https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
*/
vector<int32_t> successfulPairs(vector<int32_t> &spells, vector<int32_t> &potions, int64_t success)
{
    size_t n = spells.size();
    size_t m = potions.size();
    sort(begin(potions), end(potions));
    vector<int32_t> res(n);
    for (size_t i = 0; i < n; ++i)
    {
        /*
        double dd = 5433930978;
        float ff = 5433930978;
        */
        int64_t target = std::ceil(static_cast<double>(success) / spells[i]);
        if (target > 100000)
            res[i] = 0;
        else
        {
            int32_t idx = firstGreatOrLeftMostEqual(potions, target);
            res[i] = m - idx;
        }
    }
    return res;
}