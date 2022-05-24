class Solution:
    def findSubstringInWraproundString(self, p: str) -> int:
        cnt = [0] * 26
        alpha = 'abcdefghijklmnopqrstuvwxyz'
        for ind, cur in enumerate(alpha):
            l = 1 if p[0] == cur else 0
            hd = cur if p[0] == cur else ''
            cnt[ind] = l
            for i in range(1, len(p)):
                if hd == '':
                    if p[i] == cur: l, hd = 1, cur
                else:
                    lastch, ch = p[i-1], p[i]
                    if ord(ch) == ord(lastch) + 1 or ord(ch) == ord(lastch) - 25: l += 1
                    else:
                        l = 1 if p[i] == cur else 0
                        hd = cur if p[i] == cur else ''
                cnt[ind] = max(cnt[ind], l)
        return sum(cnt)