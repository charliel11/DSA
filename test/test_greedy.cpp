#include <Greedy.h>
#include <parse.h>

TEST(GREEDY, maxSatisfaction) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(maxSatisfaction(get<0>(c)), get<1>(c));
    }
}

TEST(GREEDY, numRescueBoats) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(numRescueBoats(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GREEDY, minimizeArrayValue) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(minimizeArrayValue(get<0>(c)), get<1>(c));
    }
}

TEST(GREEDY, miceAndCheese) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntVIntIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(miceAndCheese(get<0>(c), get<1>(c), get<2>(c)), get<3>(c));
    }
}
