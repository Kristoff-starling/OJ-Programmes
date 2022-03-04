class Solution:
    def subArrayRanges(self, nums: List[int]) -> int:
        ans = 0
        for i in range(len(nums)):
            minn, maxn = 1e10, -1e10
            for j in range(i, len(nums)):
                minn = min(minn, nums[j])
                maxn = max(maxn, nums[j])
                ans += maxn - minn
        return ans