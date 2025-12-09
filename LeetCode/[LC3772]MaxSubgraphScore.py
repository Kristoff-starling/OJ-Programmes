class Solution:
    def maxSubgraphScore(self, n: int, edges: List[List[int]], good: List[int]) -> List[int]:
        dp = [0] * n
        va = [list() for _ in range(n)]
        for x, y in edges:
            va[x].append(y)
            va[y].append(x)
        def dfs(x: int, father: int):
            dp[x] = (1 if good[x] else -1)
            for y in va[x]:
                if y != father:
                    dfs(y, x)
                    dp[x] += max(0, dp[y])
        dfs(0, -1)
        ans = [0] * n
        def getans(x: int, father: int):
            ans[x] = dp[x]
            for y in va[x]:
                if y != father:
                    dx = max(0, dp[y])
                    dp[x] -= dx
                    dy = max(0, dp[x])
                    dp[y] += dy
                    getans(y, x)
                    dp[x] += dx
                    dp[y] -= dy
        getans(0, -1)
        return ans
                