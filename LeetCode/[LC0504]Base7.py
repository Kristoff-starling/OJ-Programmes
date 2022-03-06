class Solution:
    def convertToBase7(self, num: int) -> str:
        if num == 0: return '0'
        flag, ans, num = ('-' if num < 0 else ''), '', abs(num)
        while num != 0:
            ans += str(num % 7)
            num //= 7
        return flag + ans[::-1]