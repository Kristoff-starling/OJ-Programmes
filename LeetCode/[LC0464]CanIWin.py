class Solution:
    def canIWin(self, maxChoosableInteger: int, desiredTotal: int) -> bool:
        dp = {}
        @cache
        def solve(num, Mask) -> bool:
            if (num, Mask) in dp: return dp[(num, Mask)]
            res = False
            for i in range(1, maxChoosableInteger + 1):
                if (Mask >> (i - 1) & 1) == 0:
                    if num + i >= desiredTotal: res = True
                    elif solve(num + i, Mask | (1 << (i - 1))) == False: res = True
                if res == True: break
            dp[(num, Mask)] = res
            return res

        return (1 + maxChoosableInteger) * maxChoosableInteger // 2 >= desiredTotal and solve(0, 0)