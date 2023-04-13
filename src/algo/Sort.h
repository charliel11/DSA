#pragma once

#include <algorithm>
#include <vector>

using namespace std;

/*
https://leetcode.com/problems/sort-an-array/description/
*/
inline void quicksort(vector<int32_t> &nums, int32_t left, int32_t right) {
    if (left >= right)
        return;

    int32_t mid = left + (right - left) / 2;
    int32_t pivot = nums[mid];
    int32_t l = left - 1, r = right + 1;
    while (l < r) {
        while (l < r && nums[--r] > pivot)
            ;
        while (l < r && nums[++l] < pivot)
            ;
        std::swap(nums[l], nums[r]);
    }
    quicksort(nums, left, l);
    quicksort(nums, l + 1, right);
}
inline vector<int32_t> sortArray(vector<int32_t> &nums) {
    quicksort(nums, 0, nums.size() - 1);
    return nums;
}