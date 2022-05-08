class Solution:
    def diStringMatch(self, s: str) -> List[int]:
        l, r, ans = 0, len(s), []
        for ch in s:
            if ch == 'I':
                ans.append(l)
                l += 1
            else:
                ans.append(r)
                r -= 1
        return ans + [r]