class Solution:    
    def knightProbability(self, n: int, k: int, row: int, column: int) -> float:
        dirs = ((-2, 1), (-1, 2), (1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1))
        dp = {}
        def dfs(n: int, x: int, y: int, step: int) -> float:
            def inboard(n: int, x: int, y: int) -> bool:
                return 1<=x and x<=n and 1<=y and y<=n

            if step==0:
                return float(inboard(n, x, y))
            if not inboard(n, x, y):
                return 0
            if (x, y, step) in dp:
                return dp[(x, y, step)]
            res = 0
            for dir in dirs:
                res += dfs(n, x + dir[0], y + dir[1], step - 1)
            dp[(x, y, step)] = res / 8.0
            return res / 8.0

        return dfs(n, row + 1, column + 1, k)