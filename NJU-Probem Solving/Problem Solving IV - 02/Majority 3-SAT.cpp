#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e5;

int N,n;
vector<int> v[MAXN+48];

inline int getind(int x)
{
    if (x<0) return -x; else return N+x;
}

namespace SCC
{
    int dfn[MAXN+48],low[MAXN+48],bel[MAXN+48],ind,tot;bool visited[MAXN+48];
    int sta[MAXN+48],stot;
    inline void tarjan(int cur)
    {
        dfn[cur]=low[cur]=++ind;sta[++stot]=cur;visited[cur]=true;
        for (int i=0;i<int(v[cur].size());i++)
        {
            int to=v[cur][i];
            if (!dfn[to])
            {
                tarjan(to);
                low[cur]=min(low[cur],low[to]);
            }
            else if (visited[to]) low[cur]=min(low[cur],low[to]);
        }
        if (dfn[cur]==low[cur])
        {
            ++tot;int curv;
            do
            {
                curv=sta[stot--];
                visited[curv]=false;
                bel[curv]=tot;
            }
            while (curv!=cur);
        }
    }
    inline void FindSCC()
    {
        tot=stot=ind=0;rep(i,1,n) dfn[i]=low[i]=bel[i]=0,visited[i]=false;
        rep(i,1,n) if (!dfn[i]) tarjan(i);
    }
}

int main ()
{
    int ca,k;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&N,&k);int x,y,z;n=N*2;
        rep(i,1,n) v[i].clear();
        while (k--)
        {
            scanf("%d%d%d",&x,&y,&z);
            v[getind(-x)].push_back(getind(y));
            v[getind(-x)].push_back(getind(z));
            v[getind(-y)].push_back(getind(x));
            v[getind(-y)].push_back(getind(z));
            v[getind(-z)].push_back(getind(x));
            v[getind(-z)].push_back(getind(y));
        }
        SCC::FindSCC();
        bool f=true;
        rep(i,1,N) if (SCC::bel[getind(-i)]==SCC::bel[getind(i)]) f=false;
        puts(f?"yes":"no");
    }
    return 0;
}