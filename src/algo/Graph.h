#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <queue>
#include <UnionFind.h>

using namespace std;

/*
Precondition: Node 1 and Node n on the same connected component
Getting minimal weighted edge within connected component that includes Node 1 and Node n
https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
*/
int minScore(int n, vector<vector<int>> &roads)
{
    UnionFind uf(n + 1);
    vector<int> min_dist(n + 1, INT32_MAX);
    for (auto &edge : roads)
    {
        int r1 = uf.find_root(edge[0]);
        int r2 = uf.find_root(edge[1]);
        if (r1 > r2) swap(r1, r2);
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
    // int res = INT32_MAX;
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

int makeConnected(int n, vector<vector<int>> &connections)
{
    if (connections.size() + 1 < n)
        return -1;
    UnionFind uf(n);
    int n_connected_component = n;
    for (auto &edge : connections)
    {
        int r1 = uf.find_root(edge[0]);
        int r2 = uf.find_root(edge[1]);
        if (r1 > r2) swap(r1, r2);
        uf.insert(r2, r1);
        if (r2 != r1) --n_connected_component;
    }
    return n_connected_component - 1;
}

#endif