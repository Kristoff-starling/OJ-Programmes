class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        lc, rc = [0 if s[0] == '|' else -1], [len(s)-1 if s[-1] == '|' else -1]
        for i, ch in enumerate(s[1:]):
            lc.append(i+1)
            if ch != '|': lc[-1] = lc[-2]
        for i, ch in enumerate(s[-2::-1]):
            rc.append(len(s)-i-2)
            if ch != '|': rc[-1] = rc[-2]
        rc = rc[::-1]
        cnt, cc = [0] * len(s), 0
        for i, ch in enumerate(s):
            if i != 0: cnt[i] += cnt[i-1]
            if ch == '*':
                cc += 1
            else:
                cnt[i], cc = cnt[i] + cc, 0
        ans = []
        for pair in queries:
            l, r = pair[0], pair[1]
            ans.append((0 if rc[l] == -1 or lc[r] == -1 or rc[l] >= lc[r] else cnt[lc[r]] - cnt[rc[l]]))
        return ans