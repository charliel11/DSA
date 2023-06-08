#pragma once

#include <DSA/PrefixSum.h>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <stdint.h>
#include <string>
#include <vector>


using namespace std;

namespace dp {

/*
https://leetcode.com/problems/jump-game-ii/
*/
inline int32_t jump(vector<int32_t> &nums) {
  int s = 0;
  return 0;
}

/*
https://leetcode.com/problems/minimum-path-sum/
*/
inline int32_t minPathSum(vector<vector<int32_t>> &grid) {
  int32_t m = grid.size(), n = grid[0].size();
  for (int32_t i = 1; i < n; i++)
    grid[0][i] += grid[0][i - 1];

  for (int32_t i = 1; i < m; i++) {
    grid[i][0] += grid[i - 1][0];
    for (int32_t j = 1; j < n; j++) {
      grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);
    }
  }
  return grid[m - 1][n - 1];
}

/*
https://leetcode.com/problems/minimum-cost-for-tickets/description/
RECAP:
*/
// inline int mincostTickets(vector<int> &days, vector<int> &costs) {
//     int n = days.size();
//     auto dp = vector<int>(366, -1);

//     auto dfs = [&](const auto &dfs, int i) {
//         if (i == 366)
//             return 0;

//         if (dp[i][ticket] != -1)
//             return dp[i][ticket];

//         int res = INT_MAX;
//         int next = i + 1;
//         if (days[i] > ticket) {
//             res = std::min(res, dfs(dfs, next, days[i]) + costs[0]);
//             res = std::min(res, dfs(dfs, next, days[i] + 6) + costs[1]);
//             res = std::min(res, dfs(dfs, next, days[i] + 29) + costs[2]);
//         } else {
//             res = std::min(res, dfs(dfs, next, ticket));
//         }

//         return dp[i][ticket] = res;
//     };

//     return dfs(dfs, 0, 0);
// }

namespace split_array {

/*
https://leetcode.com/problems/minimum-cost-to-split-an-array/description/
*/

inline int32_t minCost(vector<int32_t> &nums, int32_t k) {
  int32_t n = nums.size();
  int32_t dp[1001]{0};
  vector<vector<int32_t>> trim_table(n, vector<int32_t>(n, 0));
  vector<int32_t> cnt(n, 0);
  for (int32_t i = 0; i < n; ++i) {
    int32_t len = 0;
    for (int32_t j = i; j < n; ++j) {
      len += cnt[nums[j]] == 1 ? 2 : cnt[nums[j]] > 1 ? 1 : 0;
      ++cnt[nums[j]];
      trim_table[i][j] = len;
    }
    fill(cnt.begin(), cnt.end(), 0);
  }

  auto dfs = [&](const auto &dfs, size_t i) {
    if (i == n)
      return 0;
    if (dp[i] != 0)
      return dp[i];

    int32_t res = INT32_MAX;
    for (size_t j = i; j < n; ++j) {
      res = min(res, dfs(dfs, j + 1) + trim_table[i][j] + k);
    }

    return dp[i] = res;
  };

  return dfs(dfs, 0);
}

/*
https://leetcode.com/problems/restore-the-array/
*/
inline int32_t numberOfArrays(string s, int32_t k) {
  int32_t m = 1e9 + 7;
  size_t n = s.size();
  int32_t dp[100001]{0};

  auto dfs = [&](const auto &dfs, size_t i) {
    if (i == n)
      return 1;
    if (s[i] == '0')
      return 0;
    if (dp[i] != 0)
      return dp[i];

    int64_t val = 0;
    int64_t res = 0;
    for (size_t j = i; j < n; ++j) {
      val = val * 10 + (s[j] - '0');
      if (val > k)
        break;
      res = (res + dfs(dfs, j + 1)) % m;
    }
    return dp[i] = res;
  };

  return dfs(dfs, 0);
}

} // namespace split_array

