#pragma once

#include <Utility.h>
#include <queue>
#include <vector>

#include <UnionFind.h>

#include <Utility.h>

using namespace std;

/*
https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/

Precondition: Node 1 and Node n on the same connected component
Getting minimal weighted edge within connected component that includes Node 1
and Node n
*/
int32_t minScore(int32_t n, vector<vector<int32_t>> &roads) {
    UnionFind uf(n + 1);
    vector<int32_t> min_dist(n + 1, INT32_MAX);
    for (auto &edge : roads) {
        int32_t r1 = uf.find_root(edge[0]);
        int32_t r2 = uf.find_root(edge[1]);
        if (r1 > r2)
            swap(r1, r2);
        uf.insert(r2, r1);
        min_dist[r1] = min(min_dist[r1], min(min_dist[r2], edge[2]));
    }
    return min_dist[1];

    // vector<vector<pair<int32_t, int32_t>>> adjList(n + 1);
    // for (vector<int32_t> &r : roads)
    // {
    //     adjList[r[0]].push_back({r[1], r[2]});
    //     adjList[r[1]].push_back({r[0], r[2]});
    // }
    // int32_t res = int32_t32_MAX;
    // vector<int32_t8_t> visited(n + 1, 0);
    // queue<int32_t> q;
    // q.push(1);
    // visited[1] = 1;

    // while (!q.empty())
    // {
    //     int32_t cur = q.front();
    //     q.pop();
    //     for (auto next : adjList[cur])
    //     {
    //         res = min(res, next.second);
    //         if (visited[next.first] == 0)
    //         {
    //             q.push(next.first);
    //             visited[next.first] = 1;
    //         }
    //     }
    // }
    // return res;
}

/*
https://leetcode.com/problems/number-of-operations-to-make-network-connected/

* One needs at least N-1 edges to connect N nodes in a connected component
* In a connected component of a graph, if the number of edges exceeds the number
of nodes, then the component necessarily contains redundant edges
*/
int32_t makeConnected(int32_t n, vector<vector<int32_t>> &connections) {
    if (connections.size() < n - 1)
        return -1;
    UnionFind uf(n);
    int32_t n_connected_component = n;
    for (auto &edge : connections) {
        int32_t r1 = uf.find_root(edge[0]);
        int32_t r2 = uf.find_root(edge[1]);
        if (r1 > r2)
            swap(r1, r2);
        uf.insert(r2, r1);
        if (r2 != r1)
            --n_connected_component;
    }
    return n_connected_component - 1;
}

/*
https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
*/
int32_t minReorder(int32_t n, vector<vector<int32_t>> &connections) { return 0; }

/*
https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/

n1*n2*n3*n4 + n2*n3*n4 + n3*n4 => O(n^2)

sum = n1+n2+n3+n3;
n1*(sum-n1) + n2*(sum-n1-n2) + n3*(sum-n1-n2-n3) => O(n)
*/
int64_t countPairs(int32_t n, vector<vector<int32_t>> &edges) {
    UnionFind uf(n);
    vector<int32_t> root_cnt(n, 1);
    for (auto &edge : edges) {
        int32_t r1 = uf.find_root(edge[0]);
        int32_t r2 = uf.find_root(edge[1]);
        if (r1 > r2)
            swap(r1, r2);
        if (r1 != r2) {
            uf.insert(r2, r1);
            root_cnt[r1] += root_cnt[r2];
        }
    }

    int64_t res = 0ll;
    int64_t remaining = n;
    for (uint64_t i = 0; i < n; ++i)
        if (uf._parent[i] == i) {
            remaining -= root_cnt[i];
            res += remaining * root_cnt[i];
        }

    return res;
}

/*
https://leetcode.com/problems/longest-cycle-in-a-graph/

BFS detect cycle

RECAP:
*/
int32_t longestCycle(vector<int32_t> &edges) {
    int32_t n = edges.size();
    vector<int32_t> in_degree(n, 0);
    vector<int8_t> visit(n, 0);

    for (int32_t i = 0; i < n; ++i) {
        if (edges[i] == -1)
            continue;
        ++in_degree[edges[i]];
    }

    queue<int32_t> q;
    for (int32_t i = 0; i < n; ++i)
        if (in_degree[i] == 0)
            q.push(i);

    int32_t no_cycle = n;
    while (!q.empty()) {
        int32_t cur = q.front();
        visit[cur] = 1;
        q.pop();
        --no_cycle;
        int32_t next = edges[cur];
        if (next != -1) {
            --in_degree[next];
            if (in_degree[next] == 0)
                q.push(next);
        }
    }
    if (no_cycle == 0)
        return -1;

    int32_t res = 0;
    for (int32_t i = 0; i < n; ++i) {
        if (visit[i] == 1)
            continue;

        int32_t cur = i;
        int32_t cnt = 0;
        while (visit[edges[cur]] != 1) {
            ++cnt;
            cur = edges[cur];
            visit[cur] = 1;
        }
        res = max(res, cnt);
    }
    return res;
}
int32_t longestCycle_(vector<int32_t> &edges) {
    const int32_t n = edges.size();
    int32_t ans = -1, time = 1;
    vector<int32_t> time_visited(n);

    for (int32_t i = 0; i < n; ++i) {
        if (time_visited[i] > 0) {
            continue;
        }

        const int32_t start_time = time;
        int32_t j = i;
        while (j >= 0 && time_visited[j] == 0) {
            time_visited[j] = time++;
            j = edges[j];
        }

        if (j != -1 && time_visited[j] >= start_time) {
            ans = max(ans, time - time_visited[j]);
        }
    }
    return ans;
}

