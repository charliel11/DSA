#include <gtest/gtest.h>
#include <Backtracking.h>

void test_2dVector(const vector<vector<int>> &vec, const vector<vector<int>> &expected_vec)
{
    int expected_len = vec.size();
    ASSERT_EQ(expected_len, expected_vec.size());
    vector<int> exists(expected_len, 0);
    for (size_t i = 0; i < expected_len; ++i)
    {
        for (size_t j = 0; j < expected_len; ++j)
        {
            if (vec[i] == expected_vec[i])
            {
                exists[i] = 1;
                break;
            }
        }
    }

    int sum_exists = accumulate(exists.begin(), exists.end(), 0);
    EXPECT_EQ(sum_exists, expected_len);
}
TEST(BACKTRACKING, PermuteUnique)
{
    vector<int> nums = {1, 1, 2, 2};
    vector<vector<int>> expected_vec = {{1, 1, 2, 2}, {1, 2, 1, 2}, {1, 2, 2, 1}, {2, 1, 1, 2}, {2, 1, 2, 1}, {2, 2, 1, 1}};
    vector<vector<int>> vec = PermuteUnique(nums);
    test_2dVector(vec, expected_vec);

    nums = {1, 2, 3};
    expected_vec = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 2, 1}, {3, 1, 2}};
    vec = PermuteUnique(nums);
    test_2dVector(vec, expected_vec);

    nums = {1, 1, 2};
    expected_vec = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};
    vec = PermuteUnique(nums);
    test_2dVector(vec, expected_vec);
}