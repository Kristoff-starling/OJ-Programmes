#include <bits/stdc++.h>
using namespace std;

char s[48];
int ans;

bool check(int cnt,int x,int y)
{
    if ((10-cnt)/2+x<y) return true;
    if ((10-cnt+1)/2+y<x) return true;
    return false;
}

void dfs(int cur,int x,int y)
{
    if (cur==10) return;
    int xx=x,yy=y;
    if (s[cur]=='1')
    {
        if (cur&1) xx++; else yy++;
        if (check(cur,xx,yy)) ans=min(ans,cur); else dfs(cur+1,xx,yy);
    }
    if (s[cur]=='0')
    {
        if (check(cur,xx,yy)) ans=min(ans,cur); else dfs(cur+1,xx,yy);
    }
    if (s[cur]=='?')
    {
        if (check(cur,xx,yy)) ans=min(ans,cur); else dfs(cur+1,xx,yy);
        if (cur&1) xx++; else yy++;
        if (check(cur,xx,yy)) ans=min(ans,cur); else dfs(cur+1,xx,yy);
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%s",s+1);
        ans=10;dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}