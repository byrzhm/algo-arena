impl Solution {
    pub fn minimum_cost(m: i32, n: i32, horizontal_cut: Vec<i32>, vertical_cut: Vec<i32>) -> i64 {
        let mut horizontal_cut = horizontal_cut.into_iter().collect::<Vec<_>>();
        let mut vertical_cut = vertical_cut.into_iter().collect::<Vec<_>>();
        horizontal_cut.sort_unstable();
        vertical_cut.sort_unstable();
        let mut h = 1;
        let mut v = 1;
        let mut res = 0i64;
        while !horizontal_cut.is_empty() || !vertical_cut.is_empty() {
            if vertical_cut.is_empty() || (!horizontal_cut.is_empty() && horizontal_cut.last().unwrap() > vertical_cut.last().unwrap()) {
                res += (*horizontal_cut.last().unwrap() as i64) * h as i64;
                horizontal_cut.pop();
                v += 1;
            } else {
                res += (*vertical_cut.last().unwrap() as i64) * v as i64;
                vertical_cut.pop();
                h += 1;
            }
        }
        res
    }
}