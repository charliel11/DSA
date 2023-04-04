#include <parse.h>
#include <Count.h>

TEST(Count, zeroFilledSubarray) {
    std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string data_text = readtxt(DATAPATH + test_name + EXT);

    vector<VIntInt> cases;
    parse(data_text, cases);
    for (auto &c : cases) {
        ASSERT_EQ(zeroFilledSubarray(get<0>(c)), get<1>(c));
    }
}