/*
https://leetcode.com/problems/scramble-string/

*/
inline bool isScramble(string s1, string s2) {
  int32_t n1 = s1.size();
  int8_t dp[31][31][31];
  memset(dp, 0, sizeof(dp));
  auto dfs = [&](auto const &dfs, int32_t l1, int32_t r1, int32_t l2, int32_t r2) -> bool {
    if (l1 == r1)
      return s1[l1] == s2[l2];

    if (dp[l1][r1][l2] != 0)
      return dp[l1][r1][l2] == 1;

    dp[l1][r1][l2] = -1;
    int32_t len = r1 - l1;
    for (int32_t i = 0; i < len; ++i) {
      // l1 = 0, r1 = 5 [XXXXXX]
      // i = 0,1,2,3,4
      if (dfs(dfs, l1, l1 + i, l2, l2 + i) && dfs(dfs, l1 + i + 1, r1, l2 + i + 1, r2)) {
        dp[l1][r1][l2] = 1;
        break;
      }
      if (dfs(dfs, l1, l1 + i, r2 - i, r2) && dfs(dfs, l1 + i + 1, r1, l2, r2 - i - 1)) {
        dp[l1][r1][l2] = 1;
        break;
      }
    }
    return dp[l1][r1][l2] == 1;
  };
  bool res = dfs(dfs, 0, n1 - 1, 0, n1 - 1);
  return res;
}

namespace preprocessing {

/*
REVIEW:

* pattern: using precompute to reduce dp complexity(3d -> 2d)

*/

/*
https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/

"aba"

"acca"
"bbbb"
"caca"

f(0,0) -> cnt(0) * f(1,1)
       -> f(1,0)

*/
inline int32_t numWays(vector<string> &words, string target) {
  int32_t m = 1e9 + 7;
  size_t wn = 0;
  size_t tn = target.size();

  int32_t freq[1001][26]{0};
  for (size_t i = 0; i < words.size(); ++i) {
    wn = max(wn, words[i].size());
    for (size_t j = 0; j < words[i].size(); ++j) {
      ++freq[j][words[i][j] - 'a'];
    }
  }
  vector<vector<int32_t>> dp(wn, vector<int32_t>(tn, -1));

  auto dfs = [&](const auto &dfs, size_t idx, size_t t) {
    if (t == tn)
      return 1;
    if (idx == wn)
      return 0;

    if (dp[idx][t] != -1)
      return dp[idx][t];

    int64_t res = 0;
    if (freq[idx][target[t] - 'a'] > 0) {
      int64_t cnt = freq[idx][target[t] - 'a'];
      res += cnt * dfs(dfs, idx + 1, t + 1);
    }
    res += dfs(dfs, idx + 1, t);
    return dp[idx][t] = (res % m);
  };

  return dfs(dfs, 0, 0);
}

/*
https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/description/

f(n,k) = max(f(n+1,k-1) + n1[1],
             f(n+1,k-2) + n1[1] + n1[2],
             ...,
             f(n+1,0) + n1[1] + n1[2] + ... + n1[k],
             f(n+1,k))
*/
inline int32_t maxValueOfCoins(vector<vector<int32_t>> &piles, int32_t k) {
  size_t n = piles.size();
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 1; j < piles[i].size(); j++) {
      piles[i][j] += piles[i][j - 1];
    }
  }

  vector<vector<int32_t>> dp(n, vector<int32_t>(k + 1, -1));
  auto dfs = [&dp, &piles](auto const &dfs, size_t idx, size_t k) {
    if (k == 0 || idx == piles.size())
      return 0;

    if (dp[idx][k] != -1)
      return dp[idx][k];

    int32_t ans = dfs(dfs, idx + 1, k);
    size_t len = piles[idx].size();
    for (int i = 0; i < min(k, len); i++) {
      ans = max(ans, piles[idx][i] + dfs(dfs, idx + 1, k - i - 1));
    }
    return dp[idx][k] = ans;
  };
  return dfs(dfs, 0, k);
}

