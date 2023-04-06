#pragma once

#include <algorithm>
#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

static const std::string DATAPATH = "D:/0plusz/DSA/test/data/";
static const std::string EXT = ".txt";

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

template <typename T> vector<T> parse(std::string &data_text, T para) {
    stringstream ss(data_text);
    constexpr size_t n = std::tuple_size<T>{};
    vector<T> res;
    while (ss) {
        res.push_back({});
        for (size_t i = 0; i < n; ++i) {
            string s;
            getline(ss, s);
            read(s, get<i>(res.back()));
        }
    }
    return res;
}

template <typename Sig> struct signature;

template <typename R, typename... Args> struct signature<R(Args...)> {
    using type = std::tuple<decay<Args...>>;
};

template <typename F> auto arguments(const F &) -> typename signature<F>::type;

std::string readtxt(std::string path);
