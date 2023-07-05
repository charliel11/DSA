#pragma once

#include <DSA/UnionFind.h>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

namespace dsa {
namespace graph {

namespace shortest_path {

// TODO: there is no path from s to t
inline vector<int> restore_path(int s, int t, vector<int> const &p) {
  vector<int> path;

  for (int v = t; v != s; v = p[v])
    path.push_back(v);
  path.push_back(s);

  reverse(path.begin(), path.end());
  return path;
}

template <typename T, typename Relax, typename Select>
void dijkstra(vector<vector<pair<T, int>>> &adj_list, int start,
              const Relax &relax, const Select &select) {

  while (true) {
    int cur = select();
    if (cur == -1)
      break;

    for (auto &next : adj_list[cur]) {
      relax(cur, next);
    }
  }
  return;
}

template <typename T, class Compare = less<T>, class Product = plus<T>>
void dijkstra_origin(vector<vector<pair<T, int>>> &adj_list, int start,
                     vector<T> &shortest_path, vector<int> &predecessor) {

  int n = adj_list.size();
  vector<int8_t> seen(n, 0);
  auto select = [&]() {
    int res = -1;
    for (int i = 0; i < seen.size(); ++i) {
      if (!seen[i] &&
          (res == -1 || Compare{}(shortest_path[i], shortest_path[res])))
        res = i;
    }
    if (res != -1)
      seen[res] = 1;
    return res;
  };

  auto relax = [&](int cur, pair<T, int> next) {
    if (Compare{}(Product{}(shortest_path[cur], next.first),
                  shortest_path[next.second])) {
      shortest_path[next.second] = shortest_path[cur] * next.first;
      predecessor[next.second] = cur;
    }
  };

  dijkstra(adj_list, start, relax, select);
}

template <typename T, class Compare = less<T>, class Product = plus<T>>
void dijkstra_pq(vector<vector<pair<T, int>>> &adj_list, int start,
                 vector<T> &shortest_path, vector<int> &predecessor) {

  priority_queue<pair<double, int>> pq;
  pq.push({shortest_path[start], start});

  auto select = [&]() {
    if (pq.empty())
      return -1;

    int res = pq.top().second;
    pq.pop();
    return res;
  };

  auto relax = [&](int cur, pair<T, int> next) {
    if (Compare{}(Product{}(shortest_path[cur], next.first),
                  shortest_path[next.second])) {
      shortest_path[next.second] = Product{}(shortest_path[cur], next.first);
      predecessor[next.second] = cur;
      pq.push({shortest_path[next.second], next.second});
    }
  };

  dijkstra(adj_list, start, relax, select);
}

template <typename T, class Compare = less<T>, class Product = plus<T>>
void dijkstra_set(vector<vector<pair<T, int>>> &adj_list, int start,
                  vector<T> &shortest_path, vector<int> &predecessor) {

  set<pair<double, int>, std::greater<>> s;
  s.insert({shortest_path[start], start});

  auto select = [&]() {
    if (s.empty())
      return -1;
    int res = s.begin()->second;
    s.erase(s.begin());
    return res;
  };

  auto relax = [&](int cur, pair<double, int> next) {
    if (Compare{}(Product{}(shortest_path[cur], next.first),
                  shortest_path[next.second])) {
      s.erase({shortest_path[next.second], next.second});
      shortest_path[next.second] = Product{}(shortest_path[cur], next.first);
      predecessor[next.second] = cur;
      s.insert({shortest_path[next.second], next.second});
    }
  };

  dijkstra(adj_list, start, relax, select);
}

/*
https://leetcode.com/problems/path-with-maximum-probability/
*/
inline double maxProbability(int n, vector<vector<int>> &edges,
                             vector<double> &succProb, int start, int end) {

  vector<vector<pair<double, int>>> adj_list(n);
  for (int i = 0; i < edges.size(); ++i) {
    auto e = edges[i];
    adj_list[e[0]].push_back({succProb[i], e[1]});
    adj_list[e[1]].push_back({succProb[i], e[0]});
  }

  vector<double> prob(n, 0);
  vector<int> pred(n, -1);
  prob[start] = 1;
  dsa::graph::shortest_path::dijkstra_pq<double, greater<double>,
                                         multiplies<double>>(adj_list, start,
                                                             prob, pred);
  return prob[end];
}
} // namespace shortest_path

namespace connected_component {

inline int max_connected_component(vector<vector<int>> adj_list) {
  int n = adj_list.size();
  vector<int> v(n, -1);

  auto dfs = [&](const auto &dfs, int i, int root) -> int {
    v[i] = root;
    int cnt = 1;
    for (int next : adj_list[i]) {
      if (v[next] != root) {
        cnt += dfs(dfs, next, root);
      }
    }
    return cnt;
  };

  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (v[i] == -1)
      res = std::max(res, dfs(dfs, i, i));
  }
  return res;
}

/*
https://leetcode.com/problems/detonate-the-maximum-bombs/
*/
inline int maximumDetonation(vector<vector<int>> &bombs) {
  int n = bombs.size();
  vector<vector<int>> adj_list(n);

  int64_t r1, r2, dist;
  for (int i = 0; i < n - 1; ++i) {
    r1 = bombs[i][2];
    r1 *= r1;
    for (int j = i + 1; j < n; ++j) {
      int64_t dx = bombs[i][0] - bombs[j][0];
      int64_t dy = bombs[i][1] - bombs[j][1];
      dist = (dx * dx) + (dy * dy);
      if (dist <= r1) {
        adj_list[i].push_back(j);
      }
      r2 = bombs[j][2];
      r2 *= r2;
      if (dist <= r2) {
        adj_list[j].push_back(i);
      }
    }
  }

  return max_connected_component(adj_list);
}

} // namespace connected_component

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
https://johannesugb.github.io/cpu-programming/how-to-pass-lambda-functions-in-C++/

acyclic and directed graph => multi-root tree
*/
template <typename Func1, typename Func2>
bool is_acyclic_dfs(vector<vector<int>> &adj_list, const Func1 &merge,
                    const Func2 &update) {
  int n = adj_list.size();
  vector<int8_t> recursion_stack(n, 0);
  vector<int8_t> visit(n, 0);
  bool acyclic = true;

  auto dfs = [&](const auto &dfs, int i) -> bool {
    if (!acyclic)
      return acyclic;
    if (visit[i] == 1)
      return true;
    visit[i] = recursion_stack[i] = 1;
    for (int next : adj_list[i]) {
      if (recursion_stack[next] == 1 || !dfs(dfs, next)) {
        return acyclic = false;
      }
      merge(i, next); // merge current node and child node result
    }
    update(i);              // update current node result
    recursion_stack[i] = 0; // pop out
    return acyclic;
  };

  for (int i = 0; i < n; ++i) {
    if (visit[i] == 0 && !dfs(dfs, i))
      return false;
  }

  return true;
}

/*
TODO: graph_bfs_XXX
*/

/*
https://leetcode.com/problems/largest-color-value-in-a-directed-graph/

acyclic and directed graph => multi-root tree
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

  if (!is_acyclic_dfs(adj_list, merge, update))
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
  return is_acyclic_dfs(graph, merge, update);
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
  is_acyclic_dfs(graph, merge, update);
  reverse(out.begin(), out.end());
  return out;
}
} // namespace graph
} // namespace dsa