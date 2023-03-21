#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <deque>
#include <numeric>
#include <string>
#include <array>
#include <cstring>
#include <iterator>
#include <cmath>
#include <bitset>
#include <thread>
#include <functional>
#include <list>
#include "assert.h"
#include <emmintrin.h>

#include <sstream>
#include <iostream>

using namespace std;

#define ll long long
#define ld long double
#define ar array
#define vt vector
#define EACH(x, a) for (auto &x : a)
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)

template <class T>
void read(T &x)
{
    cin >> x;
}
template <class H, class... T>
void read(H &h, T &...t)
{
    read(h);
    read(t...);
}
template <class A, size_t S>
void read(array<A, S> &x)
{
    EACH(a, x)
    read(a);
}
template <class A>
void read(vt<vt<A>> &v)
{
    string s;
    cin >> s;
    v.clear();
    replace(s.begin(), s.end(), ',', ' ');
    stringstream ss(s.substr(1, s.size() - 2));
    string word;
    while (ss >> word)
    {
        if (word == "[]")
        {
            v.push_back({});
        }
        else if (word[0] == '[')
        {
            v.push_back({});
            v.back().push_back(stoi(word.substr(1)));
        }
        else
            v.back().push_back(stoi(word));
    }
}
template <class A>
void read(vt<A> &v)
{
    string s;
    cin >> s;
    v.clear();
    replace(s.begin(), s.end(), ',', ' ');
    s = s.substr(1, s.length() - 2);
    stringstream ss(s);
    string word;
    while (ss >> word)
    {
        v.push_back(stoi(word));
    }
}

#pragma region print tool

template <typename T>
void print(T& arg)
{
    cout << arg << endl;
}
template <typename T>
void print(vector<T> &arg)
{
    for (T a : arg)
        std::cout << a << ',';
    std::cout << '\n';
}
template <typename T>
void print(vector<vector<T>> &arg)
{
    for (vector<T> &a : arg)
        for (T &b : a)
            std::cout << b << ',';
    std::cout << '\n';
    std::cout << '\n';
}
template <typename T>
void print(pair<T, T> &arg)
{
    std::cout << arg.first << ',' << arg.second << '\n';
}
template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    print(firstArg); // call print() for the first argument
    print(args...);  // call print() for remaining arguments
}

#pragma endregion

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#endif