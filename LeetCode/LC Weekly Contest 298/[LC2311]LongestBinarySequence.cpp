class Solution {
    int dp[1048][1048];
public:
    int longestSubsequence(string s, int k) {
        int len = int(s.size());
        dp[0][0] = 0;
        dp[0][1] = s[0] - '0';
        for (int j = 2; j <= len; j++) dp[0][j] = k+1;
        for (int i = 1; i <= len - 1; i++)
            for (int j = 0; j <= len; j++)
                dp[i][j] = k + 1;
        for (int i = 1; i <= len - 1; i++)
        {
            dp[i][0] = 0;
            for (int j = 1; j <= len; j++)
            {
                dp[i][j] = dp[i-1][j];
                if (dp[i-1][j-1] <= k) dp[i][j] = min(dp[i][j], dp[i-1][j-1] * 2 + s[i] - '0');
            }
        }
        for (int i = len; i >= 0; i--) if (dp[len-1][i] <= k) return i;
        return 0;
    }
};