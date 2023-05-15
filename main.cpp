#include <Node.h>
#include <UnionFind.h>
#include <Utility.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <numeric>
#include <parse.h>
#include <queue>
#include <stdint.h>
#ifdef _MSVC
#include <vcruntime.h>
#endif

#define TARGET countGoodStrings

/*
https://leetcode.com/problems/count-ways-to-build-good-strings/
TODO:
*/
int countGoodStrings(int low, int high, int zero, int one) {
    int m = 1e9 + 7;
    int res = 0;
    return res;
}

/*
https://leetcode.com/problems/uncrossed-lines/
*/
int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();

    vector<vector<int>> dp(n1, vector<int>(n2, -1));
    auto dfs = [&](const auto &dfs, int i1, int i2) {
        if (i1 == n1 || i2 == n2)
            return 0;

        if (dp[i1][i2] != -1)
            return dp[i1][i2];

        int res = 0;
        if (nums1[i1] == nums2[i2])
            res = std::max(res, 1 + dfs(dfs, i1 + 1, i2 + 1));
        else
            res = std::max(dfs(dfs, i1 + 1, i2), dfs(dfs, i1, i2 + 1));

        return dp[i1][i2] = res;
    };

    return dfs(dfs, 0, 0);
}

/*
https://leetcode.com/problems/spiral-matrix/description/
*/
vector<int> spiralOrder(vector<vector<int>> &matrix) {
    vector<vector<int>> m{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int mi = 0;
    int nr = matrix.size(), nc = matrix[0].size();
    int r_begin = 0, r_end = nr - 1, c_begin = 0, c_end = nc - 1;
    int *end[4][2];
    end[0][0] = &r_begin, end[0][1] = &c_end;
    end[1][0] = &r_end, end[1][1] = &c_end;
    end[2][0] = &r_end, end[2][1] = &c_begin;
    end[3][0] = &r_begin, end[3][1] = &c_begin;

    vector<int> res;
    res.reserve(nr * nc);
    int r = 0, c = 0;
    for (int i = 0; i < nr * nc; ++i) {
        res.push_back(matrix[r][c]);
        if (r == *end[mi][0] && c == *end[mi][1]) {
            switch (mi) {
            case 0:
                ++r_begin;
                break;
            case 1:
                --c_end;
                break;
            case 2:
                --r_end;
                break;
            case 3:
                ++c_begin;
                break;
            }
            mi = (mi + 1) % 4;
        }
        r += m[mi][0];
        c += m[mi][1];
    }
    return res;
}
/*
https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/editorial/

LIS -> patient sort + binary search

*/
vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
    vector<int> stack;
    int n = obstacles.size();
    stack.reserve(n);
    vector<int> res(n);

    for (int i = 0; i < n; ++i) {
        int idx = upper_bound(stack.begin(), stack.end(), obstacles[i]) - stack.begin();
        if (idx == stack.size())
            stack.push_back(obstacles[i]);
        else
            stack[idx] = obstacles[i];
        res[i] = idx + 1;
    }
    return res;
}

/*
{3,3,6,8}

{3}

{3,3}

{3,6}
{3,3,6}

{3,8}
{3,3,8}
{3,6,8}
{3,3,6,8}


1 => 1
2 => 2**(2 - 2) = 1
3 => 2**(3 - 2) = 2
4 => 2**(4 - 2) = 4
5 => 2**(5 - 2) = 8

1 => 1, 2 => 2, 3 => 4, 4 => 8, 5 => 16
*/
int numSubseq(vector<int> &nums, int target) {
    int a = 0x0040;
    int m = 1e9 + 7;
    size_t n = nums.size();
    vector<int> pow_table(n, 1);
    for (int i = 1; i < n; ++i) {
        pow_table[i] = (pow_table[i - 1] * 2) % m;
    }
    sort(begin(nums), end(nums));

    int64_t res = 0;
    int l = 0, r = n - 1;
    while (l <= r) {
        if (nums[l] + nums[r] <= target) {
            res = (res + pow_table[r - l]) % m;
            ++l;
        } else {
            --r;
        }
    }

    return res;
}

