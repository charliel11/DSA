#pragma once

#include <DSA/Node.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

// using namespace std;

/*
[1,2,3,4,5,6]
*/
template <typename T> void parse_test_case(string &text, vector<T> &res) {
  stringstream ss;
  text = text.substr(1, text.length() - 2);
  ss << text;
  while (ss >> text) {
    if (std::is_same_v<T, int>)
      res.push_back(stoi(text));
    if (std::is_same_v<T, double>)
      res.push_back(stod(text));
  }
}

/*
[[1,2,3],[4,5,6]]
*/
void parse_test_case(string &text, vector<vector<int32_t>> &res);
/*
["123", "345"]
*/
void parse_test_case(string &text, vector<string> &res);
void parse_test_case(string &text, vector<bool> &res);
void parse_test_case(string &text, string &res);
void parse_test_case(string &text, bool &res);

template <typename T> void parse_test_case(string &text, T &res) {
  if (std::is_same_v<T, int>)
    res = stoi(text);
  if (std::is_same_v<T, int64_t>)
    res = stoll(text);
  if (std::is_same_v<T, uint64_t>)
    res = stoull(text);
  if (std::is_same_v<T, double>)
    res = stod(text);
}

/*
[1,1,1,null,1,null,null,1,1,null,1]
*/
void parse_test_case(string &text, TreeNode *&res);

void parse_test_case(string &text, ListNode *&res);

template <typename T> void printElem(T &x, stringstream &ss) {
  string s;
  getline(ss, s);
  parse_test_case(s, x);
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
