#include <bits/stdc++.h>
#define LL long long
#define LB long double 
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m,c;

struct Edge
{
	int u,v,level;
}edge[100048];
int w[148];

vector<int> v[248];
int dist[248];

struct Matrix
{
	bitset<188> b[188];
	inline void I()
	{
		for (register int i=1;i<=n;i++) b[i][i]=1;
	}
	inline void Clear() {for (register int i=1;i<=n;i++) b[i]=0;}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res,other;int i,j;
		bitset<188> cur;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				other.b[i][j]=ma.b[j][i];
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
			{
				cur=b[i]&other.b[j];
				res.b[i][j]=(cur.any()?1:0);
			}
		return res;
	}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;int i;
		for (i=1;i<=n;i++) res.b[i]=b[i]|ma.b[i];
		return res;
	}
}trans,cc,pre;

inline Matrix quick_pow(Matrix ma,LL y)
{
	Matrix res;res.I();
	while (y)
	{
		if (y&1) res=res*ma,y--;
		ma=ma*ma;y>>=1;
	}
	return res;
}

queue<int> q;
inline void bfs()
{
	int i,x,y;
	for (i=1;i<=n;i++) dist[i]=INF;
	for (i=1;i<=n;i++) if (pre.b[1][i]) dist[i]=0,q.push(i);
	while (!q.empty())
	{
		x=q.front();q.pop();
		for (i=0;i<int(v[x].size());i++)
		{
			y=v[x][i];
			if (dist[y]>=INF)
			{
				dist[y]=dist[x]+1;
				q.push(y);
			}
		}
	}
}

int main ()
{
	int i,j;
	n=getint();m=getint();c=getint();
	for (i=1;i<=m;i++)
	{
		edge[i].u=getint();edge[i].v=getint();
		edge[i].level=getint();
	}
	m++;edge[i].u=edge[i].v=n;edge[i].level=1;
	for (i=1;i<=c;i++) w[i]=getint();
	if (n>1 && w[1]) {printf("Impossible\n");return 0;}
	cc.b[1][1]=1;
	for (i=1;i<=c-1;i++)
	{
		trans.Clear();
		for (j=1;j<=m;j++) if (edge[j].level<=i) trans.b[edge[j].u][edge[j].v]=1;
		trans=quick_pow(trans,w[i+1]-w[i]);pre=cc;cc=cc*trans;
		if (cc.b[1][n]==1) break;
	}
	int reachable=i;
	if (reachable==c) pre=cc;
	for (i=1;i<=m;i++) if (edge[i].level<=reachable) v[edge[i].u].pb(edge[i].v);
	bfs();
	if (dist[n]>=INF)
		printf("Impossible\n");
	else
		printf("%d\n",w[reachable]+dist[n]);
	return 0;
}
