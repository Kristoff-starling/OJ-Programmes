class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int cnt[27];
public:
    int maxNumberOfBalloons(string text) {
        memset(cnt,0,sizeof(cnt));
        rep(i,0,int(text.size())-1) cnt[text[i]-'a'+1]++;
        return min(min(min(cnt[2],cnt[1]),min(cnt[12]/2,cnt[15]/2)),cnt[14]);
    }
};