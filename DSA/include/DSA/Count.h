#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
count subarray

[0,0,0,2,0,0]
1 -> 1 = 1
2 -> 3 = 2+1
3 -> 6 = 3+2+1
*/
inline int64_t zeroFilledSubarray(vector<int32_t> &nums) {
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
inline int32_t findTheLongestBalancedSubstring(string s) {
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

/*
https://leetcode.com/problems/sum-of-distances/

[a1, a2, a3, a4] =>
[(a4-a1)+(a3-a1)+(a2-a1), (a4-a2)+(a3-a2)+(a2-a1), (a4-a3)+(a3-a2)+(a3-a1), (a4-a3)+(a4-a2)+(a4-a1)]

[(a4+a3+a2)-3*a1, (a2 - a1) + (a4+a3 -2*a2), (a4)+2*a3-a3-(a2+a1), ()+3*a4-(a3+a2+a1)]

RECAP: deduction

*/
inline vector<int64_t> distance(vector<int32_t> &nums) {
    int32_t n = nums.size();
    unordered_map<int32_t, vector<int32_t>> hash;

    vector<int64_t> res(n);
    for (int32_t i = 0; i < n; ++i) {
        if (hash.count(nums[i])) {
            for (auto idx : hash[nums[i]]) {
                res[idx] += i - idx;
                res[i] += i - idx;
            }
        }
        hash[nums[i]].push_back(i);
    }
    return res;
}

/*
https://leetcode.com/problems/prime-in-diagonal/

RECAP: Prime

*/
inline int32_t diagonalPrime(vector<vector<int32_t>> &nums) {
    int32_t row = nums.size();
    int32_t col = nums[0].size();

    auto isPrime = [](int32_t n) -> bool {
        // Corner cases
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;

        // This is checked so that we can skip
        // middle five numbers in below loop
        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (int i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;

        return true;
    };

    int32_t diag_l = 0, diag_r = col - 1;
    int32_t res = 0;
    for (int32_t r = 0; r < row && diag_l < col && diag_r >= 0; ++diag_l, --diag_r, ++r) {
        if (isPrime(nums[r][diag_l]))
            res = max(res, nums[r][diag_l]);
        if (isPrime(nums[r][diag_r]))
            res = max(res, nums[r][diag_r]);
    }
    return res;
}