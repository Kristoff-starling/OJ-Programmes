class Solution {
    unordered_map<int,int> p;
    long long dp[201][201];
public:
    long long solve(int n, int m)
    {
        if (dp[n][m] != -1) return dp[n][m];
        dp[n][m] = 0;
        if (p.find(n * 400 + m) != p.end()) dp[n][m] = p[n * 400 + m];
        if (n >= 2)
            for (int i = 1; i <= n-1; i++) dp[n][m] = max(dp[n][m], solve(i, m) + solve(n - i, m));
        if (m >= 2)
            for (int i = 1; i <= m-1; i++) dp[n][m] = max(dp[n][m], solve(n, i) + solve(n, m - i));
        return dp[n][m];
    }
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        for (int i = 0; i < int(prices.size());i++)
            p[prices[i][0] * 400 + prices[i][1]]=prices[i][2];
        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++)
                dp[i][j] = -1;
        return solve(m, n);
    }
};