import sys
import json
import matplotlib.pyplot as plt
import numpy as np

# 从 JSON 文件中读取基准测试结果
def read_benchmark_results(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)
    return data['benchmarks']

# 解析测试名称和数据规模
def parse_test_name(name):
    parts = name.split('/')
    test_name = parts[0]
    data_size = int(parts[1])
    return test_name, data_size

# 绘制基准测试结果的柱状图
def plot_benchmark_results(benchmarks):
    test_names = []
    data_sizes = []
    real_times = []

    for benchmark in benchmarks:
        name, data_size = parse_test_name(benchmark['name'])
        test_names.append(name)
        data_sizes.append(data_size)
        real_times.append(benchmark['real_time'])

    test_name_set = list(set(test_names))
    data_size_set = sorted(list(set(data_sizes)))
    test_names = np.array(test_names)
    real_times = np.array(real_times)

    x = np.arange(len(data_size_set))
    bar_width = 1 / (len(x) + 10)
    fig, ax = plt.subplots(layout='constrained')

    for i, test_name in enumerate(test_name_set):
        bars = ax.bar(
            x + i * bar_width,
            real_times[test_names == test_name],
            width=bar_width,
            label=test_name
        )
        ax.bar_label(bars, padding=3, rotation=90)

    ax.set_xlabel('data size')
    ax.set_ylabel('real time (ns)')
    ax.set_title('Benchmark Results')
    ax.set_xticks(x + bar_width, data_size_set)

    ax.legend(loc='upper left')
    # plt.show()
    fig.savefig('benchmark.png')


def main():
    if len(sys.argv) < 2:
        print(f'Usage: python3 {sys.argv[0]} <benchmark json filename>')
        exit(0)

    benchmark_file = sys.argv[1]

    benchmarks = read_benchmark_results(benchmark_file)
    plot_benchmark_results(benchmarks)

if __name__ == '__main__':
    main()
