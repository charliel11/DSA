#include "parse.h"
#include <DP.h>

TEST(DP, minCost)
{
    std::string data_text{
R"([2,3,3,3,1,5,5,0,5,3,4,2,1,2,5,1,2,0]
5
21
[1,2,1,2,1,3,3]
2
8
[1,2,1,2,1]
2
6
[1,2,1,2,1]
5
10
)"};

    vector<VecIntInt> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(minCost(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, minPathSum)
{
    std::string data_text{
R"([[1,3,1],[1,5,1],[4,2,1]]
7
[[1,2,3],[4,5,6]]
12
)"};
    vector<VVecInt> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(minPathSum(get<0>(c)), get<1>(c));
    }
}

TEST(DP, isScramble)
{
    std::string data_text{
R"(great
rgeat
true
abcde
caebd
false
a
a
true
)"};
    vector<StrStrBool> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(isScramble(get<0>(c), get<1>(c)), get<2>(c));
    }
}