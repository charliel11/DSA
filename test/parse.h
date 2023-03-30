#ifndef __PARSE_H__
#define __PARSE_H__

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

using VecInt = tuple<vector<int32_t>, int32_t>; 
using VVecInt = tuple<vector<vector<int32_t>>, int32_t>;
using VecIntInt = tuple<vector<int32_t>, int32_t, int32_t>;
using StrStrBool = tuple<string, string, bool>;

void parse(std::string& data_text, std::vector<VecInt>& res);
void parse(std::string& data_text, std::vector<VVecInt>& res);
void parse(std::string& data_text, std::vector<VecIntInt>& res);
void parse(std::string& data_text, std::vector<StrStrBool>& res);

#endif