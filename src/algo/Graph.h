#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <queue>

#include "UnionFind.h"

using namespace std;

/*
Precondition: Node 1 and Node n on the same connected component
Getting minimal weighted edge within connected component that includes Node 1 and Node n
https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
*/
int32_t minScore(int32_t n, vector<vector<int32_t>> &roads)
{
    UnionFind uf(n + 1);
    vector<int32_t> min_dist(n + 1, INT32_MAX);
    for (auto &edge : roads)
    {
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

int32_t makeConnected(int32_t n, vector<vector<int32_t>> &connections)
{
    if (connections.size() + 1 < n)
        return -1;
    UnionFind uf(n);
    int32_t n_connected_component = n;
    for (auto &edge : connections)
    {
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
int32_t minReorder(int32_t n, vector<vector<int32_t>> &connections)
{

    return 0;
}

/*
https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
*/
int64_t countPairs(int32_t n, vector<vector<int32_t>> &edges)
{
    UnionFind uf(n);
    vector<int32_t> root_cnt(n, 1);
    for (auto &edge : edges)
    {
        int r1 = uf.find_root(edge[0]);
        int r2 = uf.find_root(edge[1]);
        if (r1 > r2)
            swap(r1, r2);
        if (r1 != r2)
        {
            uf.insert(r2, r1);
            root_cnt[r1] += root_cnt[r2];
        }
    }

    int64_t res = 0ll;
    int32_t prev = 0;
    for (uint64_t i = 0; i < n; ++i)
        if (uf._parent[i] == i)
        {
            res += root_cnt[i] * (n - root_cnt[i] - prev);
            prev += root_cnt[i];
        }

    return res;
}

/*
https://leetcode.com/problems/longest-cycle-in-a-graph/
*/
int32_t longestCycle(vector<int32_t> &edges)
{
    int32_t n = edges.size();
    vector<int32_t> in_degree(n, 0);
    vector<int8_t> visit(n, 0);

    for (int32_t i = 0; i < n; ++i)
    {
        if (edges[i] == -1)
            continue;
        ++in_degree[edges[i]];
    }

    queue<int32_t> q;
    for (int32_t i = 0; i < n; ++i)
        if (in_degree[i] == 0)
            q.push(i);

    int32_t no_cycle = n;
    while (!q.empty())
    {
        int32_t cur = q.front();
        visit[cur] = 1;
        q.pop();
        --no_cycle;
        int32_t next = edges[cur];
        if (next != -1)
        {
            --in_degree[next];
            if (in_degree[next] == 0)
                q.push(next);
        }
    }
    if (no_cycle == 0)
        return -1;

    int32_t res = 0;
    for (int32_t i = 0; i < n; ++i)
    {
        if (visit[i] == 1)
            continue;

        int32_t cur = i;
        int32_t cnt = 0;
        while (visit[edges[cur]] != 1)
        {
            ++cnt;
            cur = edges[cur];
            visit[cur] = 1;
        }
        res = max(res, cnt);
    }
    return res;
}
int32_t longestCycle_(vector<int32_t> &edges)
{
    const int32_t n = edges.size();
    int32_t ans = -1, time = 1;
    vector<int32_t> time_visited(n);

    for (int32_t i = 0; i < n; ++i)
    {
        if (time_visited[i] > 0)
        {
            continue;
        }

        const int32_t start_time = time;
        int32_t j = i;
        while (j >= 0 && time_visited[j] == 0)
        {
            time_visited[j] = time++;
            j = edges[j];
        }

        if (j != -1 && time_visited[j] >= start_time)
        {
            ans = max(ans, time - time_visited[j]);
        }
    }
    return ans;
}

/* 47. Permutations II
https://leetcode.com/problems/permutations-ii/description/
*/
bool _IsB4Duplicated(int st, int end, vector<int> &nums)
{
    for (int k = st; k < end; k++)
    {
        if (nums[k] == nums[end])
        {
            return true;
        }
    }

    return false;
}
void _PermuteUniqueHelper(vector<vector<int>> &ans, vector<int> &candidates, const int &i)
{
    if (i == candidates.size())
    {
        ans.push_back(candidates);

        return;
    }

    for (int j = i; j < candidates.size(); ++j)
    {
        if ((j == i || candidates[i] != candidates[j]) && !_IsB4Duplicated(i, j, candidates))
        {
            swap(candidates[i], candidates[j]);
            _PermuteUniqueHelper(ans, candidates, i + 1);
            swap(candidates[i], candidates[j]);
        }
    }
}
vector<vector<int>> PermuteUnique(vector<int> &nums)
{
    vector<vector<int>> out;
    vector<int> subOut;
    // sort(nums.begin(), nums.end());
    _PermuteUniqueHelper(out, nums, 0);

    return out;
}

#endif