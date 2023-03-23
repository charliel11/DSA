#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <Utility.h>

class UnionFind
{
    vector<int> _parent;

public:
    UnionFind(int n) : _parent(n)
    {
        iota(_parent.begin(), _parent.end(), 0);
    }
    void insert(int child, int parent)
    {
        _parent[child] = parent;
    }
    int find_root(int node)
    {
        while (_parent[node] != node)
            node = _parent[node];
        return node;
    }
    int merge(int node1, int node2)
    {
        int n1 = find_root(node1);
        int n2 = find_root(node2);
        if (n1 > n2)
            swap(n1, n2);
        _parent[n2] = n1;
        return n1;
    }
};

#endif