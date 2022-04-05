#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,q;
vector<Pair> v[100048];
vector<Pair> query[100048];
int ans[100048];bool taboo[100048];
int anc[100048][21],depth[100048];
int sz[100048];int LCA[100048];

const int p1=19260817,p2=998244353;
const int m1=1e9+7,m2=1e9+9;
LL pw1[100048],pw2[100048],ipw1[100048],ipw2[100048];
LL H1[100048],H2[100048],Hr1[100048],Hr2[100048];

inline LL quick_pow(LL x,LL y,LL MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=(res*x)%MO,y--;
		x=(x*x)%MO;y>>=1;
	}
	return x;
}
inline LL mod1(LL x) {while (x>=m1) x-=m1;while (x<0) x+=m1;return x;}
inline LL mod2(LL x) {while (x>=m2) x-=m2;while (x<0) x+=m2;return x;}
inline void init_hash()
{
	pw1[0]=pw2[0]=1;
	for (register int i=1;i<=n;i++)
	{
		pw1[i]=(pw1[i-1]*p1)%m1;pw2[i]=(pw2[i-1]*p2)%m2;
		ipw1[i]=quick_pow(pw1[i],m1-2,m1);ipw2[i]=quick_pow(pw2[i],m2-2,m2);
	}
}

inline void dfs(int cur,int father,int dep)
{
	depth[cur]=dep;int i,j,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			H1[y]=(H1[cur]*p1+v[cur][i].y)%m1;H2[y]=(H2[cur]*p2+v[cur][i].y)%m2;
			Hr1[y]=(Hr1[cur]+pw1[dep]*v[cur][i].y)%m1;Hr2[y]=(Hr2[cur]+pw2[dep]*v[cur][i].y)%m2;
			dfs(y,cur,dep+1);
		}
	}
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline int getup(int u,int len)
{
	for (register int i=20;i>=0;i--) if (len>=(1<<i)) u=anc[u][i],len-=(1<<i);
	return u;
}

inline void dfs(int cur,int father)
{
	sz[cur]=1;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father && !taboo[y]) dfs(y,cur),sz[cur]+=sz[y];
	}
}

inline int getroot(int cur,int Sz)
{
	int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (sz[y]>Sz/2) return getroot(y,Sz);
	}
	return cur;
}

struct node
{
	int num;
	int depth,nxt[30];
	LL h1,h2;
	inline void clear() {memset(nxt,0,sizeof(nxt));h1=h2=depth=num=0;}
}trie[100048];int tot=0;

inline void construct_trie(int tcur,int cur,int father)
{
	trie[tcur].num++;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father && !taboo[y]) 
		{
			if (!trie[tcur].nxt[v[cur][i].y-'a'+1])
			{
				trie[tcur].nxt[v[cur][i].y-'a'+1]=++tot;
				trie[tot].clear();trie[tot].depth=trie[tcur].depth+1;
				trie[tot].h1=(trie[tcur].h1*p1+v[cur][i].y)%m1;
				trie[tot].h2=(trie[tcur].h2*p2+v[cur][i].y)%m2;
			}
			construct_trie(trie[tcur].nxt[v[cur][i].y-'a'+1],y,cur);
		}
	}
}

int seq[100048],rnk[100048],ind;
inline void dfs_trie(int cur)
{
	if (cur!=1) seq[++ind]=cur;
	int i,y;
	for (i=1;i<=26;i++)
	{
		y=trie[cur].nxt[i];
		if (y) dfs_trie(y);
	}
}

inline LL gethash1(int u,int v,int LCA,int len)
{
	if (depth[u]-depth[LCA]<=len)
	{
		int uu=getup(u,len);
		return ((Hr1[u]-Hr1[uu])*ipw1[depth[uu]])%m1;
	}
	LL res=((Hr1[u]-Hr1[LCA])*ipw1[depth[LCA]])%m1,leftlen=len-(depth[u]-depth[LCA]);
	int tmp=depth[v]-depth[LCA]-leftlen,uu=getup(v,tmp);
	LL res2=mod1(H1[uu]-(H1[LCA]*pw1[leftlen])%m1);
	return (res*pw1[leftlen]+res2)%m1;
}

inline LL gethash2(int u,int v,int LCA,int len)
{
	if (depth[u]-depth[LCA]<=len)
	{
		int uu=getup(u,len);
		return ((Hr2[u]-Hr2[uu])*ipw2[depth[uu]])%m2;
	}
	LL res=((Hr2[u]-Hr2[LCA])*ipw2[depth[LCA]])%m2,leftlen=len-(depth[u]-depth[LCA]);
	int tmp=depth[v]-depth[LCA]-leftlen,uu=getup(v,tmp);
	LL res2=mod2(H2[uu]-(H2[LCA]*pw2[leftlen])%m2);
	return (res*pw2[leftlen]+res2)%m2;
}

inline int Getup(int u,int len)
{
	for (register int i=20;i>=0;i--) if (len>=(1<<i)) u=Anc[u][i],len-=(1<<i);
	return u;
}

int Anc[100048][21];
LL h1[100048],h2[100048];int d[100048];
inline void Dfs(int cur,int father)
{
	int i,j,y;
	for (i=0;i<int(query[cur].size());i++)
	{
		int len=depth[cur]+depth[query[cur].x]-2*depth[LCA[query[cur].y]];
		if (len<=d[cur]-1)
		{
			int l=1,r=len,mid,mmatch=0;
			while (l<=r)
			{
				mid=(l+r)>>1;
				LL hsh1=gethash1(cur,query[cur].x,LCA[query[cur].y],mid),hsh2=gethash2(cur,query[cur].x,LCA[query[cur].y],mid);
				int uu=Getup(cur,mid);
				LL Hsh1=(mod1(h1[cur]-h1[uu])*ipw1[d[uu]])%m1,Hsh2=(mod2(h2[cur]-h2[uu])*ipw2[d[uu]])%m2;
				if (hsh1==Hsh1 && hsh2==Hsh2) mmatch=mid,l=mid+1; else r=mid-1;
			}
		}
	}
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father && !taboo[y])
		{
			d[y]=d[cur]+1;
			Anc[j][0]=cur;
			for (j=1;j<=20;j++) Anc[y][j]=Anc[Anc[y][j-1]][j-1];
			h1[y]=(h1[cur]+pw1[cur]*v[cur][i].y)%m1;
			h2[y]=(h2[cur]+pw2[cur]*v[cur][i].y)%m2;
			Dfs(y,cur);
		}
	}
}

inline void solve(int cur)
{
	dfs(cur,-1);cur=getroot(cur,sz[cur]);
	tot=1;trie[1].clear();trie[1].depth=1;construct_trie(tot,cur,-1);
	ind=0;dfs_trie(1);
	rnk[1]=0;for (i=2;i<=ind;i++) rnk[i]=rnk[i-1]+trie[seq[i-1]].num;
	h[cur]=0;d[cur]=0;Dfs(cur,-1);
}

int main ()
{
	n=getint();q=getint();int i,x,y;char c;
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();scanf("%c",&c);
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	init_hash();dfs(1,-1,1);
	for (i=1;i<=q;i++)
	{
		x=getint();y=getint();
		query[x].pb(mp(y,i));
		LCA[i]=getlca(x,y);
	}
	solve(1);
	for (i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
