#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
    bool f;char ch;T res;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=5000;

int n,m;
vector<int> v[MAXN+48];
Pair edge[MAXN+48];

inline int getanother(int x,int id)
{
    if (edge[id].x==x) return edge[id].y; else return edge[id].x;
}

int clist[MAXN+48],tot;

int visited[MAXN+48],fa[MAXN+48],faedge[MAXN+48];
inline void dfs(int cur,int father)
{
    visited[cur]=1;fa[cur]=father;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=getanother(cur,v[cur][i]);
        if (!visited[y]) faedge[y]=v[cur][i],dfs(y,cur);
        else if (visited[y]==1 && y!=father)
        {
            tot=1;clist[1]=v[cur][i];
            int x=cur;while (x!=y) clist[++tot]=faedge[x],x=fa[x];
        }
    }
    visited[cur]=2;
}

int taboo;
int curans[MAXN+48],ans[MAXN+48],pt;

inline void Dfs(int cur,int father)
{
    curans[++pt]=cur;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        if (v[cur][i]==taboo) continue;
        int y=getanother(cur,v[cur][i]);
        if (y!=father) Dfs(y,cur);
    }
}

inline void go(int ct)
{
    pt=0;taboo=ct;Dfs(1,-1);
    bool f=true;
    for (register int i=1;i<=n;i++)
    {
        if (curans[i]<ans[i]) {f=true;break;}
        if (curans[i]>ans[i]) {f=false;break;}
    }
    if (f)
        for (register int i=1;i<=n;i++) ans[i]=curans[i];
}

int cid;
inline bool cmp(int x,int y)
{
    return getanother(cid,x)<getanother(cid,y);
}

int main ()
{
    Get(n);Get(m);int x,y;
    for (register int i=1;i<=m;i++)
    {
        Get(x);Get(y);
        v[x].pb(i);v[y].pb(i);
        edge[i]=mp(x,y);
    }
    for (register int i=1;i<=n;i++)
    {
        cid=i;
        sort(v[i].begin(),v[i].end(),cmp);
    }
    dfs(1,-1);ans[1]=INF;
    if (m==n-1) go(0);
    else
        for (register int i=1;i<=tot;i++) go(clist[i]);
    for (register int i=1;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
    return 0;
}