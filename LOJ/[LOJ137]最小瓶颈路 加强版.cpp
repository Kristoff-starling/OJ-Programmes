// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

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
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
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
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=5e5;

int n,m;

struct Edge
{
	int x,y,c;
	inline void input() {Get(x,y,c);}
	inline bool operator < (const Edge &other) const {return c<other.c;}
}edge[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];
	inline void Create(int id) {pre[id]=id;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {pre[x]=y;}
}

int fa[MAXN+48],depth[MAXN+48],in[MAXN+48],out[MAXN+48],val[MAXN+48],ind;vector<int> v[MAXN+48];
int seq[MAXN+48],tot;

inline void ex_kruskal()
{
	sort(edge+1,edge+m+1);ind=n;rep(i,1,n) val[i]=0,DSU::Create(i);
	for (register int cnt=0,i=1;i<=m && cnt<n-1;i++)
	{
		int x=edge[i].x,y=edge[i].y;x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (x==y) continue;
		++ind;DSU::Create(ind);fa[x]=fa[y]=ind;v[ind].pb(x);v[ind].pb(y);
		DSU::update(x,ind);DSU::update(y,ind);val[ind]=edge[i].c;cnt++;
	}
}

inline void dfs(int cur)
{
	in[cur]=++tot;seq[tot]=cur;
	for (auto y : v[cur]) depth[y]=depth[cur]+1,dfs(y),seq[++tot]=cur;
	out[cur]=tot;
}

int ST[MAXN+48][21],Log[MAXN+48];

inline void init_ST()
{
	rep(i,1,tot) ST[i][0]=seq[i];
	Log[0]=Log[1]=0;rep(i,2,tot) Log[i]=Log[i>>1]+1;
	rep(j,1,20) rep(i,1,tot)
	{
		ST[i][j]=ST[i][j-1];
		if (i+(1<<(j-1))<=tot && depth[ST[i][j]]>depth[ST[i+(1<<(j-1))][j-1]]) ST[i][j]=ST[i+(1<<(j-1))][j-1];
	}
}

inline int query_ST(int l,int r)
{
	int k=r-l+1,id1=ST[l][Log[k]],id2=ST[r-(1<<Log[k])+1][Log[k]];
	if (depth[id1]<depth[id2]) return id1; else return id2;
}

int q,A,B,C,P;

inline int rnd() {return A=(A*B+C)%P;}

inline int query_lca(int u,int v)
{
	if (in[u]>in[v]) swap(u,v);
	return query_ST(in[u],in[v]);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,m);rep(i,1,m) edge[i].input();
	ex_kruskal();depth[ind]=1;dfs(ind);init_ST();
	Get(q,A,B,C,P);int x,y,ans=0;
	while (q--)
	{
		x=rnd()%n+1;y=rnd()%n+1;
		Add(ans,val[query_lca(x,y)]);
	}
	printf("%d\n",ans);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
