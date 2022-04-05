//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
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
const int MOD=998244353;
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T Mul(T &x,T y) {x=mul(x,y);}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

const int MAXN=3e5;

int n,q;char s[MAXN+48];
int anc[MAXN+48][21],son[MAXN+48],level[MAXN+48],depth[MAXN+48];
int top[MAXN+48],Len[MAXN+48];vector<int> down[MAXN+48],up[MAXN+48];
int hbit[MAXN+48];

int head[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],tot;
inline void addedge(int s,int t) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;}

const int p=41;
int hsh1[MAXN+48],hsh2[MAXN+48],pw[MAXN+48],ipw[MAXN+48];

inline void dfs(int cur,int father)
{
	hsh1[cur]=add(mul(hsh1[father],p)+s[cur]-'a'+1);depth[cur]=depth[father]+1;hsh2[cur]=add(hsh2[father]+mul(pw[depth[cur]-1],s[cur]-'a'+1));
	anc[cur][0]=father;rep(i,1,20) anc[cur][i]=anc[anc[cur][i-1]][i-1];
	son[cur]=0;level[cur]=depth[cur];
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=father)
		{
			dfs(y,cur);
			if (!son[cur] || level[cur]<level[y]) son[cur]=y,level[cur]=level[y];
		}
	}
}

inline void dfs2(int cur,int tp)
{
	top[cur]=tp;down[tp].pb(cur);Len[tp]=depth[cur]-depth[tp]+1;
	if (son[cur]) dfs2(son[cur],tp);
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=anc[cur][0] && y!=son[cur]) dfs2(y,y);
	}
}

inline void getUp()
{
	rep(i,1,n)
		if (top[i]==i)
		{
			int L=Len[i],tmp=i;
			while (L && tmp!=1)
			{
				tmp=anc[tmp][0];
				up[i].pb(tmp);L--;
			}
		}
	int prod=262144,pw=18;
	REP(i,n,1)
	{
		while (prod>i) prod>>=1,pw--;
		hbit[i]=pw;
	}
}

inline int query_anc(int x,int k)
{
	if (k==0) return x;
	int y=top[anc[x][hbit[k]]];
	if (depth[x]-depth[y]<k) return up[y][k-(depth[x]-depth[y])-1]; else return down[y][depth[x]-depth[y]-k];
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	REP(i,20,0) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	REP(i,20,0) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline int query_hash1(int x,int y)
{
	int len=depth[y]-depth[x]+1;
	return sub(hsh1[y]-mul(hsh1[anc[x][0]],pw[len]));
}

inline int query_hash2(int x,int y)
{
	int len=depth[y]-1;
	return mul(sub(hsh2[x]-hsh2[anc[y][0]]),ipw[len]);
}

inline int calc_hash(int x,int y,int LCA,int len)
{
	int half=depth[x]-depth[LCA]+1;
	if (len<=half) return query_hash2(x,query_anc(x,len-1));
	int hsh1=query_hash2(x,LCA);len-=half;
	int tmp=depth[y]-depth[LCA],X=query_anc(y,tmp-1),Y=query_anc(y,tmp-len);ull hsh2=query_hash1(X,Y);
	len=depth[Y]-depth[X]+1;return add(mul(hsh1,pw[len])+hsh2);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);scanf("%s",s+1);int x,y,x1,y1;
	rep(i,1,n-1) Get(x,y),addedge(x,y),addedge(y,x);
	pw[0]=1;rep(i,1,n) pw[i]=mul(pw[i-1],p);
	ipw[n]=quick_pow(pw[n],MOD-2);REP(i,n-1,0) ipw[i]=mul(ipw[i+1],p);
	dfs(1,0);dfs2(1,1);getUp();
	Get(q);
	while (q--)
	{
		Get(x,y,x1,y1);int LCA1=getlca(x,y),LCA2=getlca(x1,y1);
		if (depth[x]+depth[y]-depth[LCA1]*2>depth[x1]+depth[y1]-depth[LCA2]*2) swap(x,x1),swap(y,y1),swap(LCA1,LCA2);
		int ans=0,l=1,r=depth[x]+depth[y]-depth[LCA1]*2+1,mid;
		while (l<=r)
		{
			mid=(l+r)>>1;
			int hsh1=calc_hash(x,y,LCA1,mid),hsh2=calc_hash(x1,y1,LCA2,mid);
			if (hsh1==hsh2) ans=mid,l=mid+1; else r=mid-1;
		}
		printf("%d\n",ans);
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
