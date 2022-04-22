class Solution:
    def maxRotateFunction(self, nums: List[int]) -> int:
        curans, s, n = 0, sum(nums), len(nums)
        for i in range(n): curans += i * nums[i]
        ans = curans
        for i in range(1, n):
            curans = curans - s + n * nums[i-1]
            ans = max(ans, curans)
        return ans