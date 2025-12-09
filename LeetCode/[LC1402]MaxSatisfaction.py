class Solution:
    def maxSatisfaction(self, satisfaction: List[int]) -> int:
        s = sorted(satisfaction, key=lambda x: -x)
        if s[0] < 0:
            return 0
        max_sum, idx = 0, 0
        while idx < len(s) and max_sum + s[idx] > 0:
            max_sum += s[idx]
            idx += 1
        ans = 0
        for i in range(idx):
            ans += s[i] * (idx - i)
        return ans
        