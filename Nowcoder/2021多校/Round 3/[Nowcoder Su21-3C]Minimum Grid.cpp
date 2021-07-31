#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
using namespace std;

const int MAXN=2000;
const int INF=1e9;

int n,m,k;

int b[MAXN+48],c[MAXN+48];

vector<Pair> v[1000048];

namespace Flow
{
    int head[800048],cur[800048],to[800048],nxt[800048],f[800048],tot,t,S,T;
    inline void init(int _t,int _S,int _T) {rep(i,0,t) head[i]=0;tot=1;t=_t;S=_S;T=_T;}
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

unordered_map<int,int> m1,m2;int tot1,tot2;

int main ()
{
    scanf("%d%d%d",&n,&m,&k);int x,y;LL ans=0;
    rep(i,1,n) scanf("%d",b+i),ans+=b[i];
    rep(i,1,n) scanf("%d",c+i),ans+=c[i];
    rep(i,1,m)
    {
        scanf("%d%d",&x,&y);
        if (b[x]==c[y]) v[b[x]].pb(mp(x,y));
    }
    rep(i,1,k)
    {
        m1.clear();m2.clear();tot1=tot2=0;
        for (auto item : v[i])
        {
            if (!m1[item.x]) m1[item.x]=++tot1;
            if (!m2[item.y]) m2[item.y]=++tot2;
        }
        Flow::init(tot1+tot2+1,0,tot1+tot2+1);
        rep(i,1,tot1) Flow::addedge(0,i,1);
        rep(i,1,tot2) Flow::addedge(tot1+i,tot1+tot2+1,1);
        for (auto item : v[i]) Flow::addedge(m1[item.x],tot1+m2[item.y],1);
        int res=Flow::dinic();
        ans-=1ll*res*i;
    }
    printf("%lld\n",ans);
    return 0;
}