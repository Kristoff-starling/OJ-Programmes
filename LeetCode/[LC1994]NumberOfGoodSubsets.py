class Solution:
    def numberOfGoodSubsets(self, nums: List[int]) -> int:
        MOD = 1000000007
        valid = [2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, 19, 21, 22, 23, 26, 29, 30]
        cnt = Counter(nums)
        dp = defaultdict(int)
        dp[1] = (2 ** cnt[1]) % MOD
        for num in valid:
            for x in list(dp):
                if math.gcd(x, num) == 1:
                    dp[x * num] = (dp[x * num] + cnt[num] * dp[x]) % MOD
        return (sum(dp.values()) - dp[1]) % MOD