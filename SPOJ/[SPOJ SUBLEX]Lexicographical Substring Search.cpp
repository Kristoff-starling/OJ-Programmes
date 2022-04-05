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

const int INF=2e9;
const LL LINf=2e16;
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

const int MAXN=1e5;

char s[MAXN+48];int len;

namespace SAM
{
	int nxt[MAXN*2][30],par[MAXN*2],maxn[MAXN*2],minn[MAXN*2],tot;
	int root,last;
	inline void init() {root=last=++tot;}
	inline void insert(char ch)
	{
		int p=last,np=++tot,w=ch-'a'+1;maxn[np]=maxn[p]+1;
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
				par[nq]=par[q];par[q]=par[np]=nq;
				while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
			}
		}
		last=np;
	}
}

using namespace SAM;

int sz[MAXN*2],sm[MAXN*2];

inline int dfs(int cur)
{
	if (sz[cur]!=-1) return sz[cur];
	if (cur!=1) sz[cur]=1;
	for (register int i=1;i<=26;i++)
		if (nxt[cur][i]) sz[cur]+=dfs(nxt[cur][i]);
	return sz[cur];
}

string ans;
inline void getans(int cur,int k)
{
	int i;if (cur!=1) k--;
	if (!k) return;
	for (i=1;i<=26;i++)
		if (nxt[cur][i])
		{
			if (sz[nxt[cur][i]]>=k) {ans+=string(1,'a'+i-1);getans(nxt[cur][i],k);return;}
			k-=sz[nxt[cur][i]];
		}
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i;scanf("%s",s+1);len=strlen(s+1);
	init();for (i=1;i<=len;i++) insert(s[i]);
	for (i=2;i<=tot;i++) minn[i]=maxn[par[i]]+1;
	memset(sz,-1,sizeof(sz));
	dfs(1);int q=getint(),k;
	while (q--)
	{
		k=getint();ans="";
		getans(1,k);cout<<ans<<endl;
	}
	return 0;
}
