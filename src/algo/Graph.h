#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <queue>

using namespace std;

/*
Precondition: Node 1 and Node n on the same connected component
Getting minimal weighted edge within connected component that includes Node 1 and Node n
https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
*/
int minScore(int n, vector<vector<int>>& roads) {
    vector<vector<pair<int,int>>> adjList(n+1);
    for (vector<int>& r : roads)
    {
        adjList[r[0]].push_back({r[1], r[2]});
        adjList[r[1]].push_back({r[0], r[2]});
    }
    int res = INT32_MAX;
    vector<int8_t> visited(n+1, 0);
    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (auto next : adjList[cur])
        {
            res = min(res, next.second);
            if (visited[next.first] == 0)
            {
                q.push(next.first);
                visited[next.first] = 1;
            }
        }
    }
    return res;
}


#endif