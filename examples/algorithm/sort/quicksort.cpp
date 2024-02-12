#include <benchmark/benchmark.h>
#include <bits/stdc++.h>

static std::vector<int> genNonRepeatVec(int size)
{
  std::vector<int> vec(size);
  for (int i = 0; i < size; ++i) {
    vec[i] = i;
  }
  std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
  return vec;
}

static std::vector<int> genRepeatVec(int size)
{
  std::vector<int> vec(size, 666);
  vec.front() = 1;
  vec.back()  = 1024;
  return vec;
}

namespace hoare {

template<typename T>
int partition(std::vector<T> &a, int lo, int hi)
{
  int i = lo - 1;
  int j = hi + 1;
  T v   = a[(lo + hi) >> 1];

  while (i < j) {
    while (a[++i] < v)
      ;
    while (a[--j] > v)
      ;
    if (i < j)
      std::swap(a[i], a[j]);
  }
  return j;
}

template<typename T>
int randomized_partition(std::vector<T> &a, int lo, int hi)
{
  static std::mt19937 rng = std::mt19937{std::random_device{}()};
  int rand                = rng() % (hi - lo + 1) + lo;
  std::swap(a[rand], a[(lo + hi) >> 1]);
  return partition(a, lo, hi);
}

template<typename T>
void quicksort(std::vector<T> &a, int lo, int hi)
{
  if (hi <= lo)
    return;
  int pos = randomized_partition(a, lo, hi);

  quicksort(a, lo, pos - 1);
  quicksort(a, pos + 1, hi);
}

}  // namespace hoare

namespace two_way {

template<typename T>
int partition(std::vector<T> &a, int lo, int hi)
{
  int idx = lo;
  for (int i = lo + 1; i <= hi; ++i) {
    if (a[i] <= a[lo]) {
      std::swap(a[++idx], a[i]);
    }
  }
  std::swap(a[idx], a[lo]);
  return idx;
}

template<typename T>
int randomized_partition(std::vector<T> &a, int lo, int hi)
{
  static std::mt19937 rng = std::mt19937{std::random_device{}()};
  int rand                = rng() % (hi - lo + 1) + lo;
  std::swap(a[rand], a[lo]);
  return partition(a, lo, hi);
}

template<typename T>
void quicksort(std::vector<T> &a, int lo, int hi)
{
  if (hi <= lo)
    return;
  int pos = randomized_partition(a, lo, hi);

  quicksort(a, lo, pos - 1);
  quicksort(a, pos + 1, hi);
}

}  // namespace two_way

namespace three_way {

template<typename T>
std::pair<int, int> partition(std::vector<T> &a, int lo, int hi)
{
  T v    = a[lo];
  int lt = lo, gt = hi;
  int i = lo;
  while (i <= gt) {
    if (a[i] < v) {
      std::swap(a[lt++], a[i++]);
    } else if (a[i] > v) {
      std::swap(a[gt--], a[i]);
    } else {
      ++i;
    }
  }

  return {lt, gt};
}

template<typename T>
std::pair<int, int> randomized_partition(std::vector<T> &a, int lo, int hi)
{
  static std::mt19937 rng = std::mt19937{std::random_device{}()};
  int rand                = rng() % (hi - lo + 1) + lo;
  std::swap(a[rand], a[lo]);
  return partition(a, lo, hi);
}

template<typename T>
void quicksort(std::vector<T> &a, int lo, int hi)
{
  if (hi <= lo)
    return;
  auto [lt, gt] = randomized_partition(a, lo, hi);

  quicksort(a, lo, lt - 1);
  quicksort(a, gt + 1, hi);
}

}  // namespace three_way

//****************************************************************
//******                      对照组                         ******
//****************************************************************

static void benchmarkGenNonRepeatVec(benchmark::State &state)
{
  for (auto _ : state) {
    std::vector<int> randVec = genNonRepeatVec(state.range());
    benchmark::DoNotOptimize(randVec);
  }
}
BENCHMARK(benchmarkGenNonRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkGenNonRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkGenNonRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkGenNonRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkGenNonRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkGenNonRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkGenNonRepeatVec)->Arg(1'000'000);

static void benchmarkGenRepeatVec(benchmark::State &state)
{
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(state.range());
    benchmark::DoNotOptimize(randVec);
  }
}
BENCHMARK(benchmarkGenRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkGenRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkGenRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkGenRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkGenRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkGenRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkGenRepeatVec)->Arg(1'000'000);

//****************************************************************
//******                使用 hoare partition                 ******
//****************************************************************

static void benchmarkHoareNonRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genNonRepeatVec(size);
    hoare::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkHoareNonRepeatVec)->Arg(1'000'000);

static void benchmarkHoareRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(size);
    two_way::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkHoareRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkHoareRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkHoareRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkHoareRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkHoareRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkHoareRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkHoareRepeatVec)->Arg(1'000'000);  // 太慢了

//****************************************************************
//******                   常规二路快排                       ******
//****************************************************************

static void benchmarkTwoWayQuicksortNonRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genNonRepeatVec(size);
    two_way::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkTwoWayQuicksortNonRepeatVec)->Arg(1'000'000);

static void benchmarkTwoWayQuicksortRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(size);
    two_way::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkTwoWayQuicksortRepeatVec)->Arg(1'000'000); // 太慢了



//****************************************************************
//******                    三路快排                         ******
//****************************************************************

static void benchmarkThreeWayQuicksortNonRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genNonRepeatVec(size);
    three_way::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkThreeWayQuicksortNonRepeatVec)->Arg(1'000'000);

static void benchmarkThreeWayQuicksortRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(size);
    three_way::quicksort(randVec, 0, size - 1);
  }
}
BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkThreeWayQuicksortRepeatVec)->Arg(1'000'000);

static void benchmarkStdSortNonRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(size);
    std::sort(randVec.begin(), randVec.end());
  }
}
BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkStdSortNonRepeatVec)->Arg(1'000'000);

static void benchmarkStdSortRepeatVec(benchmark::State &state)
{
  int size = state.range();
  for (auto _ : state) {
    std::vector<int> randVec = genRepeatVec(size);
    std::sort(randVec.begin(), randVec.end());
  }
}
BENCHMARK(benchmarkStdSortRepeatVec)->Arg(1'000);
BENCHMARK(benchmarkStdSortRepeatVec)->Arg(2'000);
BENCHMARK(benchmarkStdSortRepeatVec)->Arg(4'000);
BENCHMARK(benchmarkStdSortRepeatVec)->Arg(8'000);
// BENCHMARK(benchmarkStdSortRepeatVec)->Arg(10'000);
// BENCHMARK(benchmarkStdSortRepeatVec)->Arg(100'000);
// BENCHMARK(benchmarkStdSortRepeatVec)->Arg(1'000'000);



BENCHMARK_MAIN();