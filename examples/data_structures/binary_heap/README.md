## Python

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


## C++

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

## Java

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

## Rust

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