/*
https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/

[
    ".A..A",
    "A.A..",
    "A.AA.",
    "AAAA.",
    "A.AA."
]

*/
inline int32_t ways(vector<string> &pizza, int32_t k) {
  int32_t row = pizza.size(), col = pizza[0].size();
  vector<vector<int32_t>> cnt(row, vector<int32_t>(col, 0));
  for (int32_t r = 0; r < row; ++r) {
    for (int32_t c = 0; c < col; ++c)
      cnt[r][c] = (pizza[r][c] == 'A');
  }
  NumMatrix apple(cnt);

  int32_t dp[51][51][11];
  memset(dp, 0xff, sizeof(dp));
  auto dfs = [&](auto const &dfs, int32_t idx, int32_t r1, int32_t c1) {
    if (idx == k) {
      if (apple.sumRegion(r1, c1, row - 1, col - 1) > 0)
        return 1;
      else
        return 0;
    }

    if (dp[r1][c1][idx] != -1) {
      return dp[r1][c1][idx];
    }

    int32_t cnt = 0;
    for (int32_t i = r1; i < row - 1; ++i) {
      if (apple.sumRegion(r1, c1, i, col - 1) > 0)
        cnt = (cnt + dfs(dfs, idx + 1, i + 1, c1)) % 1000000007;
    }
    for (int32_t i = c1; i < col - 1; ++i) {
      if (apple.sumRegion(r1, c1, row - 1, i) > 0)
        cnt = (cnt + dfs(dfs, idx + 1, r1, i + 1)) % 1000000007;
    }
    return dp[r1][c1][idx] = cnt;
  };

  int32_t res = dfs(dfs, 1, 0, 0);

  return res;
}

inline int ways1(vector<string> &pizza, int k) {
  const int mod = 1000000000 + 7;
  int rows = pizza.size();
  int cols = pizza[0].size();
  int cnt[55][55] = {};

  for (int i = 1; i <= rows; i++)
    for (int j = 1; j <= cols; j++) {
      cnt[i][j] = cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] +
                  (pizza[rows - i][cols - j] == 'A' ? 1 : 0);
    }

  int dp[55][55][11] = {};
  for (int i = 0; i <= rows; i++)
    dp[i][0][0] = 1;

  for (int i = 0; i <= rows; i++)
    for (int j = 0; j <= cols; j++)
      for (int p = 0; p < k; p++)
        if (dp[i][j][p]) {
          for (int ii = i + 1; ii <= rows; ii++)
            if (cnt[ii][j] - cnt[i][j] > 0)
              dp[ii][j][p + 1] = (dp[ii][j][p + 1] + dp[i][j][p]) % mod;
          for (int jj = j + 1; jj <= cols; jj++)
            if (cnt[i][jj] - cnt[i][j] > 0)
              dp[i][jj][p + 1] = (dp[i][jj][p + 1] + dp[i][j][p]) % mod;
        }
  return dp[rows][cols][k];
}

} // namespace preprocessing

namespace mask {

/*
https://leetcode.com/problems/maximize-score-after-n-operations/

(1, ..., 14)
(1,2)->(3,4)-> ...
(1,3)->(2,4)-> ...
*/
inline int maxScore(vector<int> &nums) {

  auto gcd = [](const auto &gcd, int a, int b) {
    if (b == 0)
      return a;
    return gcd(gcd, b, a % b);
  };

  int n = nums.size();
  int res = 0;
  vector<vector<int>> dp(1 << n, vector<int>((n >> 1) + 1, 0));
  auto dfs = [&](const auto &dfs, int mask, int idx) {
    if (mask == 0) {
      return 0;
    }

    if (dp[mask][idx] != 0) {
      return dp[mask][idx];
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        for (int j = i + 1; j < n; ++j) {
          if (mask & (1 << j)) {
            int next = (mask ^ (1 << i));
            next ^= (1 << j);
            // print(next);
            res = std::max(res, idx * gcd(gcd, nums[i], nums[j]) + dfs(dfs, next, idx + 1));
          }
        }
      }
    }
    return dp[mask][idx] = res;
  };
  int mask = (1 << n) - 1;
  res = dfs(dfs, mask, 1);
  return res;
}
} // namespace mask

