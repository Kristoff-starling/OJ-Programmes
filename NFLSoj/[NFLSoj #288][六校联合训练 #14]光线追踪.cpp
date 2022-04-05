#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;
const int MAXM=4e5;

int q;

struct Operation
{
	int op,x1,y1,x2,y2;
	int l1,r1,l2,r2;
	inline void input()
	{
		Get(op);
		if (op==1) Get(x1),Get(y1),Get(x2),Get(y2); else Get(x1),Get(y1);
	}
}a[MAXN+48];

double pos[MAXM+48];int ptot;

inline double calc_k(LB x,LB y)
{
	if (x==0) return 1e9+7; else return y/x;
}

struct SegmentTree
{
	int minn[MAXM*4],minid[MAXM*4];
	inline void build(int cur,int l,int r)
	{
		minn[cur]=INF;minid[cur]=0;
		if (l!=r)
		{
			int mid=(l+r)>>1;
			build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
		}
	}
	inline void update(int cur,int left,int right,int nv,int nid,int l,int r)
	{
		if (left<=l && r<=right)
		{
			if (nv<minn[cur] || (nv==minn[cur] && nid>minid[cur])) minn[cur]=nv,minid[cur]=nid;
			return;
		}
		int mid=(l+r)>>1;
		if (left<=mid) update(cur<<1,left,right,nv,nid,l,mid);
		if (mid+1<=right) update(cur<<1|1,left,right,nv,nid,mid+1,r);
	}
	inline Pair query(int cur,int pos,int l,int r)
	{
		if (l==r) return mp(minn[cur],minid[cur]);
		int mid=(l+r)>>1;Pair res=mp(minn[cur],minid[cur]),res1;
		if (pos<=mid) res1=query(cur<<1,pos,l,mid); else res1=query(cur<<1|1,pos,mid+1,r);
		if (res1.x<res.x || (res1.x==res.x && res1.y>res.y)) res=res1;
		return res;
	}
}row,col;

int main ()
{
	Get(q);
	for (register int i=1;i<=q;i++)
	{
		a[i].input();int x1=a[i].x1,y1=a[i].y1,x2=a[i].x2,y2=a[i].y2;
		if (a[i].op==1)
		{
			double cur=calc_k(x1,y1);pos[++ptot]=cur;
			cur=calc_k(x1,y2);pos[++ptot]=cur;
			cur=calc_k(x2,y1);pos[++ptot]=cur;
		}
		else
		{
			double cur=calc_k(x1,y1);pos[++ptot]=cur;
		}
	}
	sort(pos+1,pos+ptot+1);
	ptot=unique(pos+1,pos+ptot+1)-(pos+1);
	for (register int i=1;i<=q;i++)
	{
		int x1=a[i].x1,y1=a[i].y1,x2=a[i].x2,y2=a[i].y2;
		if (a[i].op==1)
		{
			a[i].l1=lower_bound(pos+1,pos+ptot+1,calc_k(x2,y1))-pos;
			a[i].r1=lower_bound(pos+1,pos+ptot+1,calc_k(x1,y1))-pos;
			a[i].l2=a[i].r1;
			a[i].r2=lower_bound(pos+1,pos+ptot+1,calc_k(x1,y2))-pos;
		}
		else
		{
			a[i].l1=lower_bound(pos+1,pos+ptot+1,calc_k(x1,y1))-pos;
		}
	}
	row.build(1,1,ptot);col.build(1,1,ptot);
	for (register int i=1;i<=q;i++)
		if (a[i].op==1)
		{
			row.update(1,a[i].l1,a[i].r1,a[i].y1,i,1,ptot);
			col.update(1,a[i].l2,a[i].r2,a[i].x1,i,1,ptot);
		}
		else
		{
			if (a[i].x1==0)
			{
				Pair res=row.query(1,a[i].l1,1,ptot);
				if (res.x>=INF) printf("0\n"); else printf("%d\n",res.y);
				continue;
			}
			if (a[i].y1==0)
			{
				Pair res=col.query(1,a[i].l1,1,ptot);
				if (res.x>=INF) printf("0\n"); else printf("%d\n",res.y);
				continue;
			}
			Pair res1=row.query(1,a[i].l1,1,ptot),res2=col.query(1,a[i].l1,1,ptot);
			if (res1.x>=INF && res2.x>=INF) printf("0\n");
			else
			{
				LL Y1=1ll*res1.x*a[i].x1,Y2=1ll*res2.x*a[i].y1;
				if (Y1<Y2) printf("%d\n",res1.y);
				else if (Y1>Y2) printf("%d\n",res2.y);
				else printf("%d\n",max(res1.y,res2.y));
			}
		}
	return 0;
}