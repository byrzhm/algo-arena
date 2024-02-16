#include <algorithm>
#include <benchmark/benchmark.h>
#include <map>
#include <random>
#include <vector>

#include "bst.hpp"
#include "rbtree.hpp"

std::vector<int> getSortedVec(int size)
{
  std::vector<int> vec(size);
  for (int i = 0; i < size; ++i) {
    vec[i] = size;
  }
  return vec;
}

std::vector<int> getRandomVec(int size)
{
  std::vector<int> vec = getSortedVec(size);
  std::shuffle(vec.begin(), vec.end(), std::mt19937(std::random_device()()));
  return vec;
}

std::string random_string(std::size_t length)
{
  const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

  std::string random_string;

  for (std::size_t i = 0; i < length; ++i)
  {
    random_string += CHARACTERS[distribution(generator)];
  }

  return random_string;
}

std::vector<std::string> getSortedStringVec(int size)
{
  std::vector<std::string> strVec(size);
  for (int i = 0; i < size; ++i) {
    strVec[i] = random_string(66);
  }
  std::sort(strVec.begin(), strVec.end());
  return strVec;
}

std::vector<std::string> getRandomStringVec(int size)
{
  std::vector<std::string> strVec(size);
  for (int i = 0; i < size; ++i) {
    strVec[i] = random_string(66);
  }
  return strVec;
}

static void BM_BSTPutSorted(benchmark::State &state)
{
  auto vec = getSortedVec(state.range());
  for (auto _ : state) {
    BST<int, int> tree;
    for (auto num : vec) {
      tree.put(num, num);
    }
  }
}

static void BM_BSTPutRandom(benchmark::State &state)
{
  auto vec = getRandomVec(state.range());
  for (auto _ : state) {
    BST<int, int> tree;
    for (auto num : vec) {
      tree.put(num, num);
    }
  }
}