namespace game_theory {

/*
https://leetcode.com/problems/stone-game-iii
*/
inline string stoneGameIII(vector<int> &stoneValue) {
  int n = stoneValue.size();
  vector<int> dp(n, -1);

  auto dfs = [&](const auto &dfs, int s) {
    if (s >= n)
      return 0;

    if (dp[s] != -1)
      return dp[s];

    int sum = stoneValue[s];
    int res = sum - dfs(dfs, s + 1);
    if (s + 1 < n) {
      sum += stoneValue[s + 1];
      res = std::max(res, sum - dfs(dfs, s + 2));
    }
    if (s + 2 < n) {
      sum += stoneValue[s + 2];
      res = std::max(res, sum - dfs(dfs, s + 3));
    }

    return dp[s] = res;
  };

  int res = dfs(dfs, 0);
  return res == 0 ? "Tie" : res > 0 ? "Alice" : "Bob";
}
} // namespace game_theory

/*
https://leetcode.com/problems/coin-change/description/

TODO: Unbound knapsack problem
```
* 狀態轉移關係圖
dp[i-1][0] | dp[i-1][1] | ... | dp[i-1][j] | ... | dp[i-1][W]
                                     |
                  |------------------|
dp[i][0]  |  dp[i][1]  | ... |  dp[i][j]  | ... |  dp[i][W]
```

1. | : 不考慮第i件物品
2. |- : 考慮第i件物品。因為物品有無限多個，所以此時應該轉移到
dp[i][j-w[i]]，及裝入第 i 種物品還可以繼續裝入第 i 種物品

* $dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i])，j >= w[i]$

    0 | 1 | 2 | 3 | ... | amount
_   0 | x | x | x | ... | x
1   0 | 1 | 2 | 3 | ... | amount
2   0 | 1 | 2 | 1 | 2
5   x

*/
inline int32_t coinChange1(vector<int32_t> &coins, int32_t amount) {
  int32_t dp[13][10001]{};
  int32_t n = coins.size();

  dp[0][0] = 0;
  fill(begin(dp[0]), begin(dp[0]) + amount + 1, INT32_MAX - 1);
  for (int32_t i = 1; i <= n; ++i) {
    fill(begin(dp[i]), begin(dp[i]) + amount + 1, INT32_MAX - 1);
    dp[i][0] = 0;
    int32_t coin = coins[i - 1];
    for (int32_t j = 1; j <= amount; ++j) {
      if (j - coin < 0)
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = min(dp[i - 1][j], dp[i][j - coin] + 1);
    }
  }

  return dp[n][amount] == INT32_MAX - 1 ? -1 : dp[n][amount];
}

inline int32_t coinChange(vector<int32_t> &coins, int32_t amount) {
  int32_t dp[13][10001];
  memset(dp, -1, sizeof(dp));
  int32_t n = coins.size();

  auto dfs = [&](const auto &dfs, int32_t i, int32_t m) -> int32_t {
    if (m < 0)
      return 1e9;
    if (i == n) {
      return m == 0 ? 0 : 1e9;
    }
    if (dp[i][m] != -1)
      return dp[i][m];
    int32_t tmp = dfs(dfs, i + 1, m);
    int32_t sum = 0;
    int32_t coin = coins[i];
    for (int32_t j = 1; sum <= m; ++j) {
      sum += coin;
      tmp = std::min(tmp, j + dfs(dfs, i + 1, m - sum));
    }

    return dp[i][m] = tmp;
  };
  int32_t res = dfs(dfs, 0, amount);

  return res >= 1e9 ? -1 : res;
}

// int dp[10001][12];
// int helper(vector<int> &coins, int amt, int i) {
//     if (amt < 0)
//         return 1e9; // for i>=0
//     if (amt == 0)
//         return 0;
//     if (i < 0)
//         return 1e9; // amount > or <
//     if (dp[amt][i] != -1)
//         return dp[amt][i];

//     return dp[amt][i] = min(helper(coins, amt - coins[i], i) + 1,
//     helper(coins, amt, i - 1));
// }
// int coinChange(vector<int> &coins, int amount) {
//     int n = coins.size();
//     memset(dp, -1, sizeof dp);
//     int ans = helper(coins, amount, n - 1);
//     return ans > 1e4 ? -1 : ans;
// }

} // namespace dp