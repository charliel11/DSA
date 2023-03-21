#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <Utility.h>

class UnionFind
{
    vector<int> ele;

public:
    UnionFind(int n) : ele(n)
    {
        iota(ele.begin(), ele.end(), 0);
    };
    void insert(int child, int parent)
    {
        ele[child] = parent;
    }
    int find_root(int child)
    {
        int cur = child;
        while (ele[cur] != cur)
            cur = ele[cur];
        return cur;
    }
};

#endif