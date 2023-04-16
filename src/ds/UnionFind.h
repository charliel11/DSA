#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include "Utility.h"

class UnionFind {
  public:
    vector<int32_t> _parent;
    UnionFind(int32_t n) : _parent(n) { iota(_parent.begin(), _parent.end(), 0); }
    void insert(int32_t child, int32_t parent) { _parent[child] = parent; }
    int32_t find_root(int32_t node) {
        while (_parent[node] != node)
            node = _parent[node];
        return node;
    }
    int32_t merge(int32_t node1, int32_t node2) {
        int32_t n1 = find_root(node1);
        int32_t n2 = find_root(node2);
        if (n1 > n2)
            swap(n1, n2);
        _parent[n2] = n1;
        return n1;
    }
};

#endif