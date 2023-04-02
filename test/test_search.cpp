#include "parse.h"
#include <BinarySearch.h>

TEST(BINARYSEARCH, search)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntIntInt> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(search(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(BINARYSEARCH, successfulPairs)
{
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntVIntIntVInt> cases;
    parse(data_text, cases);
    for (auto& c : cases)
    {
        ASSERT_EQ(successfulPairs(get<0>(c), get<1>(c), get<2>(c)), get<3>(c));
    }
}