// Range expressions
//     https://doc.rust-lang.org/reference/expressions/range-expr.html
// collect
//     https://doc.rust-lang.org/nightly/std/iter/trait.Iterator.html#method.collect
// Closure expressions
//     https://doc.rust-lang.org/reference/expressions/closure-expr.html
// Closure types
//     https://doc.rust-lang.org/reference/types/closure.html
// sort_by
//     https://doc.rust-lang.org/std/vec/struct.Vec.html#method.sort_by
// HashMap
//     https://doc.rust-lang.org/std/collections/struct.HashMap.html
// Borrow operators
//     https://doc.rust-lang.org/reference/expressions/operator-expr.html#borrow-operators
//
// References and Borrowing
//     https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html

use std::collections::HashMap;

impl Solution {
    pub fn get_kth(lo: i32, hi: i32, k: i32) -> i32 {
        let mut power_map: HashMap<i32, i32> = HashMap::from([(1, 0)]);
        
        let mut nums: Vec<(i32, i32)> = (lo..=hi).map(|x| {
            (Self::dfs(x, &mut power_map), x)
        }).collect();

        nums.sort_unstable();
        nums[k as usize - 1].1
    }

    fn dfs(x: i32, memo: &mut HashMap<i32, i32>) -> i32 {
        if let Some(&result) = memo.get(&x) {
            return result;
        }

        let result = if x % 2 == 0 {
            Self::dfs(x / 2, memo) + 1
        } else {
            Self::dfs((x * 3 + 1) / 2, memo) + 2
        };

        memo.insert(x, result);
        result
    }
}