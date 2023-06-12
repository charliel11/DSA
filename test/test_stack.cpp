#include <DSA/Stack.h>
#include <config.h>

TEST(STACK, simplifyPath) {
  using namespace st::pattern_matching;

  std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
  std::string data_text = readtxt(DATAPATH + test_name);

  using p = decltype(arguments(simplifyPath));
  auto cases = parse<p>(data_text);
  for (auto &c : cases) {
    ASSERT_EQ(simplifyPath(get<0>(c)), get<1>(c));
  }
}

TEST(STACK, removeStars) {
  using namespace st::pattern_matching;

  std::string test_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();
  std::string data_text = readtxt(DATAPATH + test_name);

  using p = decltype(arguments(removeStars));
  auto cases = parse<p>(data_text);
  for (auto &c : cases) {
    ASSERT_EQ(removeStars(get<0>(c)), get<1>(c));
  }
}