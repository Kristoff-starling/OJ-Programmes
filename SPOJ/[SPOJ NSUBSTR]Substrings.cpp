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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=250000;

char s[MAXN+48];int len;
vector<int> v[MAXN*2];

namespace SAM
{
	int root,last,nxt[MAXN*2][27],par[MAXN*2],minn[MAXN*2],maxn[MAXN*2],sz[MAXN*2],tot=0;
	inline void init () {root=last=++tot;}
	inline void insert(char ch)
	{
		int p=last,np=++tot,w=ch-'a'+1;sz[np]=1;maxn[np]=maxn[p]+1;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p)
			par[np]=root;
		else
		{
			int q=nxt[p][w];
			if (maxn[q]==maxn[p]+1)
				par[np]=q;
			else
			{
				int nq=++tot;maxn[nq]=maxn[p]+1;
				memcpy(nxt[nq]+1,nxt[q]+1,26*sizeof(int));
				par[nq]=par[q];par[q]=nq;par[np]=nq;
				while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
			}
		}
		last=np;
	}
}

using namespace SAM;

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=len+10;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		pre[x]=y;
	}
}

inline void dfs(int cur)
{
	for (register int i=0;i<int(v[cur].size());i++)
		dfs(v[cur][i]),sz[cur]+=sz[v[cur][i]];
}

int ans[MAXN+48],seq[MAXN*2];

inline bool cmp(int x,int y) {return sz[x]>sz[y];}

int main ()
{
	int i;scanf("%s",s+1);len=strlen(s+1);
	init();for (i=1;i<=len;i++) insert(s[i]);
	for (i=2;i<=tot;i++) minn[i]=maxn[par[i]]+1;
	for (i=2;i<=tot;i++) v[par[i]].pb(i);
	dfs(1);
	for (i=2;i<=tot;i++) seq[i-1]=i;
	sort(seq+1,seq+tot,cmp);
	DSU::init();
	for (i=1;i<=tot-1;i++)
	{
		int pt=DSU::find_anc(minn[seq[i]]);
		while (pt<=maxn[seq[i]])
		{
			ans[pt]=sz[seq[i]];
			DSU::update(pt,pt+1);
			pt=DSU::find_anc(pt);
		}
	}
	for (i=1;i<=len;i++) printf("%d\n",ans[i]);
	return 0;
}
