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

const int MAXN=5e4;

int n,q;

struct Operation
{
	int type;
	int l,r,x,ind;
}a[MAXN*2+48];int tot;
int ans[MAXN+48];

int val[MAXN+48];

vector<int> used;bool visited[MAXN+48];
namespace BIT
{
	int c[MAXN+48];
	inline void clear() {for (register int i=0;i<int(used.size());i++) visited[used[i]]=false,c[used[i]]=0;used.clear();}
	inline void update(int x,int delta) {while (x<=n) {c[x]+=delta;if (!visited[x]) visited[x]=true,used.pb(x);x+=LOWBIT(x);}}
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
	inline int calc(int left,int right) {return query(right)-query(left-1);}
}

Operation tmp1[MAXN+48],tmp2[MAXN+48];int tot1,tot2;
inline void solve(int left,int right,int l,int r)
{
	if (left>right) return;
	if (l==r)
	{
		for (register int i=left;i<=right;i++)
			if (a[i].type==3) ans[a[i].ind]=l;
		return;
	}
	int i,mid=(l+r)>>1;tot1=tot2=0;
	for (i=left;i<=right;i++)
	{
		if (a[i].type==1)
		{
			if (a[i].x<=mid) BIT::update(a[i].l,1),tmp1[++tot1]=a[i];
			else tmp2[++tot2]=a[i];
		}
		if (a[i].type==2)
		{
			if (a[i].x<=mid) BIT::update(a[i].l,-1),tmp1[++tot1]=a[i];
			else tmp2[++tot2]=a[i];
		}
		if (a[i].type==3)
		{
			int sum=BIT::calc(a[i].l,a[i].r);
			if (sum>=a[i].x) tmp1[++tot1]=a[i];
			else a[i].x-=sum,tmp2[++tot2]=a[i];
		}
	}
	BIT::clear();
	int border=left+tot1-1,pt=left;
	for (i=1;i<=tot1;i++) a[pt++]=tmp1[i];
	for (i=1;i<=tot2;i++) a[pt++]=tmp2[i];
	solve(left,border,l,mid);solve(border+1,right,mid+1,r);
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i,x,y,c,ca;ca=getint();char op[5];
	while (ca--)
	{
		n=getint();q=getint();
		for (i=1;i<=n;i++) a[i].type=1,a[i].x=getint(),a[i].l=i,val[i]=a[i].x;
		tot=n;
		for (i=1;i<=q;i++)
		{
			scanf("%s",op+1);
			if (op[1]=='C')
			{
				x=getint();y=getint();
				a[++tot].type=2;a[tot].l=x;a[tot].x=val[x];
				val[x]=y;
				a[++tot].type=1;a[tot].l=x;a[tot].x=val[x];
			}
			else
			{
				a[++tot].type=3;
				a[tot].l=getint();a[tot].r=getint();a[tot].x=getint();
				a[tot].ind=i;
			}
		}
		for (i=1;i<=q;i++) ans[i]=-1;
		solve(1,tot,0,1e9);
		for (i=1;i<=q;i++) if (ans[i]!=-1) printf("%d\n",ans[i]);
	}
	return 0;
}
