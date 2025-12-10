class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        import string
        from collections import defaultdict
        MOD = 1000000007
        suffix_transfer = {}
        for i in range(0, len(evil)):
            for nxt in string.ascii_lowercase:
                new_string = evil[:i] + str(nxt)
                for l in range(len(new_string) + 1):
                    if new_string[l:] == evil[:len(new_string) - l]:
                        suffix_transfer[(i, nxt)] = len(new_string) - l
                        break
        dp = [defaultdict(int) for _ in range(n)]
        for i in range(n):
            if i == 0:
                prev = {(0, 0, 0): 1}
            else:
                prev = dp[i - 1]
            for (lower, upper, suffix), count in prev.items():
                for nxt in string.ascii_lowercase:
                    if lower == 0 and nxt < s1[i]:
                        continue
                    if upper == 0 and nxt > s2[i]:
                        continue
                    nsuffix = suffix_transfer[(suffix, nxt)]
                    if nsuffix == len(evil):
                        continue
                    nlower, nupper = lower, upper
                    if lower == 0 and nxt > s1[i]:
                        nlower = 1
                    if upper == 0 and nxt < s2[i]:
                        nupper = 1
                    nstate = (nlower, nupper, nsuffix)
                    dp[i][nstate] = (dp[i][nstate] + count) % MOD
        return sum(dp[n-1].values()) % MOD