/*
https://leetcode.com/problems/number-of-closed-islands/description/

NOTE: early return

return dfs(dfs, r - 1, c) && dfs(dfs, r, c - 1) && dfs(dfs, r + 1, c) &&
dfs(dfs, r, c + 1);

bool d1 = dfs(dfs, r - 1, c);
bool d2 = dfs(dfs, r, c - 1);
bool d3 = dfs(dfs, r + 1, c);
bool d4 = dfs(dfs, r, c + 1);
return d1 && d2 && d3 && d4;
*/
int32_t closedIsland(vector<vector<int32_t>> &grid) {
    size_t row = grid.size();
    size_t col = grid[0].size();

    int32_t res = 0;
    auto dfs = [&](const auto &dfs, size_t r, size_t c) -> bool {
        if ((r == 0 || c == 0 || r == row - 1 || c == col - 1) && grid[r][c] == 0)
            return false;
        if (grid[r][c] == 1 || grid[r][c] == 2)
            return true;
        grid[r][c] = 2;
        bool d1 = dfs(dfs, r - 1, c);
        bool d2 = dfs(dfs, r, c - 1);
        bool d3 = dfs(dfs, r + 1, c);
        bool d4 = dfs(dfs, r, c + 1);
        return d1 && d2 && d3 && d4;
    };
    for (size_t r = 1; r < row - 1; ++r) {
        for (size_t c = 1; c < col - 1; ++c) {
            if (grid[r][c] == 0) {
                if (dfs(dfs, r, c))
                    ++res;
            }
        }
    }
    return res;
}

/* 207.Course Schedule
https://leetcode.com/problems/course-schedule/
prerequisites[i] = [ai, bi] : bi -> ai
acyclic (no cycle) -> exists
O(V+E)
ref. https://www.scaler.com/topics/data-structures/topological-sort-algorithm/
*/

bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {

    // * Create graph
    vector<vector<int>> graph(numCourses);
    for (auto &edge : prerequisites)
        graph[edge[1]].push_back(edge[0]);

    // The process after this point has already been traversed (acyclic)
    vector<uint8_t> done(numCourses, 0); // vector<bool> C++17 以下要小心
    vector<uint8_t> visit(numCourses, 0);

    // * Acyclic
    auto isAcyclic = [](const auto &isAcyclic, vector<vector<int>> &graph, vector<uint8_t> &visit,
                        vector<uint8_t> &done, int node) {
        // 3 cases :
        // 1 . form a cycle
        if (visit[node])
            return 0;
        // 2. the process after this point has already been traversed
        if (done[node])
            return 1;
        // 3. not yet finished traversing
        done[node] = visit[node] = 1;
        for (auto child : graph[node]) {
            if (!isAcyclic(isAcyclic, graph, visit, done, child))
                return 0;
        }
        visit[node] = 0;
        return 1;
    };

    for (size_t i = 0; i < numCourses; ++i) {
        if (!done[i] && !isAcyclic(isAcyclic, graph, visit, done, i)) {
            return 0;
        }
    }
    return 1;
}

/* 210. Course Schedule II
https://leetcode.com/problems/course-schedule-ii/
O(V+E)
*/
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> out;
    // * Create graph
    vector<vector<int>> graph(numCourses);
    for (auto &edge : prerequisites)
        graph[edge[1]].push_back(edge[0]);

    vector<uint8_t> done(numCourses, 0); // vector<bool> C++17 以下要小心
    vector<uint8_t> visit(numCourses, 0);

    // * Acyclic
    auto isAcyclic = [&](const auto &isAcyclic, int node) {
        if (visit[node])
            return 0;
        if (done[node])
            return 1;

        done[node] = visit[node] = 1;
        for (auto neighbor : graph[node]) {
            if (!isAcyclic(isAcyclic, neighbor))
                return 0;
        }
        out.push_back(node);
        visit[node] = 0;
        return 1;
    };

    for (size_t i = 0; i < numCourses; ++i) {
        if (!done[i] && !isAcyclic(isAcyclic, i)) {
            return {};
        }
    }
    reverse(out.begin(), out.end());
    return out;
}