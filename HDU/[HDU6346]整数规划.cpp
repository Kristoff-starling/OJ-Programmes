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

const int INF=1e9;
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

const int MAXN=200;

int n;
int lx[MAXN+48],ly[MAXN+48];bool vx[MAXN+48],vy[MAXN+48];
int linkx[MAXN+48],linky[MAXN+48],pre[MAXN+48],slack[MAXN+48];
int ga[MAXN+48][MAXN+48];

inline void find_route(int &u)
{
	for (;u;swap(u,linkx[pre[u]]))
		linky[u]=pre[u];
}

int q[MAXN+48];
inline void bfs(int u)
{
	int head,tail,t;
	head=tail=1;q[1]=u;vx[u]=true;
	for (;;)
	{
		while (head<=tail)
		{
			u=q[head++];
			for (register int v=1;v<=n;v++)
			{
				if (vy[v] || (t=lx[u]+ly[v]-ga[u][v])>slack[v]) continue;
				pre[v]=u;
				if (!t)
				{
					if (!linky[v]) {find_route(v);return;}
					vy[v]=vx[q[++tail]=linky[v]]=true;
				}
				else slack[v]=t;
			}
		}
		int d=INF;
		for (register int i=1;i<=n;i++) if (!vy[i] && slack[i]<d) d=slack[u=i];
		for (register int i=1;i<=n;i++)
		{
			if (vx[i]) lx[i]-=d;
			if (vy[i]) ly[i]+=d; else slack[i]-=d;
		}
		if (!linky[u]) {find_route(u);return;}
		vy[u]=vx[q[++tail]=linky[u]]=true;
	}
}

inline void KM()
{
	memset(linkx,0,sizeof(linkx));memset(linky,0,sizeof(linky));memset(pre,0,sizeof(pre));
	for (register int i=1;i<=n;i++) lx[i]=-INF,ly[i]=0;
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			lx[i]=max(lx[i],ga[i][j]);
	for (register int i=1;i<=n;i++)
	{
		for (register int j=1;j<=n;j++) vx[j]=vy[j]=false,slack[j]=INF;
		bfs(i);
	}
}

int main ()
{
	int i,j,ca;ca=getint();int cc=0;
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				ga[i][j]=-getint();
		KM();
		LL ans=0;
		for (i=1;i<=n;i++) ans+=lx[i]+ly[i];
		ans=-ans;
		printf("Case #%d: %I64d\n",++cc,ans);
	}
	return 0;
}
