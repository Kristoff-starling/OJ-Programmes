#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const LL LINF=2e17;

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

int n,W,p,q,x,y,z,a,b,c,d,e,f,r;
int coef[1048];bool L[1048],R[1048];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d%d",&n,&W,&p,&q);rep(i,1,n) coef[i]=1;
        rep(i,1,n) L[i]=R[i]=false;
        flow::init(n+1,0,n+1);
        while (p--)
        {
            scanf("%d%d%d%d%d%d%d%d%d",&x,&y,&z,&a,&b,&c,&d,&e,&f);
            coef[x]+=d-f;coef[y]+=e-d;coef[z]+=f-e;
            flow::addedge(x,y,2ll*W*a);flow::addedge(y,x,2ll*W*a);
            flow::addedge(y,z,2ll*W*b);flow::addedge(z,y,2ll*W*b);
            flow::addedge(z,x,2ll*W*c);flow::addedge(x,z,2ll*W*c);
        }
        while (q--)
        {
            scanf("%d%d%d",&x,&y,&r);
            if (!r)
                flow::addedge(y,x,LINF);
            else if (r==1)
                flow::addedge(x,y,LINF),flow::addedge(y,x,LINF);
            else
                L[x]=true,R[y]=true;
        }
        LL ans=0;
        rep(i,1,n)
        {
            if (L[i]) {flow::addedge(0,i,LINF),ans+=1ll*(-W)*coef[i];continue;}
            if (R[i]) {flow::addedge(i,n+1,LINF),ans+=1ll*W*coef[i];continue;}
            if (1ll*(-W)*coef[i]>=0) flow::addedge(i,n+1,1ll*(-W)*coef[i]); else ans+=1ll*(-W)*coef[i],flow::addedge(0,i,1ll*W*coef[i]);
            if (1ll*W*coef[i]>=0) flow::addedge(0,i,1ll*W*coef[i]); else ans+=1ll*W*coef[i],flow::addedge(i,n+1,-1ll*W*coef[i]);
        }
        ans+=flow::dinic();printf("%lld\n",ans);
    }
    return 0;
}