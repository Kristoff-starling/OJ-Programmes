class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        m, n, res = len(mat), len(mat[0]), []
        for sm in range(m + n - 1):
            tmp = [mat[i][sm - i] for i in range(max(0, sm + 1 - n), min(sm + 1, m))]
            res += tmp if sm % 2 else tmp[::-1]
        return res