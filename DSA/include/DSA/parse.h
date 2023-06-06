#pragma once

#include <DSA/Node.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

/*
[1,2,3,4,5,6]
*/
void read(string &text, vector<int32_t> &res);
/*
[[1,2,3],[4,5,6]]
*/
void read(string &text, vector<vector<int32_t>> &res);
/*
["123", "345"]
*/
void read(string &text, vector<string> &res);
void read(string &text, vector<bool> &res);
void read(string &text, string &res);
void read(string &text, int32_t &res);
void read(string &text, int64_t &res);
void read(string &text, uint64_t &res);
void read(string &text, bool &res);

/*
[1,1,1,null,1,null,null,1,1,null,1]
*/
void read(string &text, TreeNode *&res);

void read(string &text, ListNode *&res);

template <typename T> void printElem(T &x, stringstream &ss) {
    string s;
    getline(ss, s);
    read(s, x);
};

template <typename TupleT, std::size_t... Is>
void printTupleManual(TupleT &tp, std::index_sequence<Is...>, stringstream &ss) {
    (printElem(std::get<Is>(tp), ss), ...);
};

template <typename T> vector<T> parse(std::string &data_text) {
    stringstream ss(data_text);
    vector<T> res;
    constexpr size_t n = tuple_size_v<T>;
    while (ss.peek() != -1) {
        res.push_back({});
        printTupleManual(res.back(), std::make_index_sequence<n>{}, ss);
    }
    return res;
};

template <typename Sig> struct signature;

template <typename R, typename... Args> struct signature<R(Args...)> {
    using type = std::tuple<decay_t<Args>..., decay_t<R>>;
};

template <typename F> auto arguments(const F &) -> typename signature<F>::type;

std::string readtxt(std::string path);