static void BM_BSTGetSorted(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedVec(size);
  BST<int, int> tree;
  for (auto &num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

static void BM_BSTGetRandom(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomVec(size);
  BST<int, int> tree;
  for (auto &num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

BENCHMARK(BM_BSTPutSorted)->Range(8, 8 << 18);
BENCHMARK(BM_BSTPutRandom)->Range(8, 8 << 18);
BENCHMARK(BM_BSTGetSorted)->Range(8, 8 << 18);
BENCHMARK(BM_BSTGetRandom)->Range(8, 8 << 18);


static void BM_RBTreePutSorted(benchmark::State &state)
{
  auto vec = getSortedVec(state.range());
  for (auto _ : state) {
    RBTree<int, int> tree;
    for (auto num : vec) {
      tree.put(num, num);
    }
  }
}

static void BM_RBTreePutRandom(benchmark::State &state)
{
  auto vec = getRandomVec(state.range());
  for (auto _ : state) {
    RBTree<int, int> tree;
    for (auto num : vec) {
      tree.put(num, num);
    }
  }
}

static void BM_RBTreeGetSorted(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedVec(size);
  RBTree<int, int> tree;
  for (auto &num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

static void BM_RBTreeGetRandom(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomVec(size);
  RBTree<int, int> tree;
  for (auto &num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

BENCHMARK(BM_RBTreePutSorted)->Range(8, 8 << 18);
BENCHMARK(BM_RBTreePutRandom)->Range(8, 8 << 18);
BENCHMARK(BM_RBTreeGetSorted)->Range(8, 8 << 18);
BENCHMARK(BM_RBTreeGetRandom)->Range(8, 8 << 18);


static void BM_STLMapPutSorted(benchmark::State &state)
{
  auto vec = getSortedVec(state.range());
  for (auto _ : state) {
    std::map<int, int> tree;
    for (auto num : vec) {
      tree.emplace(num, num);
    }
  }
}

static void BM_STLMapPutRandom(benchmark::State &state)
{
  auto vec = getRandomVec(state.range());
  for (auto _ : state) {
    std::map<int, int> tree;
    for (auto num : vec) {
      tree.emplace(num, num);
    }
  }
}

static void BM_STLMapGetSorted(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedVec(size);
  std::map<int, int> tree;
  for (auto &num : vec) {
    tree.emplace(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree[random_key]);
  }
}

static void BM_STLMapGetRandom(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomVec(size);
  std::map<int, int> tree;
  for (auto &num : vec) {
    tree.emplace(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree[random_key]);
  }
}

BENCHMARK(BM_STLMapPutSorted)->Range(8, 8 << 18);
BENCHMARK(BM_STLMapPutRandom)->Range(8, 8 << 18);
BENCHMARK(BM_STLMapGetSorted)->Range(8, 8 << 18);
BENCHMARK(BM_STLMapGetRandom)->Range(8, 8 << 18);

/**
 *=================================================================
 *====================== string as key ============================
 *=================================================================
 */

static void BM_BSTPutSortedString(benchmark::State &state)
{
  auto vec = getSortedStringVec(state.range());
  for (auto _ : state) {
    BST<std::string, int> tree;
    for (const auto &str : vec) {
      tree.put(str, 1);
    }
  }
}

static void BM_BSTPutRandomString(benchmark::State &state)
{
  auto vec = getRandomStringVec(state.range());
  for (auto _ : state) {
    BST<std::string, int> tree;
    for (const auto &str : vec) {
      tree.put(str, 1);
    }
  }
}

static void BM_BSTGetSortedString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedStringVec(size);
  BST<std::string, int> tree;
  for (auto &str : vec) {
    tree.put(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

static void BM_BSTGetRandomString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomStringVec(size);
  BST<std::string, int> tree;
  for (auto &str : vec) {
    tree.put(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

BENCHMARK(BM_BSTPutSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_BSTPutRandomString)->Range(8, 8 << 12);
BENCHMARK(BM_BSTGetSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_BSTGetRandomString)->Range(8, 8 << 12);

static void BM_RBTreePutSortedString(benchmark::State &state)
{
  auto vec = getSortedStringVec(state.range());
  for (auto _ : state) {
    RBTree<std::string, int> tree;
    for (const auto &str : vec) {
      tree.put(str, 1);
    }
  }
}

static void BM_RBTreePutRandomString(benchmark::State &state)
{
  auto vec = getRandomStringVec(state.range());
  for (auto _ : state) {
    RBTree<std::string, int> tree;
    for (const auto &str : vec) {
      tree.put(str, 1);
    }
  }
}

static void BM_RBTreeGetSortedString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedStringVec(size);
  RBTree<std::string, int> tree;
  for (auto &str : vec) {
    tree.put(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

static void BM_RBTreeGetRandomString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomStringVec(size);
  RBTree<std::string, int> tree;
  for (auto &str : vec) {
    tree.put(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

BENCHMARK(BM_RBTreePutSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_RBTreePutRandomString)->Range(8, 8 << 12);
BENCHMARK(BM_RBTreeGetSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_RBTreeGetRandomString)->Range(8, 8 << 12);


static void BM_STLMapPutSortedString(benchmark::State &state)
{
  auto vec = getSortedStringVec(state.range());
  for (auto _ : state) {
    std::map<std::string, int> tree;
    for (const auto &str : vec) {
      tree.emplace(str, 1);
    }
  }
}

static void BM_STLMapPutRandomString(benchmark::State &state)
{
  auto vec = getRandomStringVec(state.range());
  for (auto _ : state) {
    std::map<std::string, int> tree;
    for (const auto &str : vec) {
      tree.emplace(str, 1);
    }
  }
}

static void BM_STLMapGetSortedString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getSortedStringVec(size);
  std::map<std::string, int> tree;
  for (auto &str : vec) {
    tree.emplace(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree[random_key]);
  }
}

static void BM_STLMapGetRandomString(benchmark::State &state)
{
  int size = state.range();
  auto vec = getRandomStringVec(size);
  std::map<std::string, int> tree;
  for (auto &str : vec) {
    tree.emplace(str, 1);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    auto &random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree[random_key]);
  }
}

BENCHMARK(BM_STLMapPutSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_STLMapPutRandomString)->Range(8, 8 << 12);
BENCHMARK(BM_STLMapGetSortedString)->Range(8, 8 << 12);
BENCHMARK(BM_STLMapGetRandomString)->Range(8, 8 << 12);

BENCHMARK_MAIN();