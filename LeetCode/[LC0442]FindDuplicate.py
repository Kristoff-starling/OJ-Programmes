class Solution:
    def findDuplicates(self, nums: List[int]) -> List[int]:
        s, ans = set(nums), []
        for num in nums: 
            if num in s:
                s.remove(num)
            else: ans.append(num)
        return ans