class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        nums.sort(key = bool, reverse = True)