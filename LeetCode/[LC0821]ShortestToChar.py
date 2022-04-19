class Solution:
    def shortestToChar(self, s: str, c: str) -> List[int]:
        n = len(s)
        pre, nxt, ans = [0] * n, [0] * n, []
        nxt[n-1] = (n if s[n-1] != c else n-1)
        for i in range(n-2, -1, -1): nxt[i] = (nxt[i+1] if s[i] != c else i)
        pre[0] = (-1 if s[0] != c else 0)
        for i in range(1, n): pre[i] = (pre[i-1] if s[i] != c else i)
        for i in range(n):
            tmp = (n if pre[i] == -1 else i - pre[i])
            if nxt[i] != n: tmp = min(tmp, nxt[i] - i)
            ans.append(tmp)
        return ans