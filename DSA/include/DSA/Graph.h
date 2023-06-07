#pragma once

#include <DSA/UnionFind.h>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <string>
#include <vector>

using namespace std;

namespace dsa {
namespace graph {

/*
https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/

Precondition: Node 1 and Node n on the same connected component
Getting minimal weighted edge within connected component that includes Node 1
and Node n
*/
inline int minScore(int n, vector<vector<int>> &roads) {
  UnionFind uf(n + 1);
  vector<int> min_dist(n + 1, INT32_MAX);
  for (auto &edge : roads) {
    int r1 = uf.find_root(edge[0]);
    int r2 = uf.find_root(edge[1]);
    if (r1 > r2)
      swap(r1, r2);
    uf.insert(r2, r1);
    min_dist[r1] = min(min_dist[r1], min(min_dist[r2], edge[2]));
  }
  return min_dist[1];

  // vector<vector<pair<int, int>>> adjList(n + 1);
  // for (vector<int> &r : roads)
  // {
  //     adjList[r[0]].push_back({r[1], r[2]});
  //     adjList[r[1]].push_back({r[0], r[2]});
  // }
  // int res = int32_MAX;
  // vector<int8_t> visited(n + 1, 0);
  // queue<int> q;
  // q.push(1);
  // visited[1] = 1;

  // while (!q.empty())
  // {
  //     int cur = q.front();
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
inline int makeConnected(int n, vector<vector<int>> &connections) {
  if (connections.size() < n - 1)
    return -1;
  UnionFind uf(n);
  int n_connected_component = n;
  for (auto &edge : connections) {
    int r1 = uf.find_root(edge[0]);
    int r2 = uf.find_root(edge[1]);
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
inline int minReorder(int n, vector<vector<int>> &connections) { return 0; }

/*
https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/

n1*n2*n3*n4 + n2*n3*n4 + n3*n4 => O(n^2)

sum = n1+n2+n3+n3;
n1*(sum-n1) + n2*(sum-n1-n2) + n3*(sum-n1-n2-n3) => O(n)
*/
inline int64_t countPairs(int n, vector<vector<int>> &edges) {
  UnionFind uf(n);
  vector<int> root_cnt(n, 1);
  for (auto &edge : edges) {
    int r1 = uf.find_root(edge[0]);
    int r2 = uf.find_root(edge[1]);
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
https://johannesugb.github.io/cpu-programming/how-to-pass-lambda-functions-in-C++/
*/
template <typename Func1, typename Func2>
bool graph_dfs_acyclic(vector<vector<int>> &graph, const Func1 &merge,
                       const Func2 &update) {
  int n = graph.size();
  vector<int8_t> visit(n, 0);
  vector<int8_t> done(n, 0);
  bool acyclic = true;

  auto dfs = [&](const auto &dfs, int i) -> bool {
    if (!acyclic)
      return acyclic;
    if (done[i] == 1)
      return true;
    done[i] = visit[i] = 1;
    for (int next : graph[i]) {
      if (visit[next] == 1 || !dfs(dfs, next)) {
        return acyclic = false;
      }
      merge(i, next);
    }
    update(i);
    visit[i] = 0;
    return acyclic;
  };

  for (int i = 0; i < n; ++i) {
    if (!done[i] && !dfs(dfs, i))
      return false;
  }

  return true;
}

/*
TODO: graph_bfs_XXX
*/

/*
https://leetcode.com/problems/longest-cycle-in-a-graph/

BFS detect cycle

RECAP:
*/
inline int longestCycle(vector<int> &edges) {
  int n = edges.size();
  vector<int> in_degree(n, 0);
  vector<int8_t> visit(n, 0);

  for (int i = 0; i < n; ++i) {
    if (edges[i] == -1)
      continue;
    ++in_degree[edges[i]];
  }

  queue<int> q;
  for (int i = 0; i < n; ++i)
    if (in_degree[i] == 0)
      q.push(i);

  int no_cycle = n;
  while (!q.empty()) {
    int cur = q.front();
    visit[cur] = 1;
    q.pop();
    --no_cycle;
    int next = edges[cur];
    if (next != -1) {
      --in_degree[next];
      if (in_degree[next] == 0)
        q.push(next);
    }
  }
  if (no_cycle == 0)
    return -1;

  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (visit[i] == 1)
      continue;

    int cur = i;
    int cnt = 0;
    while (visit[edges[cur]] != 1) {
      ++cnt;
      cur = edges[cur];
      visit[cur] = 1;
    }
    res = max(res, cnt);
  }
  return res;
}
inline int longestCycle_(vector<int> &edges) {
  const int n = edges.size();
  int ans = -1, time = 1;
  vector<int> time_visited(n);

  for (int i = 0; i < n; ++i) {
    if (time_visited[i] > 0) {
      continue;
    }

    const int start_time = time;
    int j = i;
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
TODO: 4-directionally dfs
*/

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
inline int closedIsland(vector<vector<int>> &grid) {
  size_t row = grid.size();
  size_t col = grid[0].size();

  int res = 0;
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

/*
https://leetcode.com/problems/number-of-enclaves/
*/
inline int numEnclaves(vector<vector<int>> &grid) {
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

  int res = 0;
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
https://leetcode.com/problems/largest-color-value-in-a-directed-graph/

RECAP:
*/
inline int largestPathValue(string colors, vector<vector<int>> &edges) {
  size_t n = colors.size();
  vector<vector<int>> adj_list(n);
  vector<int> in_degree(n, 0);
  vector<vector<int>> cnt(n, vector<int>(26, 0));

  for (auto &e : edges) {
    ++in_degree[e[1]];
    adj_list[e[0]].push_back(e[1]);
  }

  auto merge = [&](int i, int next) {
    for (int j = 0; j < 26; ++j)
      cnt[i][j] = max(cnt[i][j], cnt[next][j]);
  };
  auto update = [&](int i) { ++cnt[i][colors[i] - 'a']; };
  if (!graph_dfs_acyclic(adj_list, merge, update))
    return -1;

  int res = -1;
  for (size_t i = 0; i < n; ++i) {
    if (in_degree[i] == 0) {
      res = max(res, *max_element(begin(cnt[i]), end(cnt[i])));
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
inline bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {

  // * Create graph
  vector<vector<int>> graph(numCourses);
  for (auto &edge : prerequisites)
    graph[edge[1]].push_back(edge[0]);

  auto merge = [&](int i, int next) {};
  auto update = [&](int i) {};
  return graph_dfs_acyclic(graph, merge, update);
}

/* 210. Course Schedule II
https://leetcode.com/problems/course-schedule-ii/
O(V+E)
*/
inline vector<int> findOrder(int numCourses,
                             vector<vector<int>> &prerequisites) {
  vector<int> out;
  // * Create graph
  vector<vector<int>> graph(numCourses);
  for (auto &edge : prerequisites)
    graph[edge[1]].push_back(edge[0]);

  auto merge = [&](int i, int next) {};
  auto update = [&](int i) { out.push_back(i); };
  graph_dfs_acyclic(graph, merge, update);
  reverse(out.begin(), out.end());
  return out;
}
} // namespace graph
} // namespace dsa