class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k <= 1: return 0
        n = len(nums)
        ans, r, prod = 0, 0, 1
        for l in range(n):
            if l != 0: prod /= nums[l-1]
            while r < n and prod * nums[r] < k:
                prod *= nums[r]
                r += 1
            ans += r - l
        return ans