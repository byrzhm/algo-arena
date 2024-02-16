#include "bst.hpp"
#include <gtest/gtest.h>

#include <random>

TEST(BSTTest, basic)
{
  BST<int, int> tree;

  // put
  tree.put(1, 10);
  tree.put(2, 20);

  // contains
  EXPECT_EQ(tree.contains(1), true);
  EXPECT_EQ(tree.contains(2), true);
  EXPECT_EQ(tree.contains(3), false);

  // get
  EXPECT_EQ(*tree.get(1), 10);
  EXPECT_EQ(*tree.get(2), 20);
  EXPECT_EQ(tree.get(3), nullptr);

  EXPECT_EQ(tree.size(), 2);

  // deleteMin/deleteMax
  tree.deleteMin();
  EXPECT_EQ(tree.get(1), nullptr);
  EXPECT_EQ(*tree.get(2), 20);
  EXPECT_EQ(tree.size(), 1);

  tree.deleteMax();
  EXPECT_EQ(tree.get(1), nullptr);
  EXPECT_EQ(tree.get(2), nullptr);
  EXPECT_EQ(tree.size(), 0);

  EXPECT_EQ(tree.isEmpty(), true);
}

TEST(BSTTest, randomPut)
{
  BST<int, int> tree;
  std::vector<int> input;
  input.reserve(10);
for (int i = 0; i < 10; ++i) {
    input.emplace_back(i);
  }

  std::shuffle(input.begin(), input.end(), std::mt19937(std::random_device()()));

  for (auto num : input) {
    tree.put(num, num);
  }

  EXPECT_EQ(tree.size(), 10);
  EXPECT_EQ(tree.min(), 0);
  EXPECT_EQ(tree.max(), 9);

  int num = 0;
  for (auto it = tree.iterator(); it.hasNext();) {
    auto val = *it.next();
    EXPECT_EQ(val, num++);
  }
}

TEST(BSTTest, shapeTest) {
  BST<int, int> tree;

  for (int i = 0; i < 100; ++i) {
    tree.put(i, i);
  }

  EXPECT_TRUE(tree.rightLinear());
}

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}