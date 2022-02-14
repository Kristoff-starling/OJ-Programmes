class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        from collections import Counter
        stack = []
        visited = set()
        cnt = Counter(s)
        for ch in s:
            cnt[ch] -= 1
            if ch not in visited:
                visited.add(ch)
                while stack and stack[-1] > ch and cnt[stack[-1]] > 0:
                    visited.remove(stack[-1])
                    stack.pop()
                stack.append(ch)
        return "".join(stack)