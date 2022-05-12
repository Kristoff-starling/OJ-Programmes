class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        ans = 0
        for col in zip(*strs):
            if list(col) != sorted(col): ans += 1
        return ans