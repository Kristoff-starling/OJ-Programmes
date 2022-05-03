class Solution:
    def reorderLogFiles(self, logs: List[str]) -> List[str]:
        alpha = [log for log in logs if log[-1].isalpha()]
        num = [log for log in logs if not log[-1].isalpha()]
        alpha.sort(key=lambda x: (x[x.index(' ')+1:], x[:x.index(' ')+1]))
        return alpha + num