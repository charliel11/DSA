#include "parse.h"
#include <Graph.h>

TEST(GRAPH, minScore)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<IntVVIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases)
    {
        ASSERT_EQ(minScore(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, makeConnected)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<IntVVIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases)
    {
        ASSERT_EQ(makeConnected(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, countPairs)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<IntVVIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases)
    {
        ASSERT_EQ(countPairs(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(GRAPH, longestCycle)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases)
    {
        ASSERT_EQ(longestCycle(get<0>(c)), get<1>(c));
    }
}