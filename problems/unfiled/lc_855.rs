use std::cmp::Ordering;
use std::collections::{BTreeSet, BinaryHeap};

#[derive(Debug, Eq, PartialEq)]
struct Interval {
    start: i32,
    end: i32,
}

impl Interval {
    fn new(start: i32, end: i32) -> Self {
        Interval {start, end}
    }

    fn length(&self) -> i32 {
        (self.end - self.start) / 2
    }
}

impl Ord for Interval {
    fn cmp(&self, other: &Self) -> Ordering {
        let length_cmp = self.length().cmp(&other.length());
        if length_cmp == Ordering::Equal {
            other.start.cmp(&self.start)
        } else {
            length_cmp
        }
    }
}

impl PartialOrd for Interval {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct ExamRoom {
    n: i32,
    seats: BTreeSet<i32>,
    pq: BinaryHeap<Interval>,
}

impl ExamRoom {
    fn new(n: i32) -> Self {
        ExamRoom {
            n,
            seats: BTreeSet::new(),
            pq: BinaryHeap::new(),
        }
    }
    
    fn seat(&mut self) -> i32 {
        if self.seats.is_empty() {
            self.seats.insert(0);
            return 0;
        }

        let left = *self.seats.iter().next().unwrap();
        let right = self.n - 1 - *self.seats.iter().rev().next().unwrap();
        while self.seats.len() >= 2 {
            if let Some(interval) = self.pq.peek() {
                let start = interval.start;
                let end = interval.end;
                if self.seats.contains(&start) && self.seats.contains(&end) &&
                   *self.seats.range((start + 1)..).next().unwrap() == end { // 不属于延迟删除的区间
                    let d = end - start;
                    if d / 2 < right || d / 2 <= left { // 最左或最右的座位更优
                        break;
                    }

                    self.pq.pop();
                    let mid = start + d / 2;
                    self.pq.push(Interval::new(start, mid));
                    self.pq.push(Interval::new(mid, end));
                    self.seats.insert(mid);
                    return mid;
                }
            }
            self.pq.pop(); // leave 函数中延迟删除的区间在此时删除
        }

        if right > left { // 最右的位置更优
            let last = *self.seats.iter().rev().next().unwrap();
            self.pq.push(Interval::new(last, self.n - 1));
            self.seats.insert(self.n - 1);
            self.n - 1
        } else {
            let first = *self.seats.iter().next().unwrap();
            self.pq.push(Interval::new(0, first));
            self.seats.insert(0);
            0
        }
    }
    
    fn leave(&mut self, p: i32) {
        if p != *self.seats.iter().next().unwrap() && p != *self.seats.iter().rev().next().unwrap() {
            let prev = *self.seats.range(..p).rev().next().unwrap();
            let next = *self.seats.range((p + 1)..).next().unwrap();
            self.pq.push(Interval::new(prev, next));
        }
        self.seats.remove(&p);
    }
}