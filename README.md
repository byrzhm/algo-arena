<div align="center">

# Algorithm Arena
<figure>
        <img src="algo-arena.webp" alt="missing image" style="width: 300px; height: auto;">
        <figcaption></figcaption>
    </figure>
</div>

Problem prefix stands for
- lc - [leetcode](https://leetcode.cn/)
- cf - [codeforces](https://codeforces.com/)
- po - [poj](https://poj.org/)
- pt - [pta](https://pintia.cn/home)
- hd - [hdu](https://acm.hdu.edu.cn/)
- lg - [luogu](https://www.luogu.com.cn/)
- uv - [uva](https://onlinejudge.org/)

Most of the problems come from the book [Yongjun Luo & Weibin Guo](http://www.tup.tsinghua.edu.cn/Wap/tsxqy.aspx?id=08808001).


## FAQs & Tips

- If you'd like to use `algs4.jar` in vscode, all you need to do is create a `lib` folder at the root of your workspace and move the `algs4.jar` file into it.

- How to disable black formatter for specific block of code? <br>
    Using `# fmt: off` and `# fmt: on`, more on [black documentation](https://black.readthedocs.io/en/stable/usage_and_configuration/the_basics.html).

- How to disable clang-format for specific block of code? <br>
    Using `// clang-format off` and `// clang-format on`, more on [clang-format documentation](https://clang.llvm.org/docs/ClangFormatStyleOptions.html#disabling-formatting-on-a-piece-of-code).

- Quickly search problems <br>
    ```bash
    find . -type f -name 'lc_307*'
    ```

- Heap or priority queue in different languages: <br>
    - Python: <br>
    Python's built-in `heapq` module implements a **min-heap** by default.
    ```python
    import heapq

    # Create a heap
    heap = []

    # Add elements to the heap
    heapq.heappush(heap, 3)
    heapq.heappush(heap, 1)
    heapq.heappush(heap, 5)
    heapq.heappush(heap, 2)

    # The smallest element is always at the root
    print(heap)  # Output: [1, 2, 5, 3]

    # Remove the smallest element
    smallest = heapq.heappop(heap)
    print(smallest)  # Output: 1
    print(heap)      # Output: [2, 3, 5]
    ```
    > [!TIP]
    > **If You Need a Max-Heap**:
    >
    > You can simulate a max-heap by storing the negative of the elements:
    > ```python
    > heapq.heappush(heap, -value)
    > # To retrieve the original value, use -heapq.heappop(heap).
    > ```
    </details>
    - C++: <br>
    The C++ Standard Library provides the `std::priority_queue` class, which is a max-heap by default.

    ```c++
    #include <iostream>
    #include <queue>

    int main() {
        std::priority_queue<int> maxHeap;
        maxHeap.push(3);
        maxHeap.push(1);
        maxHeap.push(5);
        maxHeap.push(2);

        std::cout << maxHeap.top() << std::endl;  // Output: 5
        maxHeap.pop();
        std::cout << maxHeap.top() << std::endl;  // Output: 3

        return 0;
    }
    ```
    > [!TIP]
    > **To Create a Min-Heap**:
    >
    > Use `std::priority_queue` with a custom comparator or `std::greater`:
    > ```c++
    > std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    > ```
    - Rust: <br>
    Rust provides the BinaryHeap collection in the std::collections module, which is a max-heap by default.
    ```rust
    use std::collections::BinaryHeap;

    fn main() {
        let mut max_heap = BinaryHeap::new();
        max_heap.push(3);
        max_heap.push(1);
        max_heap.push(5);
        max_heap.push(2);

        println!("{:?}", max_heap.peek()); // Output: Some(5)
    }
    ```
    > [!TIP]
    > **To Create a Min-Heap**:
    >
    > Store negative values or use `Reverse` from the `std::cmp` module:
    > ```rust
    > use std::collections::BinaryHeap;
    > use std::cmp::Reverse;
    > 
    > fn main() {
    >     let mut min_heap = BinaryHeap::new();
    >     min_heap.push(Reverse(3));
    >     min_heap.push(Reverse(1));
    >     min_heap.push(Reverse(5));
    >     min_heap.push(Reverse(2));
    > 
    >     println!("{:?}", min_heap.peek()); // Output: Some(Reverse(1))
    > }
    > ```
    - Java: <br>
    Java provides the `PriorityQueue` class, which is a min-heap by default.
    ```java
    import java.util.PriorityQueue;

    public class Main {
        public static void main(String[] args) {
            PriorityQueue<Integer> minHeap = new PriorityQueue<>();
            minHeap.add(3);
            minHeap.add(1);
            minHeap.add(5);
            minHeap.add(2);

            System.out.println(minHeap.peek()); // Output: 1
        }
    }
    ```
    > [!TIP]
    > **To Create a Max-Heap**:
    > 
    > Use a custom comparator:
    > ```java
    > PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);
    > ```