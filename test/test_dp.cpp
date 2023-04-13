#include <DP.h>
#include <config.h>

TEST(DP, minCost) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(minCost));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(minCost(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, minPathSum) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(minPathSum));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(minPathSum(get<0>(c)), get<1>(c));
    }
}

TEST(DP, isScramble) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(isScramble));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(isScramble(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, ways) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(ways));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(ways(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, coinChange) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(coinChange));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(coinChange(get<0>(c), get<1>(c)), get<2>(c));
    }
}