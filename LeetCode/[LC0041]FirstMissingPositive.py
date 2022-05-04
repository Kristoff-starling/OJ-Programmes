class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            tmp, pos = nums[i], i
            while 1 <= tmp <= n and tmp != pos+1:
                t, tmp = tmp, nums[tmp-1]
                nums[t-1], pos = t, t-1
        for i in range(n):
            if nums[i] != i+1: return i+1
        return n+1