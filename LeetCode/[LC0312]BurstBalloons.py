# Let dp(i, j) be the maximum coins we can get by bursting the balloons in the range (i, j).
# i and j are not included in the range, we just guarantee that balloon i and j are bursted after all
# the balloon in this range.
# To compute this, we enumerate the LAST bursted balloon k in this range.
# dp(i, j) = max(dp(i, k) + nums[i] * nums[k] * nums[j] + dp(k, j)) for all k in (i, j).
class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        nums = [1] + nums + [1]
        n = len(nums)
        dp = [[-1] * (n + 1) for _ in range(n + 1)]
        def solve(l, r):
            if l + 1 >= r:
                return 0
            if dp[l][r] >= 0:
                return dp[l][r]
            for i in range(l + 1, r):
                dp[l][r] = max(dp[l][r], nums[l] * nums[i] * nums[r] + solve(l, i) + solve(i, r))
            return dp[l][r]
        return solve(0, n - 1)