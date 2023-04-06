#include <Graph.h>
#include <parse.h>

TEST(GRAPH, minScore) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(minScore));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(minScore(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, makeConnected) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(makeConnected));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(makeConnected(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, countPairs) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(countPairs));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(countPairs(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, longestCycle) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(longestCycle));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(longestCycle(get<0>(c)), get<1>(c));
    }
}

TEST(GRAPH, closedIsland) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(closedIsland));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(closedIsland(get<0>(c)), get<1>(c));
    }
}