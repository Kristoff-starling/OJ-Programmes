#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e9;

namespace flow
{
    int head[800048],cur[800048],to[800048],nxt[800048],tot,t,S,T;int f[800048];
    void init(int _t,int _S,int _T) {rep(i,0,_t) head[i]=0;tot=1;t=_t;S=_S;T=_T;}
    void addedge(int s,int t,int cap)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
        to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
    }
    int q[800048],Head,Tail;int depth[800048];
    bool bfs()
    {
        for (int i=0;i<=t;i++) depth[i]=-1;
        depth[S]=0;q[1]=S;Head=Tail=1;
        while (Head<=Tail)
        {
            int x=q[Head++];
            for (int i=head[x];i;i=nxt[i])
            {
                int y=to[i];
                if (depth[y]==-1 && f[i])
                {
                    depth[y]=depth[x]+1;
                    q[++Tail]=y;
                }
            }
        }
        return depth[T]!=-1;
    }
    int dfs(int x,int maxf)
    {
        if (x==T || !maxf) return maxf;
        int y,minf,now,ans=0;
        for (int &i=cur[x];i;i=nxt[i])
        {
            y=to[i];
            if (depth[y]==depth[x]+1 && f[i])
            {
                minf=min(maxf-ans,f[i]);
                now=dfs(y,minf);
                f[i]-=now;f[i^1]+=now;ans+=now;
            }
            if (ans>=maxf) return ans;
        }
        if (!ans) depth[x]=0;
        return ans;
    }
    inline int dinic()
    {
        int ans=0;
        while (bfs())
        {
            for (int i=0;i<=t;i++) cur[i]=head[i];
            ans+=dfs(S,INF);
        }
        return ans;
    }
}

int n,X1[101],Y1[101],X2[101],Y2[101];

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d%d",X1+i,Y1+i);
    rep(i,1,n) scanf("%d%d",X2+i,Y2+i);
    flow::init(2*n+1,0,2*n+1);
    rep(i,1,n) flow::addedge(0,i,1),flow::addedge(n+i,n+n+1,1);
    rep(i,1,n) rep(j,1,n) if (X1[i]<X2[j] && Y1[i]<Y2[j]) flow::addedge(i,n+j,1);
    printf("%d\n",flow::dinic());return 0;
}