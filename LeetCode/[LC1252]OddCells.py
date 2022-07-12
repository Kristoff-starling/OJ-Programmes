class Solution:
    def oddCells(self, m: int, n: int, indices: List[List[int]]) -> int:
        cr, cc = [0] * m, [0] * n
        for r, c in indices: cr[r], cc[c] = cr[r] + 1, cc[c] + 1
        rodd, codd = sum(cr[r] % 2 for r in range(m)), sum(cc[c] % 2 for c in range(n))
        return rodd * (n - codd) + (m - rodd) * codd