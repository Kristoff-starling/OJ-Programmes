class Solution:
    def luckyNumbers (self, matrix: List[List[int]]) -> List[int]:
        rowmin = [min(i) for i in matrix]
        colmax = [max(i) for i in zip(*matrix)]
        return list(set(rowmin) & set(colmax))