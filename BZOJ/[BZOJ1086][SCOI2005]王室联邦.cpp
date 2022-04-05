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
const int MOD=998244353;
const int magic=348;
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

const int MAXN=1000;

int n,b;
vector<int> v[MAXN+48];
int ind=0;int bel[MAXN+48],centre[MAXN+48];
int sta[MAXN+48],stot;

inline void dfs(int cur,int father)
{
	sta[++stot]=cur;int spos=stot;
	int i,y;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			if (stot-spos>=b)
			{
				++ind;
				while (stot!=spos) bel[sta[stot--]]=ind;
				centre[ind]=cur;
			}
		}
	}
	if (stot-spos+1>=b)
	{
		++ind;
		while (stot!=spos) bel[sta[stot--]]=ind;
		bel[sta[stot--]]=ind;
		centre[ind]=cur;
	}
}

inline int Dfs(int cur,int father)
{
	if (bel[cur]) return bel[cur];
	for (register int i=0;i<int(v[cur].size());i++)
		if (v[cur][i]!=father)
		{
			int res=Dfs(v[cur][i],cur);
			if (res!=-1) return res;
		}
	return -1;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	n=getint();b=getint();
	if (n<b)
	{
		puts("0");
		return 0;
	}
	int i,x,y;
	for (i=1;i<=n-1;i++) x=getint(),y=getint(),v[x].pb(y),v[y].pb(x);
	dfs(1,-1);
	if (stot)
	{
		int Ind=Dfs(1,-1);
		for (i=1;i<=n;i++) if (!bel[i]) bel[i]=Ind;
	}
	printf("%d\n",ind);
	for (i=1;i<=n;i++) printf("%d ",bel[i]);puts("");
	for (i=1;i<=ind;i++) printf("%d ",centre[i]);puts("");
	return 0;
}
