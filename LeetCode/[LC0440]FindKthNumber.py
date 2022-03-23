class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        def countTree(cur, n) -> int:
            res, last = 0, cur + 1
            while (cur <= n):
                res += min(n + 1, last) - cur
                cur, last = cur * 10, last * 10
            return res
        cur, k = 1, k - 1
        while k > 0:
            res = countTree(cur, n)
            if res <= k: cur, k = cur + 1, k - res
            else: cur, k = cur * 10, k - 1
        return cur