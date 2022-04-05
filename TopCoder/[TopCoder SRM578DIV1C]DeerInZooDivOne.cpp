#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

/*(
struct Flow
{
    int head[1548],cur[1548],to[1548],nxt[1548],f[1548],cost[1548],tot,t;
    int maxflow,mincost,D[148];bool visited[148];
    inline void init(int _t) {t=_t;tot=1;for (register int i=0;i<=t;i++) head[i]=D[i]=0;}
    inline void addedge(int s,int t,int cap,int cc)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
        to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
    }
    inline int aug(int x,int maxf)
    {
        if (x==t)
        {
            maxflow+=maxf;
            mincost+=(-D[0])*maxf;
            return maxf;
        }
        visited[x]=true;
        int y,minf,now,ans=0;
        for (register int &i=cur[x];i;i=nxt[i])
        {
            y=to[i];
            if (!visited[y] && f[i] && D[x]+cost[i]-D[y]==0)
            {
                minf=min(maxf-ans,f[i]);
                now=aug(y,minf);
                f[i]-=now;f[i^1]+=now;ans+=now;
            }
        }
        return ans;
    }
    inline bool relabel()
    {
        int d=INF;
        for (register int cur=0;cur<=t;cur++)
            for (register int i=head[cur];i;i=nxt[i])
            {
                int y=to[i];
                if (visited[cur] && !visited[y] && f[i]) check_min(d,D[cur]+cost[i]-D[y]);
            }
        if (d>=INF) return false;
        for (register int cur=0;cur<=t;cur++) if (visited[cur]) D[cur]-=d;
        return true;
    }
    inline Pair zkw()
    {
        maxflow=mincost=0;
        do
        {
            for (register int i=0;i<=t;i++) cur[i]=head[i];
            do
                for (register int i=0;i<=t;i++) visited[i]=false;
            while (aug(0,INF));
        }
        while (relabel());
        return mp(maxflow,mincost);
    }
};
*/

struct Flow
{
    int head[1548],cur[1548],to[1548],nxt[1548],f[1548],w[1548],h[148],prevv[148],preve[148],tot,t;
    int dist[148];priority_queue<Pair> q;
    inline void init(int _t) {t=_t;tot=1;for (register int i=0;i<=t;i++) head[i]=h[i]=0;}
    inline void addedge(int s,int t,int cap,int cc)
    {
        to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;w[tot]=cc;
        to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;w[tot]=-cc;
    }
    bool dijkstra()
    {
        int i,x,y,dd;
        for (i=0;i<=t;i++) dist[i]=INF;
        dist[0]=0;q.push(mp(0,0));
        while (!q.empty())
        {
            x=q.top().y;dd=-q.top().x;q.pop();
            if (dd>dist[x]) continue;
            for (i=head[x];i;i=nxt[i])
            {
                y=to[i];
                if (f[i] && dist[x]+w[i]+h[x]-h[y]<dist[y])
                {
                    dist[y]=dist[x]+w[i]+h[x]-h[y];
                    prevv[y]=x;preve[y]=i;
                    q.push(mp(-dist[y],y));
                }
            }
        }
        if (dist[t]>=INF) return false; else return true;
    }
    Pair min_cost_flow()
    {
        int i,u,res,minf;
        for (i=0;i<=t;i++) h[i]+=dist[i];
        minf=INF;
        for (u=t;u;u=prevv[u]) minf=min(minf,f[preve[u]]);
        res=minf*h[t];
        for (u=t;u;u=prevv[u])
        {
            f[preve[u]]-=minf;
            f[preve[u]^1]+=minf;
        }
        return mp(minf,res);
    }
    inline Pair solve()
    {
        Pair ans=mp(0,0);
        while (dijkstra())
        {
            Pair res=min_cost_flow();
            ans.x+=res.x;ans.y+=res.y;
        }
        return ans;
    }
};

int n,tx,ty;
vector<int> v[148];int fa[148];
int dp[148][148];

namespace DSU
{
    int pre[148];
    inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
    inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

inline bool check_taboo(int x,int y) {return (x==tx && y==ty) || (x==ty && y==tx);}

inline void dfs(int cur,int father)
{
    fa[cur]=father;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (!check_taboo(cur,y) && y!=father) dfs(y,cur);
    }
}

inline int solve(int root1,int root2)
{
    if (dp[root1][root2]!=-1) return dp[root1][root2];
    Flow A;A.init(n+1);
    bool v1[148],v2[148];for (register int i=1;i<=n;i++) v1[i]=v2[i]=false;
    for (register int i=0;i<int(v[root1].size());i++)
    {
        int x=v[root1][i];
        if (x!=fa[root1] && !check_taboo(root1,x))
        for (register int j=0;j<int(v[root2].size());j++)
        {
            int y=v[root2][j];
            if (y!=fa[root2] && !check_taboo(root2,y))
            {
                int val=solve(x,y);A.addedge(x,y,1,n*2-val);
                v1[x]=true;v2[y]=true;
            }
        }
    }
    for (register int i=1;i<=n;i++) if (v1[i]) A.addedge(0,i,1,0);
    for (register int i=1;i<=n;i++) if (v2[i]) A.addedge(i,A.t,1,0);
    // Pair res=A.zkw();
    Pair res=A.solve();
    res.y=-res.y;res.y+=n*2*res.x;
    dp[root1][root2]=res.y+1;
    return dp[root1][root2];
}

class DeerInZooDivOne
{
    public:
        inline int getmax(vector<int> A,vector<int> B)
        {
            n=int(A.size())+1;for (register int i=1;i<=n;i++) v[i].clear();
            for (register int i=0;i<n-1;i++) A[i]++,B[i]++;
            for (register int i=0;i<n-1;i++) v[A[i]].pb(B[i]),v[B[i]].pb(A[i]);
            int ans=0;
            for (register int tedge=0;tedge<n-1;tedge++)
            {
                tx=A[tedge];ty=B[tedge];
                DSU::init();for (register int i=0;i<n-1;i++) if (i!=tedge) DSU::update(A[i],B[i]);
                for (register int rt1=1;rt1<=n;rt1++)
                    for (register int rt2=1;rt2<=n;rt2++)
                        if (DSU::find_anc(rt1)!=DSU::find_anc(rt2))
                        {
                            // cerr<<tedge<<' '<<rt1<<' '<<rt2<<endl;
                            dfs(rt1,-1);dfs(rt2,-1);
                            memset(dp,-1,sizeof(dp));
                            check_max(ans,solve(rt1,rt2));
                        }
            }
            return ans;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
    int n,x;vector<int> AA,BB;
    DeerInZooDivOne A;
    while (cin>>n)
    {
        AA.clear();BB.clear();
        for (register int i=1;i<=n-1;i++) cin>>x,AA.pb(x);
        for (register int i=1;i<=n-1;i++) cin>>x,BB.pb(x);
        cout<<A.getmax(AA,BB)<<endl;
    }
    io.flush();
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
    return 0;
}
#endif