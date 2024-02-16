#include <algorithm>
#include <benchmark/benchmark.h>
#include <map>
#include <random>
#include <vector>

#include "bst.hpp"
#include "rbtree.hpp"

// TODO(zhm): benchmark rbtree

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
  std::vector<int> vec = getSortedVec(size);
  BST<int, int> tree;
  for (int num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    int random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

static void BM_BSTGetRandom(benchmark::State &state)
{
  int size = state.range();
  std::vector<int> vec = getRandomVec(size);
  BST<int, int> tree;
  for (int num : vec) {
    tree.put(num, num);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, size - 1);

  for (auto _ : state) {
    int random_key = vec[dis(gen)];
    benchmark::DoNotOptimize(tree.get(random_key));
  }
}

BENCHMARK(BM_BSTPutSorted)->Range(8, 8 << 18);
BENCHMARK(BM_BSTPutRandom)->Range(8, 8 << 18);
BENCHMARK(BM_BSTGetSorted)->Range(8, 8 << 18);
BENCHMARK(BM_BSTGetRandom)->Range(8, 8 << 18);

BENCHMARK_MAIN();