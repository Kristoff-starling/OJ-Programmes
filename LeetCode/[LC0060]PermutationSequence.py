class Solution:
    def getPermutation(self, n: int, k: int) -> str:
        def fac(n: int) -> int:
            if n <= 1:
                return 1
            else:
                return n * fac(n - 1)
        ans = []
        num = list(range(1, n + 1))
        for i in range(1, n + 1):
            id = math.ceil(k / fac(n - i)) - 1
            ans.append(str(num[id]))
            num.remove(num[id])
            k -= id * fac(n - i)
        return "".join(ans)