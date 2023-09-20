#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e9;

int n,m;
int a[101][101],b[101][101],sa[101][101],sb[101][101];

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

int getind(int l,int x,int y) {return (l-1)*n*m+(x-1)*m+y;}

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int main ()
{
    scanf("%d%d",&n,&m);int ans=0;
    rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]),ans+=a[i][j];
    rep(i,1,n) rep(j,1,m) scanf("%d",&b[i][j]),ans+=b[i][j];
    rep(i,1,n) rep(j,1,m) scanf("%d",&sa[i][j]),ans+=sa[i][j];
    rep(i,1,n) rep(j,1,m) scanf("%d",&sb[i][j]),ans+=sb[i][j];
    flow::init(n*m*3+1,0,n*m*3+1);
    int S=flow::S,T=flow::T;
    rep(i,1,n) rep(j,1,m) flow::addedge(S,getind(1,i,j),a[i][j]),flow::addedge(getind(1,i,j),T,b[i][j]);
    rep(i,1,n) rep(j,1,m)
    {
        flow::addedge(S,getind(2,i,j),sa[i][j]);flow::addedge(getind(2,i,j),getind(1,i,j),INF);
        rep(dir,0,3)
        {
            int xx=i+dx[dir],yy=j+dy[dir];
            if (1<=xx && xx<=n && 1<=yy && yy<=m) flow::addedge(getind(2,i,j),getind(1,xx,yy),INF);
        }
        flow::addedge(getind(3,i,j),T,sb[i][j]);flow::addedge(getind(1,i,j),getind(3,i,j),INF);
        rep(dir,0,3)
        {
            int xx=i+dx[dir],yy=j+dy[dir];
            if (1<=xx && xx<=n && 1<=yy && yy<=m) flow::addedge(getind(1,xx,yy),getind(3,i,j),INF);
        }
    }
    ans-=flow::dinic();printf("%d\n",ans);
    return 0;
}