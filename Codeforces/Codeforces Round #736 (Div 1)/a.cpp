#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e5;

int n,m,q;

set<int> s[MAXN+48];
int ans;

void add(int x,int y)
{
    int ori=0;
    if (s[x].empty() || (*(--s[x].end()))<x) ori=1;
    s[x].insert(y);
    if (*(--s[x].end())>x && ori==1) ans--;
}

void sub(int x,int y)
{
    int ori=1;
    if (!s[x].empty() && (*(--s[x].end()))>x) ori=0;
    set<int>::iterator iter=s[x].find(y);s[x].erase(iter);
    if ((s[x].empty() || (*(--s[x].end()))<x) && ori==0) ans++;
}

int main ()
{
    scanf("%d%d",&n,&m);int op,x,y;
    ans=n;
    rep(i,1,m)
    {
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    scanf("%d",&q);
    while (q--)
    {
        scanf("%d",&op);
        if (op==1) scanf("%d%d",&x,&y),add(x,y),add(y,x);
        if (op==2) scanf("%d%d",&x,&y),sub(x,y),sub(y,x);
        if (op==3) printf("%d\n",ans);
    }
    return 0;
}