#include <gtest/gtest.h>
#include <Graph.h>

TEST(GRAPH, MINSCORE)
{
    vector<vector<int>> nums{{1,2,9},{2,3,6},{2,4,5},{1,4,7}};
    ASSERT_EQ(minScore(4, nums), 5);
    nums = {{1,2,2},{1,3,4},{3,4,7}};
    ASSERT_EQ(minScore(4, nums), 2);
}