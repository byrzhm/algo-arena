#include <benchmark/benchmark.h>
#include <cstddef>
#include <random>
#include <sstream>

std::mt19937 rng{std::random_device{}()};

static std::string get_random_str(size_t size)
{
  std::string str;
  for (size_t i = 0; i < size; ++i) {
    str += static_cast<char>(rng() & 0xff);
  }
  return str;
}

static std::string get_random_str_by_stream(size_t size)
{
  std::stringstream sstream;
  for (size_t i = 0; i < size; ++i) {
    sstream << static_cast<char>(rng() & 0xff);
  }
  return sstream.str();
}

static void CreateString(benchmark::State &state)
{
  size_t size = state.range();
  for (auto _ : state) {
    std::string str = get_random_str(size);
    benchmark::DoNotOptimize(str);
  }
}

static void CreateStringByStream(benchmark::State &state)
{
  size_t size = state.range();
  for (auto _ : state) {
    std::string str = get_random_str_by_stream(size);
    benchmark::DoNotOptimize(str);
  }
}

static void ReverseStringByAdd(benchmark::State &state)
{
  size_t size     = state.range();
  std::string str = get_random_str(size);

  for (auto _ : state) {
    std::string reverse;
    for (auto iter = str.rbegin(); iter != str.rend(); ++iter) {
      reverse += *iter;
    }
    benchmark::DoNotOptimize(reverse);
  }
}

static void ReverseStringByStream(benchmark::State &state)
{
  size_t size     = state.range();
  std::string str = get_random_str(size);

  for (auto _ : state) {
    std::string reverse;
    std::stringstream sstream;
    for (auto iter = str.rbegin(); iter != str.rend(); ++iter) {
      sstream << *iter;
    }
    reverse = sstream.str();
    benchmark::DoNotOptimize(reverse);
  }
}


BENCHMARK(CreateString)->Range(8, 2 << 10);
BENCHMARK(CreateStringByStream)->Range(8, 2 << 10);
BENCHMARK(ReverseStringByAdd)->Range(8, 2 << 10);
BENCHMARK(ReverseStringByStream)->Range(8, 2 << 10);

BENCHMARK_MAIN();