class Solution:
    def minCost(self, costs: List[List[int]]) -> int:
        n = len(costs)
        dp = [[0] * 3 for _ in range(n)]
        dp[0] = costs[0]
        for i in range(1, n):
            for j in range(3):
                dp[i][j] = 1e9
                for k in range(3):
                    if j != k:
                        dp[i][j] = min(dp[i][j], dp[i-1][k] + costs[i][j])
        return min(dp[n-1][0], dp[n-1][1], dp[n-1][2])