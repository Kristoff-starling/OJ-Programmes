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

inline char Getchar()
{
	char ch;
	while (!isalpha(ch=getchar())) {}
	return ch;
}

const int MAXN=100;

int n,m;
int ans[MAXN+48];

struct Edge
{
	int x,y,c;
	Edge () {}
	inline Edge (int xx,int yy,int cc) {x=xx;y=yy;c=cc;}
	inline bool operator < (const Edge &other) const {return c<other.c;}
}r[MAXN+48],g[MAXN+48],b[MAXN+48],a[MAXN+48],aa[MAXN+48];
int rtot,gtot,btot,tot,atot;
bool used[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];
	inline void init () {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

int main ()
{
	int i,ca,x,y,c;char type;ca=getint();int cc=0;
	while (ca--)
	{
		n=getint();m=getint();
		printf("Case #%d:\n",++cc);
		rtot=gtot=btot=0;
		for (i=1;i<=m;i++)
		{
			x=getint();y=getint();c=getint();type=Getchar();
			if (type=='R') r[++rtot]=Edge(x,y,c);
			if (type=='G') g[++gtot]=Edge(x,y,c);
			if (type=='B') b[++btot]=Edge(x,y,c);
		}
		for (i=1;i<=m;i++) ans[i]=INF;
		tot=0;
		for (i=1;i<=rtot;i++) a[++tot]=r[i];
		for (i=1;i<=gtot;i++) a[++tot]=g[i];
		sort(a+1,a+tot+1);DSU::init();memset(used,false,sizeof(used));
		int cnt=0,sum=0;
		for (i=1;i<=tot;i++)
			if (DSU::find_anc(a[i].x)!=DSU::find_anc(a[i].y))
			{
				cnt++;
				DSU::update(a[i].x,a[i].y);sum+=a[i].c;
				used[i]=true;
				if (cnt==n-1) break;
			}
		if (cnt==n-1)
		{
			ans[n-1]=min(ans[n-1],sum);
			atot=0;
			for (i=1;i<=tot;i++)
				if (!used[i]) aa[++atot]=a[i];
			for (i=1;i<=btot;i++) aa[++atot]=b[i];
			sort(aa+1,aa+atot+1);
			for (i=1;i<=atot;i++)
				sum+=aa[i].c,ans[n-1+i]=min(ans[n-1+i],sum);
		}
		tot=0;
		for (i=1;i<=btot;i++) a[++tot]=b[i];
		for (i=1;i<=gtot;i++) a[++tot]=g[i];
		sort(a+1,a+tot+1);DSU::init();memset(used,false,sizeof(used));
		cnt=0;sum=0;
		for (i=1;i<=tot;i++)
			if (DSU::find_anc(a[i].x)!=DSU::find_anc(a[i].y))
			{
				cnt++;
				DSU::update(a[i].x,a[i].y);sum+=a[i].c;
				used[i]=true;
				if (cnt==n-1) break;
			}
		if (cnt==n-1)
		{
			ans[n-1]=min(ans[n-1],sum);
			atot=0;
			for (i=1;i<=tot;i++)
				if (!used[i]) aa[++atot]=a[i];
			for (i=1;i<=rtot;i++) aa[++atot]=r[i];
			sort(aa+1,aa+atot+1);
			for (i=1;i<=atot;i++)
				sum+=aa[i].c,ans[n-1+i]=min(ans[n-1+i],sum);
		}
		for (i=1;i<=m;i++) if (ans[i]>=INF) puts("-1"); else printf("%d\n",ans[i]);
	}
	return 0;
}
