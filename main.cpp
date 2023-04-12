#include <Utility.h>
#include <functional>
#include <parse.h>

#define TARGET minimizeMax

/*
https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/
*/
// int32_t minimumVisitedCells(vector<vector<int32_t>> &grid) {}

/*
https://leetcode.com/problems/coin-change/description/
*/
int32_t coinChange(vector<int32_t> &coins, int32_t amount) {}

/*
https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/

RECAP:

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
int32_t minimizeMax(vector<int32_t> &nums, int32_t p) {
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

/*
https://leetcode.com/problems/sum-of-distances/

[a1, a2, a3, a4] =>
[(a4-a1)+(a3-a1)+(a2-a1), (a4-a2)+(a3-a2)+(a2-a1), (a4-a3)+(a3-a2)+(a3-a1), (a4-a3)+(a4-a2)+(a4-a1)]

[(a4+a3+a2-3*a1), (a4+a3-a2-a1), (a4+a3-a2-a1), (3*a4-a3-a2-a1)]

sum => (6*a4+2*a3-2*a2-6*a1)


prefix sum => [a1, a2+a1, a3+a2+a1, a4+a3+a2+a1]

RECAP: deduction

*/
vector<int64_t> distance(vector<int32_t> &nums) {
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
*/
int32_t diagonalPrime(vector<vector<int32_t>> &nums) {
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

/*
https://leetcode.com/problems/removing-stars-from-a-string/description/
*/
string removeStars(string s) {
    string res;
    res.reserve(s.size());
    for (char &c : s) {
        if (c != '*') {
            res.push_back(c);
        } else {
            res.pop_back();
        }
    }
    return res;
}

/*
https://leetcode.com/problems/number-of-enclaves/
*/
int32_t numEnclaves(vector<vector<int32_t>> &grid) {
    size_t row = grid.size(), col = grid[0].size();

    auto dfs = [&](const auto &dfs, size_t r, size_t c, size_t &area) {
        if ((r == 0 || r == row - 1 || c == 0 || c == col - 1) && grid[r][c] == 1) {
            return false;
        }
        if (grid[r][c] == 0 || grid[r][c] == 2)
            return true;

        grid[r][c] = 2;
        ++area;
        bool r1 = dfs(dfs, r + 1, c, area);
        bool r2 = dfs(dfs, r - 1, c, area);
        bool r3 = dfs(dfs, r, c + 1, area);
        bool r4 = dfs(dfs, r, c - 1, area);

        return r1 && r2 && r3 && r4;
    };

    int32_t res = 0;
    for (size_t r = 1; r < row - 1; ++r) {
        for (size_t c = 1; c < col - 1; ++c) {
            size_t area = 0;
            if (grid[r][c] == 1 && dfs(dfs, r, c, area))
                res += area;
        }
    }
    return res;
}

/*
https://leetcode.com/problems/minimum-reverse-operations/
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
    string data = readtxt(DIR + '/' + target_fun);
    using p = decltype(arguments(TARGET));
    auto cases = parse<p>(data);
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