#ifndef __SORT_H__
#define __SORT_H__

#include <vector>

using namespace std;

/*
https://leetcode.com/problems/sort-an-array/description/
*/
vector<int32_t> sortArray(vector<int32_t> &nums)
{
    quicksort(nums, 0, nums.size() - 1);
    return nums;
}
void quicksort(vector<int32_t> &nums, int32_t left, int32_t right)
{
    if (left >= right)
        return;

    int32_t mid = left + (right - left) / 2;
    int32_t pivot = nums[mid];
    int32_t l = left - 1, r = right + 1;
    while (l < r)
    {
        while (l < r && nums[--r] > pivot)
            ;
        while (l < r && nums[++l] < pivot)
            ;
        swap(nums[l], nums[r]);
    }
    quicksort(nums, left, l);
    quicksort(nums, l + 1, right);
}

#endif