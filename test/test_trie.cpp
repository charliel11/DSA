#include <gtest/gtest.h>
#include <Trie.h>

TEST(TRIE, TEST1)
{
    Trie trie;
    trie.insert("apple");
    ASSERT_EQ(trie.startsWith("app"), true);
}

TEST(TESTNAME, TEST1)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
