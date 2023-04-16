#include <Utility.h>
#include <functional>
#include <parse.h>
#include <stdint.h>
#include <vcruntime.h>

#define TARGET numWays

/*
https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/

"aba"

"acca"
"bbbb"
"caca"

f(0,0) -> cnt(0) * f(1,1)
       -> f(1,0)

*/
int32_t numWays(vector<string> &words, string target) {
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
int32_t maxValueOfCoins(vector<vector<int32_t>> &piles, int32_t k) {
    size_t n = piles.size();
    vector<vector<int32_t>> dp(n, vector<int32_t>(k + 1, -1));
    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 1; j < piles[i].size(); j++) {
            piles[i][j] += piles[i][j - 1];
        }
    }

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
https://leetcode.com/problems/longest-palindromic-subsequence/

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