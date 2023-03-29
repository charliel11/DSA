#ifndef __PARSE_H__
#define __PARSE_H__

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

using VecAns = tuple<vector<int32_t>, int32_t>; 
using Vec2Ans = tuple<vector<vector<int32_t>>, int32_t>;
using VecIntAns = tuple<vector<int32_t>, int32_t, int32_t>;

void parse(std::string& data_text, std::vector<VecAns>& res);
void parse(std::string& data_text, std::vector<Vec2Ans>& res);
void parse(std::string& data_text, std::vector<VecIntAns>& res);

#endif