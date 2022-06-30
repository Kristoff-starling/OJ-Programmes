class Solution:
    def numPrimeArrangements(self, n: int) -> int:
        def isPrime(n: int) -> bool:
            for i in range(2, n):
                if n % i == 0: return False
            return True
        cnt1, cnt2, ans1, ans2, MOD = 1, 0, 1, 1, 1000000007
        for i in range(2, n + 1):
            if isPrime(i):
                cnt2 += 1
                ans2 = (ans2 * cnt2) % MOD
            else:
                cnt1 += 1
                ans1 = (ans1 * cnt1) % MOD
        return ans1 * ans2 % MOD