class Solution:
    def reverseOnlyLetters(self, s: str) -> str:
        alpha, ans = [ch for ch in s if ch.isalpha()], []
        for ch in s:
            if ch.isalpha():
                ans.append(alpha.pop())
            else:
                ans.append(ch)
        return "".join(ans)