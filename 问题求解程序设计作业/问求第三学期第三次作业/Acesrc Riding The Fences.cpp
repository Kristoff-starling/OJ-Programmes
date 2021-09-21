#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int m;

int ga[501][501],d[501];

int sta[2000],stot,ans[2000],tot;

void fleury(int cur)
{
    sta[++stot]=cur;
    rep(i,1,500) if (ga[cur][i])
    {
        ga[cur][i]--;ga[i][cur]--;
        fleury(i);
    }
    ans[++tot]=sta[stot--];
}

int main ()
{
    scanf("%d",&m);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),d[x]++,d[y]++,ga[x][y]++,ga[y][x]++;
    int minn=501;REP(i,500,1) if (d[i]&1) minn=i;
    if (minn>500) REP(i,500,1) if (d[i]) minn=i;
    fleury(minn);
    REP(i,tot,1) printf("%d\n",ans[i]);
    return 0;
}