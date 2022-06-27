class Solution {
public:
    int dp[100048][2];
    const int MOD = 1e9 + 7;
    int countHousePlacements(int n) {
        dp[1][0] = dp[1][1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % MOD;
            dp[i][1] = dp[i-1][0];
        }
        int ans = (dp[n][0] + dp[n][1]) % MOD;
        return 1ll * ans * ans % MOD;
    }
};