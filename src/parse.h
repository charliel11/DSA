#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

using VIntInt = tuple<vector<int32_t>, int32_t>;
using VIntVIntIntVInt = tuple<vector<int32_t>, vector<int32_t>, int64_t, vector<int32_t>>;
using VIntVIntIntInt = tuple<vector<int32_t>, vector<int32_t>, int64_t, int64_t>;
using VVIntInt = tuple<vector<vector<int32_t>>, int32_t>;
using VIntIntInt = tuple<vector<int32_t>, int32_t, int32_t>;
using IntVVIntInt = tuple<int32_t, vector<vector<int32_t>>, int32_t>;
using StrStrBool = tuple<string, string, bool>;
using StrInt = tuple<string, int32_t>;
using VStrIntInt = tuple<vector<string>, int32_t, int32_t>;

void parse(std::string &data_text, std::vector<VIntInt> &res);
void parse(std::string &data_text, std::vector<VVIntInt> &res);
void parse(std::string &data_text, std::vector<VIntIntInt> &res);
void parse(std::string &data_text, std::vector<StrStrBool> &res);
void parse(std::string &data_text, std::vector<StrInt> &res);
void parse(std::string &data_text, std::vector<VStrIntInt> &res);
void parse(std::string &data_text, std::vector<IntVVIntInt> &res);
void parse(std::string &data_text, std::vector<VIntVIntIntVInt> &res);
void parse(std::string &data_text, std::vector<VIntVIntIntInt> &res);

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
void read(string &text, string &res);
void read(string &text, int32_t &res);
void read(string &text, int64_t &res);
void read(string &text, bool &res);

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
