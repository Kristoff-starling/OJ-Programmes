class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    int n,m,ans,tmpans;bool touched;
    int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
    void dfs(int x,int y,vector<vector<int>> &grid)
    {
        tmpans++;grid[x][y]=-1;
        if (x==0 || x==n-1 || y==0 || y==m-1) touched=true;
        rep(dir,0,3)
        {
            int xx=x+dx[dir],yy=y+dy[dir];
            if (0<=xx && xx<=n-1 && 0<=yy && yy<=m-1 && grid[xx][yy]==1)
                dfs(xx,yy,grid);
        }
        return;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        n=int(grid.size());m=int(grid[0].size());ans=0;
        rep(i,1,n) rep(j,1,m) if (grid[i-1][j-1]==1)
        {
            touched=false;tmpans=0;dfs(i-1,j-1,grid);
            if (!touched) ans+=tmpans;
        }
        return ans;
    }
};