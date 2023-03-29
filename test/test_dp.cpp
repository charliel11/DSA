#include <gtest/gtest.h>
#include <DP.h>

TEST(DP, minPathSum)
{
    vector<vector<int32_t>> nums={{1,3,1},{1,5,1},{4,2,1}};
    ASSERT_EQ(minPathSum(nums), 7);
}