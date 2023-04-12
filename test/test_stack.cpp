#include <Stack.h>
#include <config.h>

TEST(Stack, simplifyPath) {
    using namespace st::pattern_matching;

    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(simplifyPath));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(simplifyPath(get<0>(c)), get<1>(c));
    }
}

TEST(Stack, removeStars) {
    using namespace st::pattern_matching;

    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    using p = decltype(arguments(removeStars));
    auto cases = parse<p>(data_text);
    for (auto &c : cases) {
        ASSERT_EQ(removeStars(get<0>(c)), get<1>(c));
    }
}