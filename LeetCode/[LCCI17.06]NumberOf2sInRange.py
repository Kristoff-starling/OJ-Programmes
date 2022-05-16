class Solution:
    def numberOf2sInRange(self, n: int) -> int:
        length, ans = len(str(n)), 0
        for i in range(length):
            front, back = str(n)[:length-i-1], str(n)[length-i:]
            fc = 0 if front == '' else int(front)
            bc = 0 if back == '' else int(back)
            ans += fc * (10 ** i)
            if int(str(n)[length-i-1]) == 2: ans += bc + 1
            elif int(str(n)[length-i-1]) > 2: ans += 10 ** i
        return ans