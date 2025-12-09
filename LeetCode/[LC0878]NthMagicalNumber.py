class Solution:
    def nthMagicalNumber(self, n: int, a: int, b: int) -> int:
        MOD = 1000000007
        def gcd(x, y):
            if y == 0:
                return x
            else:
                return gcd(y, x % y)
        g = gcd(a, b)
        group = a * b // g
        gnum = group // a + group // b - 1
        gcnt, remaining = n // gnum, n % gnum
        if remaining == 0:
            return group * gcnt % MOD
        lst = sorted([a * i for i in range(1, group // a)] + [b * i for i in range(1, group // b)])
        return (lst[remaining - 1] + group * gcnt % MOD) % MOD