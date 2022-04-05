#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <iomanip>
#include <bitset>
#include <cmath>
#include <functional>
#include <sstream>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
vector<int> v[100048];
LL val[100048];

inline LL mod(LL x,LL MO) {while (x>=MO) x-=MO;while (x<0) x+=MO;return x;}
inline LL gcd(LL x,LL y) {return y==0?x:gcd(y,x%y);}
inline LL myabs(LL x) {return x>=0?x:-x;}

inline LL quick_mul(LL x,LL y,LL MO)
{
	x%=MO;LL res=0;
	while (y)
	{
		if (y&1) res=mod(res+x,MO),y--;
		x=mod(x+x,MO);y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	x%=MO;LL res=1;
	while (y)
	{
		if (y&1) res=quick_mul(res,x,MO),y--;
		x=quick_mul(x,x,MO);y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y)
{
	LL res=1;
	while (y)
	{
		if (y&1) res*=x,y--;
		x*=x;y>>=1;
	}
	return res;
}

int lp[]={2,3,5,7,11,13,17,19,23,29,31,37};
LL x[148];
inline bool Miller_Rabin(LL n)
{
	int i;
	for (i=0;i<=11;i++)
	{
		if (n==lp[i]) return true;
		if (n%lp[i]==0) return false;
	}
	LL tmp=n-1;int k=0,ti=20;
	while (!(tmp&1)) k++,tmp>>=1;
	while (ti--)
	{
		LL a=rand()%(n-2)+2;
		x[0]=quick_pow(a,tmp,n);
		for (i=1;i<=k;i++)
		{
			x[i]=quick_mul(x[i-1],x[i-1],n);
			if (x[i]==1 && x[i-1]!=1 && x[i-1]!=n-1) return false;
		}
		if (x[k]!=1) return false;
	}
	return true;
}

inline LL pollard_rho(LL n,LL c)
{
	LL x=rand()%(n-1)+1,y=x,i=1,k=2;
	while (true)
	{
		i++;
		x=mod(quick_mul(x,x,n)+c,n);
		LL p=gcd(myabs(x-y),n);
		if (p!=1 && p!=n) return p;
		if (y==x) return n;
		if (i==k)
		{
			y=x;
			k<<=1;
		}
	}
	return n;
}

vector<LL> fac;
inline void findfac(LL n)
{
	if (n==1) return;
	if (Miller_Rabin(n)) {fac.pb(n);return;}
	LL p=n;
	while (p>=n) p=pollard_rho(n,rand()%(n-1));
	findfac(p);findfac(n/p);
}

LL p[48],pw[48];int ptot=0;
LL p1[48],pw1[48],p2[48],pw2[48];int p1tot,p2tot;

inline void Two()
{
	LL minn=LINF;int Mask;int pt1,pt2,i;
	for (Mask=0;Mask<=(1<<ptot)-1;Mask++)
	{
		pt1=pt2=1;
		for (i=1;i<=ptot;i++)
			if (Mask&(1<<(i-1))) pt1*=(pw[i]+1); else pt2*=(pw[i]+1);
		if (max(pt1,pt2)<minn)
		{
			minn=max(pt1,pt2);
			p1tot=p2tot=0;
			for (i=1;i<=ptot;i++)
				if (Mask&(1<<(i-1))) p1[++p1tot]=p[i],pw1[p1tot]=pw[i]; else p2[++p2tot]=p[i],pw2[p2tot]=pw[i];
		}
	}
}

LL val1[1000048],val2[1000048],v1tot,v2tot;
int cp[148];

inline void dfs1(int pos)
{
	if (pos==p1tot+1)
	{
		LL v=1;
		for (register int i=1;i<=p1tot;i++) v*=quick_pow(p1[i],cp[i]);
		val1[++v1tot]=v;
		return;
	}
	for (register int i=0;i<=pw1[pos];i++) cp[pos]=i,dfs1(pos+1);
}

inline void dfs2(int pos)
{
	if (pos==p2tot+1)
	{
		LL v=1;
		for (register int i=1;i<=p2tot;i++) v*=quick_pow(p2[i],cp[i]);
		val2[++v2tot]=v;
		return;
	}
	for (register int i=0;i<=pw2[pos];i++) cp[pos]=i,dfs2(pos+1);
}

int sum[2048][2048];
vector<int> vv1[2048],vv2[2048];
int dp[100048];
pLL Val[100048];

inline void dfs(int cur,int father)
{
	int pos1=lower_bound(val1+1,val1+v1tot+1,Val[cur].x)-val1;
	int pos2=lower_bound(val2+1,val2+v2tot+1,Val[cur].y)-val2;
	int i,y;
	if (cur==1)
		dp[cur]=1;
	else
	{
		dp[cur]=0;
		for (i=0;i<int(vv2[pos2].size());i++)
			dp[cur]=mod(dp[cur]+sum[pos1][vv2[pos2][i]],MOD);
	}
	for (i=0;i<int(vv1[pos1].size());i++)
		sum[vv1[pos1][i]][pos2]=mod(sum[vv1[pos1][i]][pos2]+dp[cur],MOD);
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) dfs(y,cur);
	}
	for (i=0;i<int(vv1[pos1].size());i++)
		sum[vv1[pos1][i]][pos2]=mod(sum[vv1[pos1][i]][pos2]-dp[cur],MOD);
}

int main ()
{
	int i,j,x,y;n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	for (i=1;i<=n;i++) val[i]=getLL();
	findfac(val[1]);
	sort(fac.begin(),fac.end());
	for (i=0;i<int(fac.size());i++)
	{
		if (i && fac[i]==fac[i-1]) {pw[ptot]++;continue;}
		p[++ptot]=fac[i];pw[ptot]=1;
	}
	Two();
	dfs1(1);sort(val1+1,val1+v1tot+1);
	for (i=1;i<=v1tot;i++)
		for (j=1;j<=i;j++)
			if (val1[i]%val1[j]==0) vv1[i].pb(j);
	dfs2(1);sort(val2+1,val2+v2tot+1);
	for (i=1;i<=v2tot;i++)
		for (j=i;j<=v2tot;j++)
			if (val2[j]%val2[i]==0) vv2[i].pb(j);
	for (i=1;i<=n;i++)
	{
		Val[i].x=1;LL tmp=val[i];
		for (j=1;j<=p1tot;j++)
			while (tmp%p1[j]==0) Val[i].x*=p1[j],tmp/=p1[j];
		Val[i].y=tmp;
	}
	dfs(1,-1);
	for (i=1;i<=n;i++) printf("%d\n",dp[i]);
	return 0;
}
