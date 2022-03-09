class Solution:
    def bestRotation(self, nums: List[int]) -> int:
        n = len(nums)
        sum = [0] * n
        def addtag(l: int, r: int) -> bool:
            if l > r: return False
            sum[l] += 1
            if r != n-1: sum[r+1] -= 1
            return True
        for i,num in enumerate(nums):
            addtag(0, i - num)
            addtag(i + 1, min(i + 1 + (n - 1 - num), n - 1))
        for i in range(1, n): sum[i] += sum[i-1]
        return sum.index(max(sum))