class Solution:
    def deserialize(self, s: str) -> NestedInteger:
        if s[0] != '[': return NestedInteger(int(s))
        num, neg, stack = 0, False, []
        for i, ch in enumerate(s):
            if ch == '-': neg = True
            elif ch == '[': stack.append(NestedInteger())
            elif ch.isdigit(): num = num * 10 + int(ch)
            elif ch in ',]':
                if s[i-1].isdigit():
                    if neg: num = -num
                    stack[-1].add(NestedInteger(num))
                num, neg = 0, False
                if ch == ']' and len(stack) > 1:
                    stack[-2].add(stack.pop())
        assert(len(stack) == 1)
        return stack.pop()