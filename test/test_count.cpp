#include <Count.h>
#include <parse.h>

TEST(Count, zeroFilledSubarray) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(zeroFilledSubarray));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(zeroFilledSubarray(get<0>(c)), get<1>(c));
    }
}

TEST(Count, findTheLongestBalancedSubstring) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(findTheLongestBalancedSubstring));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(findTheLongestBalancedSubstring(get<0>(c)), get<1>(c));
    }
}