class Solution:
    def orderlyQueue(self, s: str, k: int) -> str:
        if k > 1: return ''.join(sorted(s))
        return min([s[i:] + s[:i] for i in range(0, len(s))])