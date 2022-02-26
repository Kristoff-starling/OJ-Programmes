class Solution:
    def optimalDivision(self, nums: List[int]) -> str:
        if len(nums) == 1: return str(nums[0])
        elif len(nums) == 2: return '/'.join(map(str, nums))
        else: return str(nums[0]) + "/(" + '/'.join(map(str, nums[1:])) + ")"