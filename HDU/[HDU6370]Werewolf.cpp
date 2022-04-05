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

const int MAXN=1e5;

int n;
Pair a[MAXN+48];

int final[MAXN+48];
vector<int> v[MAXN+48];
bool visited[MAXN+48];

inline int solve(int x)
{
	if (a[x].y==1) return final[x]=a[x].x;
	if (final[x]) return final[x];
	final[x]=-1;
	final[x]=solve(a[x].x);
	return final[x];
}

inline void dfs(int cur)
{
	visited[cur]=true;
	for (register int i=0;i<int(v[cur].size());i++)
		if (!visited[v[cur][i]]) dfs(v[cur][i]);
}

int main ()
{
	char s[48];int x;
	int ca;ca=getint();
	while (ca--)
	{
		n=getint();
		for (register int i=1;i<=n;i++) v[i].clear();
		for (register int i=1;i<=n;i++)
		{
			scanf("%d%s",&x,s+1);
			if (s[1]=='w') a[i]=mp(x,1); else a[i]=mp(x,0),v[x].pb(i);
	 	}
		memset(final,0,sizeof(final));
		for (register int i=1;i<=n;i++) final[i]=solve(i);
		memset(visited,false,sizeof(visited));
		for (register int i=1;i<=n;i++) if (final[i]==i) dfs(i);
		int cnt=0;for (register int i=1;i<=n;i++) if (visited[i]) cnt++;
		printf("0 %d\n",cnt);
	}
	return 0;
}
