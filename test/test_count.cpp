#include <gtest/gtest.h>
#include <Count.h>

TEST(MATH, TEST2)
{
    std::vector<int> nums{1,3,0,0,2,0,0,4};
    ASSERT_EQ(zeroFilledSubarray(nums), 6);
    nums = {0,0,0,2,0,0};
    ASSERT_EQ(zeroFilledSubarray(nums), 9);
}