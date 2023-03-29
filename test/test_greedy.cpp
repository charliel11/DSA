#include <gtest/gtest.h>
#include <Greedy.h>

#include "parse.h"

TEST(GREEDY, maxSatisfaction)
{
    std::string data_text{
R"([-1,-8,0,5,-7]
14
[4,3,2]
20
[-1,-4,-5]
0
[-1,-1,0,5,-1]
19
[-1]
0
[4]
4
)"};

    vector<VecAns> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(maxSatisfaction(get<0>(c)), get<1>(c));
    }
}