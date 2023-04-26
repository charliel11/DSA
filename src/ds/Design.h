#pragma once

#include <set>

using namespace std;

class SmallestInfiniteSet {
    int32_t cur;
    set<int32_t> s;

  public:
    SmallestInfiniteSet() : cur(1) {}

    int popSmallest() {
        if (s.empty())
            return cur++;
        else {
            int32_t res = *s.begin();
            s.erase(s.begin());
            return res;
        }
    }

    void addBack(int num) {
        if (num < cur) {
            s.insert(num);
        }
    }
};