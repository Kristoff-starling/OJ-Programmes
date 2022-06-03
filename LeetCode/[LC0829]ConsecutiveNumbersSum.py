class Solution:
    def consecutiveNumbersSum(self, n: int) -> int:
        ans, i = 0, 1
        while i * (i + 1) // 2 <= n:
            if n % i == 0 and i % 2 == 1: ans += 1
            if n % i != 0 and (2 * n) % i == 0 and i % 2 == 0: ans += 1
            i += 1
        return ans