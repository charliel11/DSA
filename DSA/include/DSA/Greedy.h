#pragma once

#include <algorithm>
#include <math.h>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
https://leetcode.com/problems/reducing-dishes/

[-9, -8, -1, 0, 5]
p_sum = 5
p1 = 1 * 0 + 2 * 5 = 10
p2 = 2 * 0 + 3 * 5 = (1 + 1) * 0 + (1 + 2) * 5 = p1 + p_sum
p3 = 3 * 0 + 4 * 5 = p2 + p_sum
*/
int32_t maxSatisfaction(vector<int32_t> &satisfaction) {
    sort(begin(satisfaction), end(satisfaction));
    int32_t n = satisfaction.size();
    int32_t positive_sum = 0;
    int32_t res = 0;
    int32_t cur = 1;
    int32_t last_negative_index = -1;
    for (int32_t i = 0; i < n; ++i) {
        int32_t score = satisfaction[i];
        if (score >= 0) {
            positive_sum += score;
            res += cur * score;
            ++cur;
        } else
            ++last_negative_index;
    }

    int32_t include_negative;
    int32_t negative_sum = 0;
    while (last_negative_index >= 0) {
        include_negative = res + positive_sum + satisfaction[last_negative_index] + negative_sum;
        if (include_negative < res)
            break;
        negative_sum += satisfaction[last_negative_index];
        res = include_negative;
        --last_negative_index;
    }
    return res;
}

/*
https://leetcode.com/problems/boats-to-save-people/
*/
int32_t numRescueBoats(vector<int32_t> &people, int32_t limit) {
    sort(begin(people), end(people));
    size_t l = 0, r = people.size() - 1;
    int32_t res = 0;

    while (l < r) // size_t
    {
        ++res;
        if (people[l] + people[r] <= limit)
            ++l;
        --r;
    }
    if (r == l)
        ++res;
    return res;
}

/*
https://leetcode.com/problems/optimal-partition-of-string/description/

The use of a 32-bit variable to log which letters have been shown.
*/
int32_t partitionString(string s) {
    int32_t hash = 0;
    int32_t res = 1;
    for (char &c : s) {
        int32_t shift = c - 'a';
        if (hash & (1 << shift)) {
            hash = 0;
            ++res;
        }
        hash |= (1 << shift);
    }

    return res;
}

/*
https://leetcode.com/problems/minimize-maximum-of-array/
RECAP:
*/
int32_t minimizeArrayValue(vector<int32_t> &nums) {
    int64_t res = 0;
    int64_t prefix_sum = 0;
    size_t n = nums.size();
    for (int32_t i = 0; i < n; ++i) {
        prefix_sum += nums[i];
        res = max(res, (prefix_sum + i) / (i + 1));
    }
    return res;
}

/*
https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/

NOTE: 895. Maximum Frequency Stack
*/
vector<vector<int32_t>> findMatrix(vector<int32_t> &nums) {
    int32_t idx[201]{0};
    vector<vector<int32_t>> res{1, vector<int32_t>()};

    for (int32_t &num : nums) {
        if (res.size() - 1 < idx[num])
            res.push_back({});
        res[idx[num]].emplace_back(num);
        ++idx[num];
    }
    return res;
}

/*
https://leetcode.com/problems/mice-and-cheese/

*/
int32_t miceAndCheese(vector<int32_t> &reward1, vector<int32_t> &reward2, int32_t k) {
    size_t n = reward1.size();
    vector<int32_t> diff(n);
    for (size_t i = 0; i < n; ++i)
        diff[i] = reward2[i] - reward1[i];

    auto comp = [&](size_t i, size_t j) { return diff[i] < diff[j]; };
    priority_queue<int32_t, vector<int32_t>, decltype(comp)> pq(comp);
    int32_t i = 0;
    int32_t mouse1 = 0;
    for (; i < k; ++i) {
        mouse1 += reward1[i];
        pq.push(i);
    }
    int32_t mouse2 = 0;
    for (; i < n; ++i) {
        if (!pq.empty() && diff[i] < diff[pq.top()]) {
            int32_t t = pq.top();
            pq.pop();
            pq.push(i);
            mouse1 -= reward1[t];
            mouse1 += reward1[i];
            mouse2 += reward2[t];
        } else {
            mouse2 += reward2[i];
        }
    }

    return mouse1 + mouse2;
}