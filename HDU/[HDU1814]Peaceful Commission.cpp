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
const int MOD=1e9+7;
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

int n,e;
vector<int> v[MAXN+48];

inline int getanother(int x)
{
	if (x&1) return x+1; else return x-1;
}

inline int getind(int cur) {return (cur+1)/2;}

bool visited[MAXN+48];
int path[MAXN+48];int ptot;

inline bool check(int cur)
{
	visited[cur]=true;int i,y;path[++ptot]=cur;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (visited[y]) continue;
		if (visited[getanother(y)]) return false;
		if (!check(y)) return false;
	}
	return true;
}

int main ()
{
	int i,j,x,y;
	while (scanf("%d%d",&n,&e)!=EOF)
	{
		for (i=1;i<=n*2;i++) visited[i]=false,v[i].clear();
		for (i=1;i<=e;i++)
		{
			x=getint();y=getint();
			v[x].pb(getanother(y));
			v[y].pb(getanother(x));
		}
		bool f=true;
		for (i=1;i<=n;i++)
		{
			if (visited[i*2-1] || visited[i*2]) continue;
			ptot=0;
			if (check(i*2-1)) continue;
			for (int j=1;j<=ptot;j++) visited[path[j]]=false;
			ptot=0;
			if (check(i*2)) continue; else {f=false;break;}
		}
		if (!f) printf("NIE\n"); else for (i=1;i<=n*2;i++) if (visited[i]) printf("%d\n",i);
	}
	return 0;
}
