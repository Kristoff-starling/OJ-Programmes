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

const int MAXN=2e5;
const int N=480;

typedef bitset<MAXN+48> bs;

int n,m,k;
Pair a[MAXN+48];
vector<int> v[MAXN+48];
vector<int> info[MAXN+48];
bool visited[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];bool exist[MAXN+48];
	inline void init ()
	{
		for (register int i=1;i<=n;i++)
		{
			pre[i]=i;
			if (int(v[i].size())) exist[i]=true; else exist[i]=false;
		}
	}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		pre[x]=y;if (exist[x]) exist[y]=true;
	}
}

int main ()
{
	int i,j;
	n=getint();m=getint();k=getint();
	for (i=1;i<=k;i++) a[i].x=getint(),a[i].y=getint(),v[a[i].x].pb(a[i].y),info[a[i].y].pb(a[i].x),visited[a[i].y]=true;
	DSU::init();
	for (i=1;i<=m;i++)
		for (j=1;j<int(info[i].size());j++)
			DSU::update(info[i][0],info[i][j]);
	int cnt=0;
	for (i=1;i<=n;i++)
		if (DSU::find_anc(i)==i && DSU::exist[i]) cnt++;
	cnt--;
	for (i=1;i<=m;i++) if (!visited[i]) cnt++;
	for (i=1;i<=n;i++) if (!int(v[i].size())) cnt++;
	printf("%d\n",cnt);
	return 0;
}
