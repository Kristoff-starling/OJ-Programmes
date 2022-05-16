class Solution:
    def compressString(self, S: str) -> str:
        ans, lastch, cnt = "", '', 0
        for ch in S:
            if ch == lastch: cnt += 1
            else:
                if cnt != 0: ans += str(lastch) + str(cnt)
                lastch = ch
                cnt = 1
        if cnt != 0:
            ans += str(lastch) + str(cnt)
        return ans if len(ans) < len(S) else S