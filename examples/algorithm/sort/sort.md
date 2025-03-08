### **1. C++**

**库**: `<algorithm>`  
**函数**: `std::sort`  
**特点**: 原地排序（修改原容器），默认升序。

#### 基本用法：

```cpp
#include <algorithm>
#include <vector>

std::vector<int> nums = {3, 1, 4, 1, 5};
std::sort(nums.begin(), nums.end()); // 升序
```

#### 自定义排序（降序）：

```cpp
// 方法1: 使用 greater<T>
std::sort(nums.begin(), nums.end(), std::greater<int>());

// 方法2: Lambda 表达式
std::sort(nums.begin(), nums.end(), [](int a, int b) {
    return a > b; // 降序
});
```

---

### **2. Python**

**内置函数**:

- `sorted()`: 返回新列表，不修改原数据
- `list.sort()`: 原地排序（仅列表可用）

#### 基本用法：

```python
nums = [3, 1, 4, 1, 5]
sorted_nums = sorted(nums)  # 升序，返回新列表
nums.sort()                 # 原地升序排序
```

#### 自定义排序：

```python
# 降序
sorted_nums = sorted(nums, reverse=True)

# 按字符串长度排序
words = ["apple", "cat", "banana"]
sorted_words = sorted(words, key=lambda x: len(x))

# 自定义对象排序（按 age 字段）
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

people = [Person("Alice", 30), Person("Bob", 25)]
sorted_people = sorted(people, key=lambda p: p.age)
```

---

### **3. Java**

**工具类**:

- `Arrays.sort()`: 对数组排序
- `Collections.sort()`: 对 List 集合排序

#### 基本用法：

```java
import java.util.Arrays;
import java.util.Collections;
import java.util.ArrayList;

// 数组排序
int[] nums = {3, 1, 4, 1, 5};
Arrays.sort(nums); // 升序

// List 排序
ArrayList<Integer> list = new ArrayList<>(Arrays.asList(3, 1, 4, 1, 5));
Collections.sort(list); // 升序
```

#### 自定义排序：

```java
// 降序（使用 Comparator）
Integer[] nums = {3, 1, 4, 1, 5};
Arrays.sort(nums, (a, b) -> b - a); // Lambda 表达式

// 按字符串长度排序
ArrayList<String> words = new ArrayList<>(Arrays.asList("apple", "cat", "banana"));
Collections.sort(words, (a, b) -> a.length() - b.length());

// 自定义对象排序（按 age 字段）
class Person {
    String name;
    int age;
    // 构造方法省略
}

ArrayList<Person> people = new ArrayList<>();
Collections.sort(people, (p1, p2) -> p1.age - p2.age);
```

---

### **4. Go**

**包**: `sort`  
**特点**: 需要实现 `sort.Interface` 接口（定义 `Len`, `Swap`, `Less` 方法）。

#### 基本用法：

```go
package main

import (
    "fmt"
    "sort"
)

// 对 int 切片排序
nums := []int{3, 1, 4, 1, 5}
sort.Ints(nums) // 升序
fmt.Println(nums) // [1 1 3 4 5]

// 降序
sort.Sort(sort.Reverse(sort.IntSlice(nums)))
```

#### 自定义排序：

```go
// 按字符串长度排序
words := []string{"apple", "cat", "banana"}
sort.Slice(words, func(i, j int) bool {
    return len(words[i]) < len(words[j])
})

// 自定义结构体排序
type Person struct {
    Name string
    Age  int
}

people := []Person{
    {"Alice", 30},
    {"Bob", 25},
}

// 按 Age 升序
sort.Slice(people, func(i, j int) bool {
    return people[i].Age < people[j].Age
})
```
