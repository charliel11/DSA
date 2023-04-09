#include <Utility.h>
#include <functional>
#include <parse.h>

#define TARGET largestPathValue

/*
https://leetcode.com/problems/largest-color-value-in-a-directed-graph/

RECAP:
*/
int32_t largestPathValue(string colors, vector<vector<int32_t>> &edges) {
    size_t n = colors.size();
    vector<vector<int32_t>> adj_list(n);
    vector<int32_t> in_degree(n, 0);
    vector<int8_t> visited(n, 0);
    vector<int8_t> done(n, 0);
    vector<vector<int32_t>> cnt(n, vector<int32_t>(26, 0));

    for (auto &e : edges) {
        ++in_degree[e[1]];
        adj_list[e[0]].push_back(e[1]);
    }
    int32_t res = -1;
    bool is_cycle = false;

    auto dfs = [&](const auto &dfs, int32_t i) -> void {
        if (is_cycle)
            return;
        if (done[i] == 1) {
            return;
        }
        done[i] = 1;
        visited[i] = 1;
        for (auto &next : adj_list[i]) {
            if (visited[next] == 0) {
                dfs(dfs, next);
            } else {
                is_cycle = true;
                return;
            }
            for (int j = 0; j < 26; ++j)
                cnt[i][j] = max(cnt[i][j], cnt[next][j]);
        }
        ++cnt[i][colors[i] - 'a'];
        visited[i] = 0;
        return;
    };

    for (size_t i = 0; i < n; ++i) {
        dfs(dfs, i);
        if (is_cycle)
            return -1;
    }

    for (size_t i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            res = max(res, *max_element(begin(cnt[i]), end(cnt[i])));
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