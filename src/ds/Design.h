#pragma once

#include <queue>
#include <set>
#include <string>
#include <vector>

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

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq;
    int _k;

  public:
    KthLargest(int k, vector<int> &nums) : pq(nums.begin(), nums.end()), _k(k) {
        while (pq.size() > k) {
            pq.pop();
        }
    };

    int add(int val) {
        pq.push(val);
        if (pq.size() > _k)
            pq.pop();
        return pq.top();
    }
};

class MyHashSet {
  public:
    MyHashSet() {}

    void add(int key) {}

    void remove(int key) {}

    bool contains(int key) {}
};

class UndergroundSystem {
  public:
    UndergroundSystem() {}

    void checkIn(int id, string stationName, int t) {}

    void checkOut(int id, string stationName, int t) {}

    double getAverageTime(string startStation, string endStation) {}
};
