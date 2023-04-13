#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;

namespace bs {

/*
https://leetcode.com/problems/binary-search/
*/
inline int32_t search(vector<int32_t> &nums, int32_t target) {
    int32_t l = 0, r = nums.size() - 1;
    while (l <= r) {
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

inline int32_t firstGreatOrLeftMostEqual(vector<int32_t> &nums, int32_t target) {
    int32_t left = 0, right = nums.size() - 1;
    while (left < right) {
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
inline vector<int32_t> successfulPairs(vector<int32_t> &spells, vector<int32_t> &potions,
                                       int64_t success) {
    size_t n = spells.size();
    size_t m = potions.size();
    sort(begin(potions), end(potions));
    vector<int32_t> res(n);
    for (size_t i = 0; i < n; ++i) {
        /*
        double dd = 5433930978;
        float ff = 5433930978;
        */
        int64_t target = std::ceil(static_cast<double>(success) / spells[i]);
        if (target > 100000)
            res[i] = 0;
        else {
            int32_t idx = firstGreatOrLeftMostEqual(potions, target);
            res[i] = m - idx;
        }
    }
    return res;
}

namespace minmax {

/*
https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/

RECAP:
TODO:

* Since the value of p is less than or equal to half the length of the array, we can find the minimal difference of pairs by sorting the array and comparing adjacent elements.

* Next, we need to select p pairs from the n-1 minimal difference pairs without picking consecutive pairs.

* However, simply selecting p pairs from n-1 pairs will result in a time limit exceeded error due to the O(n!) complexity of the combination problem.

* Therefore, we need to solve the problem of picking p pairs from n-1 pairs with minimal difference, which can be approached like the Knapsack problem with a complexity of O(np).

https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/solutions/3406380/i-kotlin-recursion-dp-explained-non-binary-search-approach/?topicTags=dynamic-programming

[1,1,2,3,7,10]
[0,1,1,4,3]
f(i,p) = min(max(nums[i],f(i+2,p-1)), f(i+1,p))

* But this problem n*p > 10^9 that cause TLE again.

*/
inline int32_t minimizeMax(vector<int32_t> &nums, int32_t p) {
    if (p == 0)
        return 0;
    size_t n = nums.size();
    sort(begin(nums), end(nums));
    for (size_t i = 1; i < n; ++i) {
        nums[i - 1] = nums[i] - nums[i - 1];
    }

    vector<vector<int32_t>> dp(n, vector<int32_t>(p + 1, INT32_MAX));
    dp[0][0] = 0;
    for (size_t i = 1; i < n; ++i)
        dp[i][1] = min(dp[i - 1][1], nums[i - 1]);

    for (size_t i = 2; i < n; ++i) {
        for (size_t j = 2; j <= p; ++j) {
            dp[i][j] = min(max(nums[i - 1], dp[i - 2][j - 1]), dp[i - 1][j]);
        }
    }

    return dp[n - 1][p];
}

} // namespace minmax

} // namespace bs