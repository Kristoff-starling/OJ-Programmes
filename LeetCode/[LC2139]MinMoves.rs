impl Solution {
    pub fn min_moves(target: i32, max_doubles: i32) -> i32 {
        let mut target = target;
        let mut max_doubles = max_doubles;
        let mut ans: i32 = 0;
        while target > 1 && max_doubles > 0 {
            if max_doubles > 0 && target % 2 == 0 {
                max_doubles -= 1;
                target >>= 1;
            }
            else {
                target -= 1;
            }
            ans += 1
        }
        ans + target - 1
    }
}