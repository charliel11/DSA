#include <gtest/gtest.h>
#include <DP.h>

using VecIntAns = tuple<vector<int32_t>, int64_t, int32_t>;
// #include "parse.h"

void parse(std::string& data_text, std::vector<VecIntAns>& res)
{
    replace(data_text.begin(), data_text.end(), ',', ' ');
    stringstream ss1(data_text), ss2;
    string s;
    string v;
    string a;
    while (getline(ss1, s))
    {
        getline(ss1, v);
        getline(ss1, a);
        res.push_back({vector<int>{}, stoi(v), stoi(a)});
        ss2.clear();
        s = s.substr(1, s.length() - 2);
        ss2 << s;
        while (ss2 >> s)
            get<0>(res.back()).push_back(stoi(s));
    }
}



TEST(DP, minCost)
{
    std::string data_text{
R"([1,2,1,2,1,3,3]
2
8
[1,2,1,2,1]
2
6
[1,2,1,2,1]
5
10
)"};

    vector<VecIntAns> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(minCost(get<0>(c), get<1>(c)), get<2>(c));
    }
}