class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int ans;
    int cnt[11][11],N;
    void updateboard(int ix,int iy,int delta)
    {
        int x,y;
        rep(i,ix,N) cnt[i][iy]+=delta;
        for (x=ix,y=iy;x<=N && y<=N;x++,y++) cnt[x][y]+=delta;
        for (x=ix,y=iy;x<=N && y>=1;x++,y--) cnt[x][y]+=delta;
    }
    void dfs(int step)
    {
        if (step==N+1) {ans++;return;}
        int x,y;
        rep(i,1,N) if (cnt[step][i]==0)
        {
            updateboard(step,i,1);
            dfs(step+1);
            updateboard(step,i,-1);
        }
    }
public:
    int totalNQueens(int n) {
        ans=0;memset(cnt,0,sizeof(cnt));N=n;
        dfs(1);
        return ans;
    }
};