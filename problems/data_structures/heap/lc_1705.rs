use std::collections::BinaryHeap;
use std::cmp::Reverse;

/*
 * https://doc.rust-lang.org/std/option/
 * https://doc.rust-lang.org/std/cmp/struct.Reverse.html
 * https://doc.rust-lang.org/std/collections/struct.BinaryHeap.html
 */

impl Solution {
    pub fn eaten_apples(apples: Vec<i32>, days: Vec<i32>) -> i32 {
        let mut ans = 0;
        let mut pq = BinaryHeap::new();
        let n = apples.len();
        let mut i = 0;
        
        while i < n {
            while let Some(Reverse((rotten_day, count))) = pq.peek() {
                if *rotten_day <= i as i32 {
                    pq.pop();
                } else {
                    break;
                }
            }
            let rotten_day = i as i32 + days[i];
            let count = apples[i];
            if count > 0 {
                pq.push(Reverse((rotten_day, count)));
            }
            if let Some(Reverse((rotten_day, mut count))) = pq.pop() {
                count -= 1;
                if count > 0 {
                    pq.push(Reverse((rotten_day, count)));
                }
                ans += 1;
            }
            i += 1;
        }

        while let Some(Reverse((rotten_day, mut count))) = pq.pop() {
            if rotten_day <= i as i32 {
                continue;
            }
            let num = std::cmp::min(rotten_day - i as i32, count);
            ans += num;
            i += num as usize;
        }
        ans
    }
}