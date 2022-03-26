class Solution:
    def calPoints(self, ops: List[str]) -> int:
        ans = []
        for op in ops:
            if op == '+': ans.append(ans[-1] + ans[-2])
            elif op == 'D': ans.append(ans[-1] * 2)
            elif op == 'C': ans = ans[:-1:]
            else: ans.append(int(op))
        return sum(ans)