class Solution:
    def countNumbersWithUniqueDigits(self, n: int) -> int:
        def A(n: int, m: int) -> int:
            rt = 1
            for i in range(n-m+1, n+1): rt *= i
            return rt
        
        if n == 0: return 1
        elif n == 1: return 10
        else:
            ans = 10
            for i in range(2, n+1): ans += 9 * A(9, i-1)
            return ans