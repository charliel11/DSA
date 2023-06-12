#include <DSA/Design.h>
#include <config.h>

TEST(DESIGN, SnapshotArray) {
  SnapshotArray s(1);
  ASSERT_EQ(s.snap(), 0);
  ASSERT_EQ(s.snap(), 1);
  s.set(0, 4);
  ASSERT_EQ(s.snap(), 2);
  ASSERT_EQ(s.get(0, 1), 0);
  s.set(0, 12);
  ASSERT_EQ(s.get(0, 1), 0);
  ASSERT_EQ(s.snap(), 3);
  ASSERT_EQ(s.get(0, 3), 12);
}