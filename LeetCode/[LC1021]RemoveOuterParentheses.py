class Solution:
    def removeOuterParentheses(self, s: str) -> str:
        ans, cnt = '', 0
        for ch in s:
            cnt += 1 if ch == '(' else -1
            if not((cnt == 1 and ch == '(') or (cnt == 0 and ch == ')')):
                ans += str(ch)
        return ans