/*
https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/

union_find variant
*/
vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList,
                                       vector<vector<int>> &queries) {
    UnionFind uf(n);
    sort(edgeList.begin(), edgeList.end(),
         [](vector<int> &a, vector<int> &b) { return a[2] < b[2]; });
    size_t qn = queries.size();
    size_t en = edgeList.size();
    vector<int32_t> idx(qn);
    std::iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(),
         [&queries](int a, int b) { return queries[a][2] < queries[b][2]; });
    vector<bool> res(qn);

    int32_t j = 0;
    for (auto i : idx) {
        int32_t limit = queries[i][2];
        for (; j < en && edgeList[j][2] < limit; ++j) {
            int32_t r1 = uf.find_root(edgeList[j][0]);
            int32_t r2 = uf.find_root(edgeList[j][1]);
            if (r1 != r2) {
                int32_t tmp = std::min(r1, r2);
                r2 = std::max(r1, r2);
                r1 = tmp;
                uf.insert(r2, r1);
            }
        }
        int32_t r1 = uf.find_root(queries[i][0]);
        int32_t r2 = uf.find_root(queries[i][1]);
        res[i] = r1 == r2;
    }
    return res;
}

/*
https://leetcode.com/problems/similar-string-groups/

1. similar(X,Y) => edges => groups => union find

*/
int32_t numSimilarGroups(vector<string> &strs) {
    int16_t n = strs.size();
    int16_t sn = strs[0].size();
    vector<vector<int16_t>> edges;
    for (int16_t i = 0; i < n; ++i) {
        for (int16_t j = i + 1; j < n; ++j) {
            int16_t cnt = 0;
            for (int16_t k = 0; k < sn && cnt < 3; ++k) {
                if (strs[i][k] != strs[j][k])
                    ++cnt;
            }
            if (cnt == 2 || cnt == 0)
                edges.push_back({i, j});
        }
    }
    UnionFind uf(n);
    int32_t n_connected_component = n;
    for (auto &e : edges) {
        int32_t r1 = uf.find_root(e[0]);
        int32_t r2 = uf.find_root(e[1]);
        if (r1 != r2) {
            int32_t tmp = std::min(r1, r2);
            r2 = std::max(r1, r2);
            r1 = tmp;
            uf.insert(r2, r1);
            --n_connected_component;
        }
    }
    return n_connected_component;
}

/*
https://leetcode.com/problems/profitable-schemes/

*/
int32_t profitableSchemes(int32_t n, int32_t minProfit, vector<int32_t> &group,
                          vector<int32_t> &profit) {

    int32_t pn = profit.size();
    int32_t res = 0;

    auto dfs = [&](const auto &dfs, int32_t idx, int32_t cur_profit, int32_t cur_n) {
        if (cur_n < 0)
            return;
        if (idx == pn) {
            if (cur_profit >= minProfit)
                ++res;
            return;
        }
        dfs(dfs, idx + 1, cur_profit + profit[idx], cur_n - group[idx]);
        dfs(dfs, idx + 1, cur_profit, cur_n);
        return;
    };

    dfs(dfs, 0, 0, n);
    return res;
}

