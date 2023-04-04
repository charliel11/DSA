#include <parse.h>
#include <DP.h>

TEST(DP, minCost) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(minCost(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, minPathSum) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VVIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(minPathSum(get<0>(c)), get<1>(c));
    }
}

TEST(DP, isScramble) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<StrStrBool> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(isScramble(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(DP, ways) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VStrIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(ways(get<0>(c), get<1>(c)), get<2>(c));
    }
}