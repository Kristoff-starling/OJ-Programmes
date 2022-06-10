class Solution:
    def countPalindromicSubsequences(self, s: str) -> int:
        n = len(s)
        dp = [[[0] * n for _ in range(n)] for __ in range(4)]
        for ch in range(4):
            for i in range(n):
                dp[ch][i][i] = 1 if ord(s[i]) == 97 + ch else 0
                if i >= 1: dp[ch][i][i-1] = 0
        for length in range(2, n + 1):
            for ch in range(4):
                for l in range(n - length + 1):
                    r = l + length - 1
                    if ord(s[l]) == 97 + ch and ord(s[r]) == 97 + ch:
                        dp[ch][l][r] = (2 + dp[0][l+1][r-1] + dp[1][l+1][r-1] + dp[2][l+1][r-1] + dp[3][l+1][r-1]) % 1000000007
                    elif ord(s[l]) == 97 + ch:
                        dp[ch][l][r] = dp[ch][l][r-1]
                    else: dp[ch][l][r] = dp[ch][l+1][r]
        return sum([dp[_][0][n-1] for _ in range(4)]) % 1000000007