#include <Graph.h>
#include <config.h>

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

TEST(GRAPH, numEnclaves) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(numEnclaves));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(numEnclaves(get<0>(c)), get<1>(c));
    }
}

TEST(GRAPH, canFinish) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(canFinish));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(canFinish(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, findOrder) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(findOrder));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(findOrder(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, largestPathValue) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(largestPathValue));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(largestPathValue(get<0>(c), get<1>(c)), get<2>(c));
    }
}