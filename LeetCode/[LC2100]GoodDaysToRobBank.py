class Solution:
    def goodDaysToRobBank(self, security: List[int], time: int) -> List[int]:
        n = len(security)
        left, right = [0] * n, [0] * n
        for i in range(1, n): left[i] = (0 if security[i] > security[i-1] else left[i-1] + 1)
        for i in range(n-2, -1, -1): right[i] = (0 if security[i] > security[i+1] else right[i+1] + 1)
        return [i for i in range(n) if left[i] >= time and right[i] >= time]