#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e9;

bool isprime[300048];int prime[300048],tot;
vector<int> odd,even,tmp;int n;bool hasone;

void sieve()
{
    memset(isprime,true,sizeof(isprime));isprime[1]=false;tot=0;
    rep(i,2,300000)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=300000;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
}

namespace flow
{
    int head[800048],cur[6000048],to[6000048],nxt[6000048],f[6000048],tot,t,S,T;
    inline void init(int _t,int _S,int _T) {memset(head,0,sizeof(head));tot=1;t=_t;S=_S;T=_T;}
    inline void addedge(int s,int t,int cap)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
        to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
    }
    int q[800048],Head,Tail;int depth[800048];
    inline bool bfs()
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
    inline int dfs(int x,int maxf)
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

int main ()
{
    sieve();hasone=false;scanf("%d",&n);int x,ans=0;
    rep(i,1,n)
    {
        scanf("%d",&x);
        if (x==1)
        {
            if (!hasone)
                hasone=true,odd.push_back(x);
        }
        else {if (x&1) odd.push_back(x); else even.push_back(x);}
    }
    int N=int(odd.size()),M=int(even.size());flow::init(N+M+1,0,N+M+1);
    rep(i,1,N) flow::addedge(0,i,1);rep(i,1,M) flow::addedge(N+i,N+M+1,1);
    rep(i,1,N) rep(j,1,M) if (isprime[odd[i-1]+even[j-1]]) flow::addedge(i,N+j,1);
    ans=N+M-flow::dinic();
    printf("%d\n",ans);
    return 0;
}