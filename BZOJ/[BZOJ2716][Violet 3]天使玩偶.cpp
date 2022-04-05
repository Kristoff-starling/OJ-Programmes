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

const int LIM=1e6+48;
const int MAXN=1e6;

int n,m;

struct BIT
{
#define LOWBIT(x) x & (-x)
	int c[LIM+48];
	inline void init() {for (register int i=1;i<=LIM;i++) c[i]=INF;}
	inline void clear(int x) {while (x<=LIM) c[x]=INF,x+=LOWBIT(x);}
	inline void update(int x,int newval) {while (x<=LIM) c[x]=min(c[x],newval),x+=LOWBIT(x);}
	inline int query(int x) {int res=INF;while (x) {res=min(res,c[x]),x-=LOWBIT(x);}return res;}
}MIN;

struct Query
{
	int op,x,y,ind;
	inline void input() {op=getint();x=getint()+1;y=getint()+1;}
}q[MAXN+48],tmp[MAXN+48],Q[MAXN+48];

int ans1[MAXN+48],ans2[MAXN+48],ans3[MAXN+48],ans4[MAXN+48],ans[MAXN+48],ind;Pair a[MAXN+48];
int history[MAXN+48],htot;

inline void cdq1(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq1(left,mid);cdq1(mid+1,right);
	int pt=0,k1,k2,i;htot=0;
	for (k1=left,k2=mid+1;k1<=mid && k2<=right;)
	{
		if (q[k1].x>=q[k2].x)
		{
			if (q[k1].op==1) MIN.update(LIM-q[k1].y,q[k1].x+q[k1].y),history[++htot]=LIM-q[k1].y;
			tmp[++pt]=q[k1++];
		}
		else
		{
			if (q[k2].op==2) ans1[q[k2].ind]=min(ans1[q[k2].ind],MIN.query(LIM-q[k2].y));
			tmp[++pt]=q[k2++];
		}
	}
	while (k1<=mid) tmp[++pt]=q[k1++];
	while (k2<=right)
	{
		if (q[k2].op==2) ans1[q[k2].ind]=min(ans1[q[k2].ind],MIN.query(LIM-q[k2].y));
		tmp[++pt]=q[k2++];
	}
	for (i=1;i<=htot;i++) MIN.clear(history[i]);
	for (i=left;i<=right;i++) q[i]=tmp[i-left+1];
}

inline void cdq2(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq2(left,mid);cdq2(mid+1,right);
	int pt=0,k1,k2,i;htot=0;
	for (k1=left,k2=mid+1;k1<=mid && k2<=right;)
	{
		if (q[k1].x<=q[k2].x)
		{
			if (q[k1].op==1) MIN.update(LIM-q[k1].y,-q[k1].x+q[k1].y),history[++htot]=LIM-q[k1].y;
			tmp[++pt]=q[k1++];
		}
		else
		{
			if (q[k2].op==2) ans2[q[k2].ind]=min(ans2[q[k2].ind],MIN.query(LIM-q[k2].y));
			tmp[++pt]=q[k2++];
		}
	}
	while (k1<=mid) tmp[++pt]=q[k1++];
	while (k2<=right)
	{
		if (q[k2].op==2) ans2[q[k2].ind]=min(ans2[q[k2].ind],MIN.query(LIM-q[k2].y));
		tmp[++pt]=q[k2++];
	}
	for (i=1;i<=htot;i++) MIN.clear(history[i]);
	for (i=left;i<=right;i++) q[i]=tmp[i-left+1];
}

inline void cdq3(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq3(left,mid);cdq3(mid+1,right);
	int pt=0,k1,k2,i;htot=0;
	for (k1=left,k2=mid+1;k1<=mid && k2<=right;)
	{
		if (q[k1].x<=q[k2].x)
		{
			if (q[k1].op==1) MIN.update(q[k1].y,-q[k1].x-q[k1].y),history[++htot]=q[k1].y;
			tmp[++pt]=q[k1++];
		}
		else
		{
			if (q[k2].op==2) ans3[q[k2].ind]=min(ans3[q[k2].ind],MIN.query(q[k2].y));
			tmp[++pt]=q[k2++];
		}
	}
	while (k1<=mid) tmp[++pt]=q[k1++];
	while (k2<=right)
	{
		if (q[k2].op==2) ans3[q[k2].ind]=min(ans3[q[k2].ind],MIN.query(q[k2].y));
		tmp[++pt]=q[k2++];
	}
	for (i=1;i<=htot;i++) MIN.clear(history[i]);
	for (i=left;i<=right;i++) q[i]=tmp[i-left+1];
}

inline void cdq4(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1;
	cdq4(left,mid);cdq4(mid+1,right);
	int pt=0,k1,k2,i;htot=0;
	for (k1=left,k2=mid+1;k1<=mid && k2<=right;)
	{
		if (q[k1].x>=q[k2].x)
		{
			if (q[k1].op==1) MIN.update(q[k1].y,q[k1].x-q[k1].y),history[++htot]=q[k1].y;
			tmp[++pt]=q[k1++];
		}
		else
		{
			if (q[k2].op==2) ans4[q[k2].ind]=min(ans4[q[k2].ind],MIN.query(q[k2].y));
			tmp[++pt]=q[k2++];
		}
	}
	while (k1<=mid) tmp[++pt]=q[k1++];
	while (k2<=right)
	{
		if (q[k2].op==2) ans4[q[k2].ind]=min(ans4[q[k2].ind],MIN.query(q[k2].y));
		tmp[++pt]=q[k2++];
	}
	for (i=1;i<=htot;i++) MIN.clear(history[i]);
	for (i=left;i<=right;i++) q[i]=tmp[i-left+1];
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i;n=getint();m=getint();
	for (i=1;i<=n;i++) q[i].op=1,q[i].x=getint()+1,q[i].y=getint()+1;
	for (i=1;i<=m;i++)
	{
		q[i+n].input();
		if (q[i+n].op==2) q[i+n].ind=++ind,a[ind]=mp(q[i+n].x,q[i+n].y);
	}
	for (i=1;i<=n+m;i++) Q[i]=q[i];
	//I
	for (i=1;i<=ind;i++) ans1[i]=INF;
	MIN.init();cdq1(1,n+m);
	for (i=1;i<=n+m;i++) q[i]=Q[i];
	//II
	for (i=1;i<=ind;i++) ans2[i]=INF;
	MIN.init();cdq2(1,n+m);
	for (i=1;i<=n+m;i++) q[i]=Q[i];
	//III
	for (i=1;i<=ind;i++) ans3[i]=INF;
	MIN.init();cdq3(1,n+m);
	for (i=1;i<=n+m;i++) q[i]=Q[i];
	//IV
	for (i=1;i<=ind;i++) ans4[i]=INF;
	MIN.init();cdq4(1,n+m);
	for (i=1;i<=n+m;i++) q[i]=Q[i];
	for (i=1;i<=ind;i++)
	{
		ans[i]=ans1[i]-a[i].x-a[i].y;
		ans[i]=min(ans[i],ans2[i]+a[i].x-a[i].y);
		ans[i]=min(ans[i],ans3[i]+a[i].x+a[i].y);
		ans[i]=min(ans[i],ans4[i]-a[i].x+a[i].y);
		printf("%d\n",ans[i]);
	}
	return 0;
}
