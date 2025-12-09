class Solution:
    def maxValueAfterReverse(self, nums: List[int]) -> int:
        ans = sum([abs(nums[i] - nums[i + 1]) for i in range(len(nums) - 1)])
        dmax = 0
        pmin, pmax = 1000000, -1000000
        for i in range(len(nums) - 1):
            minn, maxn = min(nums[i], nums[i+1]), max(nums[i], nums[i + 1])
            dmax = max(dmax, 2 * (minn - pmin))
            dmax = max(dmax, 2 * (pmax - maxn))
            if i > 0:
                minn, maxn = min(nums[i - 1], nums[i]), max(nums[i - 1], nums[i])
                pmin = min(pmin, maxn)
                pmax = max(pmax, minn)
        for i in range(2, len(nums)):
            dmax = max(dmax, abs(nums[i] - nums[0]) - abs(nums[i] - nums[i-1]))
        for i in range(len(nums) - 2):
            dmax = max(dmax, abs(nums[i] - nums[-1]) - abs(nums[i] - nums[i + 1]))
        return ans + dmax