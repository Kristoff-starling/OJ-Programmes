class Solution:
    def findPairs(self, nums: List[int], k: int) -> int:
        nums = sorted(nums)
        n, l, ans = len(nums), 0, 0
        for r in range(n):
            if r != n-1 and nums[r] == nums[r+1]: continue
            while nums[r] - nums[l] > k: l += 1
            if l != r and nums[r] - nums[l] == k: ans += 1
        return ans