/*
https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

f(0,n)
* a[0] == a[n] => f(1,n-1),
* a[0] != a[n] => (f(0,n-1)+1, f(1,n)+1)

*/
int32_t minInsertions(string s) {

    int32_t n = s.size();
    int32_t dp[n][n];
    memset(dp, 0xff, sizeof(dp));

    auto dfs = [&](const auto &dfs, int32_t l, int32_t r) {
        if (l >= r) {
            return 0;
        }
        if (dp[l][r] != -1)
            return dp[l][r];

        int32_t res = INT32_MAX;
        if (s[l] == s[r])
            res = std::min(res, dfs(dfs, l + 1, r - 1));
        else {
            res = std::min(res, dfs(dfs, l + 1, r) + 1);
            res = std::min(res, dfs(dfs, l, r - 1) + 1);
        }
        return dp[l][r] = res;
    };
    return dfs(dfs, 0, n - 1);
}
/*
https://leetcode.com/problems/maximum-width-of-binary-tree/

1
2 3
4567

*/
int32_t widthOfBinaryTree(TreeNode *root) {
    int32_t res = 0;
    deque<pair<TreeNode *, uint32_t>> q;
    q.push_back({root, 1});
    while (!q.empty()) {
        int32_t level = q.size();
        int32_t width = q.back().second - q.front().second + 1;
        res = max(res, width);
        while (level--) {
            auto cur = q.front();
            q.pop_front();
            if (cur.first->left != nullptr)
                q.push_back({cur.first->left, cur.second * 2});
            if (cur.first->right != nullptr)
                q.push_back({cur.first->right, cur.second * 2 + 1});
        }
    }
    return res;
}

/*
https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
*/
int32_t longestZigZag(TreeNode *root) {
    int32_t res = 0;

    auto dfs = [&](const auto &dfs, TreeNode *node) -> pair<int32_t, int32_t> {
        if (node == nullptr)
            return {-1, -1};

        int l = 1 + dfs(dfs, node->left).second;
        int r = 1 + dfs(dfs, node->right).first;
        res = std::max(res, std::max(l, r));

        return {l, r};
    };
    dfs(dfs, root);
    return res;
}

/*
https://leetcode.com/problems/longest-palindromic-subsequence/

TODO:

b,b,b,a,b
1,1,1,1,1

bbbab

f(i,j) = max(f(i+1,j-1)+(a[i]==a[j]),f(i+1,j), f(i,j-1))
f(1,1) => f(2,1), f(1,0);
*/
// int32_t longestPalindromeSubseq(string s) {
//     size_t n = s.size();
//     int32_t dp[1001][1001];

//     for ()

//         return dp[0][0];
// }

/*
https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/
*/
// int32_t minimumVisitedCells(vector<vector<int32_t>> &grid) {}

/*
https://leetcode.com/problems/validate-stack-sequences/description/

TODO:
*/
bool validateStackSequences(vector<int32_t> &pushed, vector<int32_t> &popped) {
    deque<int32_t> st;

    size_t i = 0;
    for (auto &val : pushed) {
        st.emplace_back(val);

        while (!st.empty() && st.back() == popped[i]) {
            st.pop_back();
            ++i;
        }
    }
    return st.empty();
}

/*
https://leetcode.com/problems/minimum-reverse-operations/

TODO:
*/
vector<int32_t> minReverseOperations(int32_t n, int32_t p, vector<int32_t> &banned, int32_t k) {
    vector<int32_t> res{0};
    return res;
}

/*------------------------------------------------------*/

#define str(x) #x
#define NAME(x) str(x)
#define F(tup) TARGET(tup);

static const string DIR{PROJECTDIR};

template <typename TupleT, std::size_t... Is> auto call(TupleT tup, std::index_sequence<Is...>) {
    return F(std::get<Is>(tup)...);
}

int main() {
    string target_fun = NAME(TARGET);
    string data_text = readtxt(DIR + '/' + target_fun);
    using p = decltype(arguments(TARGET));
    auto cases = parse<p>(data_text);
    size_t n = cases.size();
    FOR(n) {
        cout << "---Case #" << i << ": ---" << endl;
        auto c = cases[i];
        constexpr size_t tup_len = tuple_size_v<p> - 1;
        auto res = call(c, std::make_index_sequence<tup_len>{});
        print("Your Result: ", res);
        print("Answer: ", get<tup_len>(c));
    };
    return 0;
}