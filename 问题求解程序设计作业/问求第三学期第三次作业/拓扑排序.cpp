#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=3e5;

int n,m,d[MAXN+48];
vector<int> v[MAXN+48];

priority_queue<int> q;

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),d[y]++,v[x].push_back(y);
    rep(i,1,n) if (!d[i]) q.push(-i);
    while (!q.empty())
    {
        int cur=-q.top();q.pop();
        printf("%d ",cur);
        for (auto to : v[cur])
        {
            d[to]--;
            if (!d[to]) q.push(-to);
        }
    }
    puts("");return 0;
}