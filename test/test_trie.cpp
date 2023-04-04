#include <gtest/gtest.h>
#include <Trie.h>

TEST(TRIE, insert) {
    Trie trie;
    trie.insert("apple");
    ASSERT_EQ(trie.startsWith("app"), true);
    ASSERT_EQ(1, 1);
}