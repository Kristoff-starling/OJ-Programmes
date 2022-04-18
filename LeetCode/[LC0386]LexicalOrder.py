class Solution:
    def lexicalOrder(self, n: int) -> List[int]:
        def next(x: int, lim: int) -> int:
            x *= 10
            if x <= lim: return x
            while x >= 10:
                x //= 10
                if x % 10 != 9 and x + 1 <= lim: return x + 1
            return 0
        
        cur, ans = next(1, n), [1]
        while cur != 0:
            ans.append(cur)
            cur = next(cur, n)
        return ans