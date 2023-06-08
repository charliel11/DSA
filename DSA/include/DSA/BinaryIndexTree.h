#pragma once

#include <vector>

class FenwickTree {
  std::vector<int> tree;
  static inline int lowbit(int x) { return x & (-x); }

public:
  FenwickTree(int n) : tree(n + 1, 0) {}

  // change idx i value
  void update(int i, int value) {
    while (i > 0 && i < tree.size()) {
      tree[i] += value;
      i += lowbit(i);
    }
  }
  // sum of range [0, i];
  int query(int i) const {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= lowbit(i);
    }
    return sum;
  }
};