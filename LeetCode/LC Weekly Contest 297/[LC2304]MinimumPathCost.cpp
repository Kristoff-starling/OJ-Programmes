class Solution {
    int dp[100][100];
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int n = int(grid.size()), m = int(grid[0].size());
        for (int i = 0; i < m; i++) dp[0][i] = grid[0][i];
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                dp[i][j] = 1000000000;
                for (int k = 0; k < m; k++)
                    dp[i][j] = min(dp[i][j], dp[i-1][k] + moveCost[grid[i-1][k]][j]);
                dp[i][j] += grid[i][j];
            }
        int ans = 1000000000;
        for (int i = 0; i < m; i++) ans = min(ans, dp[n-1][i]);
        return ans;
    }
};