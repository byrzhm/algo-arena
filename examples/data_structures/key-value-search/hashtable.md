## C++ (`unordered_map`)

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    // 创建哈希表
    std::unordered_map<std::string, int> scores;

    // 插入键值对
    scores["Alice"] = 90;
    scores.emplace("Bob", 85);
    scores.insert({"Charlie", 95});

    // 访问元素
    std::cout << "Alice's score: " << scores["Alice"] << std::endl;

    // 删除元素
    scores.erase("Bob");

    // 遍历哈希表
    for (const auto& pair : scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
```

## Java (`HashMap`)

```java
import java.util.HashMap;

public class Main {
    public static void main(String[] args) {
        // 创建哈希表
        HashMap<String, Integer> scores = new HashMap<>();

        // 插入键值对
        scores.put("Alice", 90);
        scores.put("Bob", 85);
        scores.put("Charlie", 95);

        // 访问元素
        System.out.println("Alice's score: " + scores.get("Alice"));

        // 删除元素
        scores.remove("Bob");

        // 遍历哈希表
        for (String key : scores.keySet()) {
            System.out.println(key + ": " + scores.get(key));
        }
    }
}
```

## Python (`dict`)

```python
# 创建字典
scores = {}

# 插入键值对
scores["Alice"] = 90
scores.update({"Bob": 85, "Charlie": 95})

# 访问元素
print("Alice's score:", scores["Alice"])

# 删除元素
del scores["Bob"]

# 遍历字典
for key, value in scores.items():
    print(f"{key}: {value}")
```

## Go (`map`)

```go
package main

import "fmt"

func main() {
    // 创建哈希表
    scores := make(map[string]int)

    // 插入键值对
    scores["Alice"] = 90
    scores["Bob"] = 85
    scores["Charlie"] = 95

    // 访问元素
    fmt.Println("Alice's score:", scores["Alice"])

    // 删除元素
    delete(scores, "Bob")

    // 遍历哈希表
    for key, value := range scores {
        fmt.Printf("%s: %d\n", key, value)
    }
}
```

## Rust (`std::collections::HashMap`)

```rust
use std::collections::HashMap;

fn main() {
    // 创建哈希表
    let mut scores = HashMap::new();

    // 插入键值对
    scores.insert("Alice", 90);
    scores.insert("Bob", 85);
    scores.insert("Charlie", 95);

    // 访问元素
    println!("Alice's score: {}", scores["Alice"]);

    // 删除元素
    scores.remove("Bob");

    // 遍历哈希表
    for (key, value) in &scores {
        println!("{}: {}", key, value);
    }
}
```

## JavaScript (`Map` 或 `Object`)

`Map` (Recommended):
```javascript
// 创建 Map
const scores = new Map();

// 插入键值对
scores.set("Alice", 90);
scores.set("Bob", 85);
scores.set("Charlie", 95);

// 访问元素
console.log("Alice's score:", scores.get("Alice"));

// 删除元素
scores.delete("Bob");

// 遍历 Map
scores.forEach((value, key) => {
    console.log(`${key}: ${value}`);
});
```

`Object`:
```javascript
// 创建对象
const scores = {};

// 插入键值对
scores["Alice"] = 90;
scores.Bob = 85;  // 等价于 scores["Bob"] = 85

// 访问元素
console.log("Alice's score:", scores["Alice"]);

// 删除元素
delete scores.Bob;

// 遍历对象
for (const key in scores) {
    console.log(`${key}: ${scores[key]}`);
}
```