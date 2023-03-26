#include <gtest/gtest.h>
#include <Graph.h>

TEST(GRAPH, minScore)
{
    vector<vector<int>> nums{{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
    ASSERT_EQ(minScore(4, nums), 5);
    nums = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
    ASSERT_EQ(minScore(4, nums), 2);
    nums = {{1, 3, 1484}, {3, 2, 3876}, {2, 4, 6823}, {6, 7, 579}, {5, 6, 4436}, {4, 5, 8830}};
    ASSERT_EQ(minScore(7, nums), 579);
}

TEST(GRAPH, makeConnected)
{
    vector<vector<int>> nums{{0, 1}, {0, 2}, {1, 2}};
    ASSERT_EQ(makeConnected(4, nums), 1);
    nums = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
    ASSERT_EQ(makeConnected(6, nums), 2);
    nums = {{0, 1}, {0, 2}, {0, 3}, {1, 2}};
    ASSERT_EQ(makeConnected(6, nums), -1);
}

TEST(GRAPH, countPairs)
{
    vector<vector<int>> nums{{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}};
    ASSERT_EQ(countPairs(7, nums), 14);
    // nums = {{0,1},{0,2},{0,3},{1,2},{1,3}};
    // ASSERT_EQ(makeConnected(6, nums), 2);
    // nums = {{0,1},{0,2},{0,3},{1,2}};
    // ASSERT_EQ(makeConnected(6, nums), -1);
}

TEST(GRAPH, longestCycle)
{
    vector<int32_t> edges{3, 3, 4, 2, 3};
    ASSERT_EQ(longestCycle(edges), 3);
    edges = {2, -1, 3, 1};
    ASSERT_EQ(longestCycle(edges), -1);
    edges = {3, 4, 0, 2, -1, 2};
    ASSERT_EQ(longestCycle(edges), 3);
    edges = {1, 2, 0, 4, 5, 6, 3, 8, 9, 7};
    ASSERT_EQ(longestCycle(edges), 4);
}

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
TEST(GRAPH, PermuteUnique)
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