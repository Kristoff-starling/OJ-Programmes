class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1: return s
        ans, MOD = "", numRows * 2 - 2
        for r in range(numRows):
            ans += ''.join([s[i] for i in range(len(s)) if (i % MOD == r) or (i % MOD == MOD - r) ])
        return ans