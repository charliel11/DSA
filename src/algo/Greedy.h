#pragma once

#include <vector>
#include <algorithm>

using namespace std;

/*
https://leetcode.com/problems/reducing-dishes/

[-9, -8, -1, 0, 5]
psum = 5
p1 = 1 * 0 + 2 * 5 = 10
p2 = 2 * 0 + 3 * 5 = (1 + 1) * 0 + (1 + 2) * 5 = p1 + psum
p3 = 3 * 0 + 4 * 5 = p2 + psum
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