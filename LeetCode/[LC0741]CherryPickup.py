class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        def walk(r, c, d):
            if d == 0:
                return r + 1, c
            else:
                return r, c + 1
        n = len(grid)
        dp = [[[-1] * n for __ in range(n)] for _ in range(n * 2)] 
        dp[0][0][0] = 1 if grid[0][0] == 1 else 0
        for step in range(n * 2 - 2):
            for r1 in range(n):
                for r2 in range(n):
                    c1, c2 = step - r1, step - r2
                    if not (0 <= c1 <= n-1 and 0 <= c2 <= n-1 and dp[step][r1][r2] >= 0): continue
                    for d1 in range(0, 2):
                        for d2 in range(0, 2):
                            nr1, nc1 = walk(r1, c1, d1)
                            nr2, nc2 = walk(r2, c2, d2)
                            if 0 <= nr1 <= n-1 and 0 <= nc1 <= n-1 and 0 <= nr2 <= n-1 and 0 <= nc2 <= n-1 and grid[nr1][nc1] != -1 and grid[nr2][nc2] != -1:
                                val = grid[nr1][nc1] + grid[nr2][nc2]
                                if nr1 == nr2 and nc1 == nc2: val -= grid[nr1][nc1]
                                dp[step+1][nr1][nr2] = max(dp[step+1][nr1][nr2], dp[step][r1][r2] + val)
        return max(dp[n * 2 - 2][n - 1][n - 1], 0)
