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

struct Edge
{
	int x,y;LL c;
	inline void input() {x=getint()+1;y=getint()+1;c=getint();}
}edge[MAXN+48];

int minroot;

namespace zhuliu
{
	LL in[MAXN+48];int pre[MAXN+48],bel[MAXN+48];int cirind,tot,i,u,v;
	int visited[MAXN+48];
	inline LL solve(int root)
	{
		tot=n;LL res=0;
		while (true)
		{
			for (i=1;i<=tot;i++) in[i]=LINF;
			for (i=1;i<=e;i++)	
				if (edge[i].x!=edge[i].y && in[edge[i].y]>edge[i].c)
				{
					in[edge[i].y]=edge[i].c;
					pre[edge[i].y]=edge[i].x;
					if (edge[i].x==root) minroot=i;
				}
			for (i=1;i<=tot;i++) if (i!=root && in[i]==LINF) return -1;
			in[root]=0;cirind=0;
			memset(visited,0,sizeof(visited));
			memset(bel,0,sizeof(bel));
			for (i=1;i<=tot;i++)
			{
				res+=in[i];
				v=i;while (visited[v]!=i && v!=root && !bel[v]) visited[v]=i,v=pre[v];
				if (v!=root && !bel[v])
				{
					++cirind;u=pre[v];
					while (u!=v) bel[u]=cirind,u=pre[u];
					bel[u]=cirind;
				}
			}
			if (!cirind) break;
			for (i=1;i<=tot;i++) if (!bel[i]) bel[i]=++cirind;
			for (i=1;i<=e;i++)
			{
				v=edge[i].y;
				edge[i].x=bel[edge[i].x];edge[i].y=bel[edge[i].y];
				if (edge[i].x!=edge[i].y) edge[i].c-=in[v];
			}
			tot=cirind;root=bel[root];
		}
		return res;
	}
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i;LL sum=0;
	while (scanf("%d%d",&n,&e)!=EOF)
	{
		sum=0;
		for (i=1;i<=e;i++) edge[i].input(),sum+=edge[i].c;
		for (i=1;i<=n;i++) edge[++e].x=n+1,edge[e].y=i,edge[e].c=sum+1;
		n++;
		LL res=zhuliu::solve(n);
		if (res==-1 || res>=(sum+1)*2) {puts("impossible\n");continue;}
		res-=(sum+1);
		printf("%lld %d\n\n",res,minroot-(e-(n-1))-1);
	}
	return 0;
}
