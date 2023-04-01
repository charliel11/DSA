#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

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
    return left;
};

#endif