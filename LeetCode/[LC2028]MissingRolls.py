class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        m = len(rolls)
        s = mean * (n + m) - sum(rolls)
        if not n <= s <= 6 * n: return []
        base = s // n
        num = s - base * n
        return [base + 1] * num + [base] * (n - num)