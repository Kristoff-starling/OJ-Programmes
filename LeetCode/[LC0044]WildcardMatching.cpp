class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int n,m;
    bool match(char c1,char c2) {return c1=='?' || c2=='?' || c1==c2;}
public:
    bool isMatch(string s, string p) {
        n=int(s.size());m=int(p.size());
        vector<vector<bool> > dp(n+48, vector<bool>(m+48,false));
        dp[0][0]=true;
        rep(i,0,n) rep(j,0,m) if (dp[i][j])
        {
            if (i && s[i-1]=='*') dp[i][j+1]=true;
            if (j && p[j-1]=='*') dp[i+1][j]=true;
            if (i<n && j<m && match(s[i],p[j])) dp[i+1][j+1]=true;
            if (i<n && s[i]=='*') dp[i+1][j]=true;
            if (j<m && p[j]=='*') dp[i][j+1]=true;
        }
        return dp[n][m];
    }
};