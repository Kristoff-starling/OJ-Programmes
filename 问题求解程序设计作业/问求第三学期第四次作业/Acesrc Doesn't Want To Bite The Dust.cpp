#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const LL LINF=2e16;

namespace flow
{
    int head[800048],cur[800048],to[800048],nxt[800048],tot,t,S,T;LL f[800048];
    void init(int _t,int _S,int _T) {rep(i,0,_t) head[i]=0;tot=1;t=_t;S=_S;T=_T;}
    void addedge(int s,int t,LL cap)
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
    LL dfs(int x,LL maxf)
    {
        if (x==T || !maxf) return maxf;
        LL y,minf,now,ans=0;
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
    inline LL dinic()
    {
        LL ans=0;
        while (bfs())
        {
            for (int i=0;i<=t;i++) cur[i]=head[i];
            ans+=dfs(S,LINF);
        }
        return ans;
    }
}

int n,m;
int A[100],B[100],C[100],L[100],R[100];
int u[200],v[200],d[200];
int sum[100];

int getid(int x,int y)
{
    return sum[x-1]+y-L[x]+1;
}

int calc(int a,int b,int c,int x)
{
    return a*x*x+b*x+c;
}

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d%d%d",A+i,B+i,C+i);
    rep(i,1,n) scanf("%d%d",L+i,R+i);
    rep(i,1,m) scanf("%d%d%d",u+i,v+i,d+i);
    rep(i,1,n) sum[i]=R[i]-L[i]+2,sum[i]+=sum[i-1];
    flow::init(sum[n]+1,0,sum[n]+1);
    rep(i,1,n) rep(j,L[i],R[i]) flow::addedge(getid(i,j),getid(i,j+1),1e7-calc(A[i],B[i],C[i],j));
    rep(i,1,n) flow::addedge(0,getid(i,L[i]),LINF),flow::addedge(getid(i,R[i]+1),sum[n]+1,LINF);
    rep(i,1,m)
    {
        rep(j,L[v[i]],R[v[i]]) if (j+d[i]+1<=R[u[i]]+1)
            flow::addedge(getid(u[i],max(j+d[i]+1,L[u[i]])),getid(v[i],j+1),LINF);
    }
    printf("%lld\n",10000000ll*n-flow::dinic());
    return 0;
}