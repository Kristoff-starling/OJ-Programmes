class Solution:
    def minMoves2(self, nums: List[int]) -> int:
        std = sorted(nums)[(len(nums) + 1) // 2 - 1]
        return sum([abs(num - std) for num in nums])