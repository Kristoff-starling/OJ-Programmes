class Solution:
    def lengthLongestPath(self, fs: str) -> int:
        n, stack, pt, ans = len(fs), [], 0, 0
        while pt < n:
            depth = 0
            while fs[pt] == '\t':
                pt += 1; depth += 1
            length, isFile = 0, False
            while pt < n and fs[pt] != '\n':
                length += 1
                if fs[pt] == '.': isFile = True
                pt += 1
            pt += 1
            while len(stack) > depth: stack.pop()
            if len(stack) > 0: length += stack[-1] + 1
            stack.append(length)
            if isFile: ans = max(ans, length)
        return ans