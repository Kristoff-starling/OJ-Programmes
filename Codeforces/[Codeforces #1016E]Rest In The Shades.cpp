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
#define pii pair<LB,LB>

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

inline LB myabs(LB x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(LB x,LB y) {return x-y>eps;}
inline bool issmaller(LB x,LB y) {return x-y<-eps;}
inline bool isequal(LB x,LB y) {return myabs(x-y)<eps;}

const int MAXN=2e5;

pii a[MAXN+48];int n;
LB len[MAXN+48],sum[MAXN+48];

LB sy,A,B;int q;

inline LB getpos(pii pt1,pii pt2,LB Y)
{
	if (isequal(pt1.x,pt2.x)) return pt1.x;
	LB k=(pt2.y-pt1.y)/(pt2.x-pt1.x),b=pt1.y-k*pt1.x;
	return (Y-b)/k;
}

inline int bsearch1(pii pt)
{
	int l=1,r=n,mid,res=n+1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (!issmaller(getpos(pt,mp(a[mid].x,0),sy),A)) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

inline int bsearch2(pii pt)
{
	int l=1,r=n,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (!islarger(getpos(pt,mp(a[mid].y,0),sy),B)) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

LB ans;

inline void doit1(pii pt1,pii pt)
{
	LB res=getpos(pt1,pt,sy);
	if (!islarger(res,A)) return;
	ans+=res-A;
}

inline void doit2(pii pt1,pii pt)
{
	LB res=getpos(pt1,pt,sy);
	if (!issmaller(res,B)) return;
	ans+=B-res;
}

int main ()
{
	sy=getint();A=getint();B=getint();
	n=getint();int i;
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint(),len[i]=a[i].y-a[i].x;
	sum[0]=0;for (i=1;i<=n;i++) sum[i]=sum[i-1]+len[i];
	q=getint();LB x,y;
	while (q--)
	{
		x=getint();y=getint();
		int pos1=bsearch1(mp(x,y)),pos2=bsearch2(mp(x,y));
		ans=(sum[pos2]-sum[pos1-1])/y*(y-sy);
		if (pos1>1) doit1(mp(a[pos1-1].y,0),mp(x,y));
		if (pos2<n) doit2(mp(a[pos2+1].x,0),mp(x,y));
		double aa=ans;
		printf("%.15lf\n",aa);
	}
	return 0;
}
