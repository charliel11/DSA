#include <BinarySearch.h>
#include <parse.h>

TEST(BINARYSEARCH, search) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(bs::search));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(bs::search(get<0>(c), get<1>(c)), get<2>(c));
    }
}

TEST(BINARYSEARCH, successfulPairs) {
    using namespace bs;
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(successfulPairs));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(successfulPairs(get<0>(c), get<1>(c), get<2>(c)), get<3>(c));
    }
}