class Solution:
    def minSubsequence(self, nums: List[int]) -> List[int]:
        s, cs, ans = sum(nums), 0, []
        nums.sort(key=lambda x: -x)
        ind = 0
        while cs <= s - cs:
            ans.append(nums[ind])
            cs += nums[ind]
            ind += 1
        return ans