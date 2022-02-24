class Solution:
    def findBall(self, grid: List[List[int]]) -> List[int]:
        m, n = len(grid), len(grid[0])
        def dfs(x: int, y: int) -> int:
            if x == m: return y
            if grid[x][y] == 1:
                return -1 if y == n-1 or grid[x][y+1] == -1 else dfs(x+1, y+1)
            else:
                return -1 if y == 0 or grid[x][y-1] == 1 else dfs(x+1, y-1)
        return [dfs(0, i) for i in range(0, n)]