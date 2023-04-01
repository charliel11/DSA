#ifndef __PARSE_H__
#define __PARSE_H__

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

static const std::string DATAPATH = "D:/project/DSA/test/data/";
static const std::string EXT = ".txt";

using VIntInt = tuple<vector<int32_t>, int32_t>;
using VVIntInt = tuple<vector<vector<int32_t>>, int32_t>;
using VIntIntInt = tuple<vector<int32_t>, int32_t, int32_t>;
using IntVVIntInt = tuple<int32_t, vector<vector<int32_t>>, int32_t>;
using StrStrBool = tuple<string, string, bool>;
using VStrIntInt = tuple<vector<string>, int32_t, int32_t>;

void parse(std::string &data_text, std::vector<VIntInt> &res);
void parse(std::string &data_text, std::vector<VVIntInt> &res);
void parse(std::string &data_text, std::vector<VIntIntInt> &res);
void parse(std::string &data_text, std::vector<StrStrBool> &res);
void parse(std::string &data_text, std::vector<VStrIntInt> &res);
void parse(std::string &data_text, std::vector<IntVVIntInt> &res);
std::string readtxt(std::string path);

#endif