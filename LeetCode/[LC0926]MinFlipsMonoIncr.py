class Solution:
    def minFlipsMonoIncr(self, s: str) -> int:
        zcnt, ocnt = 0, 0
        for ch in s:
            if ch == '0': zcnt += 1
            else: ocnt += 1
        zz, oo, ans = 0, 0, min(zcnt, ocnt)
        for i, ch in enumerate(s):
            if ch == '0': zz += 1
            else: oo += 1
            ans = min(ans, i + 1 - zz + len(s) - 1 - i - (ocnt - oo))
        return ans