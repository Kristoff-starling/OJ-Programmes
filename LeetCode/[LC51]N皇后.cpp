class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    vector<vector<string> > res;
    vector<string> sol;
    int cnt[11][11],N;
    string pattern[48];
    void updateboard(int ix,int iy,int delta)
    {
        int x,y;
        rep(i,ix,N) cnt[i][iy]+=delta;
        for (x=ix,y=iy;x<=N && y<=N;x++,y++) cnt[x][y]+=delta;
        for (x=ix,y=iy;x<=N && y>=1;x++,y--) cnt[x][y]+=delta;
    }
    void dfs(int step)
    {
        if (step==N+1) {res.push_back(sol);return;}
        int x,y;
        rep(i,1,N) if (cnt[step][i]==0)
        {
            updateboard(step,i,1);sol.push_back(pattern[i]);
            dfs(step+1);
            updateboard(step,i,-1);sol.pop_back();
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        res.clear();sol.clear();memset(cnt,0,sizeof(cnt));N=n;
        rep(i,1,N)
        {
            pattern[i]="";
            rep(j,1,N) if (i==j) pattern[i]+="Q"; else pattern[i]+=".";
        }
        dfs(1);
        return res;
    }
};