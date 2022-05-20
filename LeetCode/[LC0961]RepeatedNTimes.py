class Solution:
    def repeatedNTimes(self, nums: List[int]) -> int:
        nums = sorted(nums)
        for i in range(1, len(nums)):
            if nums[i] == nums[i-1]: return nums[i]