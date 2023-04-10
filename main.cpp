#include <Utility.h>
#include <functional>
#include <parse.h>

#define TARGET largestPathValue

template <typename Op> bool graph_dfs(vector<vector<int32_t>> &graph, Op &op) {
    int32_t n = graph.size();
    vector<int8_t> visit(n, 0);
    vector<int8_t> done(n, 0);

    auto dfs = [&](const auto &dfs, int32_t i) -> bool {
        if (done[i] == 1)
            return true;

        done[i] = visit[i] = 1;
        for (int32_t next : graph[i]) {
            if (visit[next] == 1 || !dfs(dfs, next))
                return false;
            op.merge(i, next);
        }

        op.post_processing(i);
        visit[i] = 0;
        return true;
    };

    for (int32_t i = 0; i < n; ++i) {
        if (!dfs(dfs, i))
            return false;
    }

    return true;
}

/*
https://johannesugb.github.io/cpu-programming/how-to-pass-lambda-functions-in-C++/
*/
template <typename Func1, typename Func2>
bool graph_dfs1(vector<vector<int32_t>> &graph, const Func1 &func1, const Func2 &func2) {
    int32_t n = graph.size();
    vector<int8_t> visit(n, 0);
    vector<int8_t> done(n, 0);

    auto dfs = [&](const auto &dfs, int32_t i) -> bool {
        if (done[i] == 1)
            return true;

        done[i] = visit[i] = 1;
        for (int32_t next : graph[i]) {
            if (visit[next] == 1 || !dfs(dfs, next))
                return false;
            func1(i, next);
        }

        func2(i);
        visit[i] = 0;
        return true;
    };

    for (int32_t i = 0; i < n; ++i) {
        if (!dfs(dfs, i))
            return false;
    }

    return true;
}

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

    // struct Color {
    //     vector<vector<int32_t>> _cnt;
    //     string _color;
    //     Color(size_t n, string color) : _cnt(n, vector<int32_t>(26, 0)), _color(color) {}

    //     void merge(size_t i, size_t next) {
    //         for (int j = 0; j < 26; ++j)
    //             _cnt[i][j] = max(_cnt[i][j], _cnt[next][j]);
    //     }
    //     void post_processing(size_t i) { ++_cnt[i][_color[i] - 'a']; }
    // };
    // Color color(n, colors);
    // graph_dfs(adj_list, color);

    auto merge = [&](int32_t i, int32_t next) {
        for (int j = 0; j < 26; ++j)
            cnt[i][j] = max(cnt[i][j], cnt[next][j]);
    };
    auto post = [&](int32_t i) { ++cnt[i][colors[i] - 'a']; };
    if (!graph_dfs1(adj_list, merge, post))
        return -1;

    int32_t res = -1;
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