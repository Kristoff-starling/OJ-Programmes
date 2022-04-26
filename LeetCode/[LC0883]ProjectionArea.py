class Solution:
    def projectionArea(self, grid: List[List[int]]) -> int:
        return sum([sum(map(max, grid)), sum(map(max, zip(*grid))), sum(v > 0 for row in grid for v in row)])