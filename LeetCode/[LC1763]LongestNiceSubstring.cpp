class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int n,cnt,ans,l,r;
    int low[48],high[48];
public:
    string longestNiceSubstring(string s) {
        n=int(s.size());cnt=0;;ans=0;
        rep(i,0,n-1) rep(j,i+1,n-1)
        {
            if (j-i+1<=ans) continue;
            memset(low,0,sizeof(low));memset(high,0,sizeof(high));
            rep(k,i,j) if (isupper(s[k])) high[s[k]-'A'+1]=1; else low[s[k]-'a'+1]=1;
            bool f=true;
            rep(i,1,26) if (high[i]^low[i]) f=false;
            if (f) ans=j-i+1,l=i,r=j;
        }
        if (ans==0) return "";
        return s.substr(l,ans);
    }
};