impl Solution {
    pub fn longest_ideal_string(s: String, k: i32) -> i32 {
        let mut dp = [0; 26];
        for ch in s.as_bytes()
        {
            let ord = (ch - b'a') as i32;
            let old_dp = dp.clone();
            for i in 0..26
            {
                if (ord - i).abs() <= k
                {
                    dp[ord as usize] = dp[ord as usize].max(old_dp[i as usize] + 1);
                }
            }
        }
        let mut ans = 0;
        for v in dp
        {
            ans = ans.max(v)
        }
        ans
    }
}