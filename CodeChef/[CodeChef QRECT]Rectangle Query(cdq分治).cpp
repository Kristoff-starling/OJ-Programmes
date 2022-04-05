#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
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

struct BIT
{
	int c[400048];
	inline void init() {memset(c,0,sizeof(c));}
	inline void update(int x,int lim,int delta) {while (x<=lim) c[x]+=delta,x+=LOWBIT(x);}
	inline void clear(int x,int lim) {while (x<=lim) c[x]=0,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
}up,down,lft,rght,CDQ;

struct Query
{
	int type;
	int x1,y1,x2,y2;
	int nx1,nx2,ny1,ny2;
}a[100048];

struct C
{
	int type;
	int x,y,ind;
}c[100048],tmp[100048];

struct point
{
	int val;
	int from;bool type;
	inline bool operator < (const point &x) const {return val<x.val;}
}b[500048];int btot;

int n,itot1,itot2;
int ind[100048],indtot=0;
int ans[100048];
int history[100048],htot;

inline void cdq(int left,int right)
{
	if (left==right) return;
	int mid=(left+right)>>1,k1,k2,pt;
	cdq(left,mid);cdq(mid+1,right);htot=0;
	for (k1=left,k2=mid+1,pt=left;k1<=mid && k2<=right;)
	{
		if (c[k1].x<=c[k2].x)
		{
			if (c[k1].type==1) CDQ.update(c[k1].y,itot2,1),history[++htot]=c[k1].y;
			if (c[k1].type==2) CDQ.update(c[k1].y,itot2,-1),history[++htot]=c[k1].y;
			tmp[pt++]=c[k1++];
		}
		else
		{
			if (c[k2].type==3) ans[c[k2].ind]+=CDQ.query(c[k2].y);
			tmp[pt++]=c[k2++];
		}
	}
	while (k1<=mid) tmp[pt++]=c[k1++];
	while (k2<=right)
	{
		if (c[k2].type==3) ans[c[k2].ind]+=CDQ.query(c[k2].y);
		tmp[pt++]=c[k2++];
	}
	for (register int i=left;i<=right;i++) c[i]=tmp[i];
	for (register int i=1;i<=htot;i++) CDQ.clear(history[i],itot2);
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i,x;n=getint();string type;
	for (i=1;i<=n;i++)
	{
		cin>>type;
		if (type=="I")
		{
			ind[++indtot]=i;
			a[i].x1=getint();a[i].y1=getint();a[i].x2=getint();a[i].y2=getint();
			a[i].type=1;
		}
		if (type=="D")
		{
			x=getint();
			a[i]=a[ind[x]];a[i].type=2;
		}
		if (type=="Q")
		{
			a[i].x1=getint();a[i].y1=getint();a[i].x2=getint();a[i].y2=getint();
			a[i].type=3;
		}
	}
	btot=0;
	for (i=1;i<=n;i++) b[++btot]=point{a[i].x1,i,false},b[++btot]=point{a[i].x2,i,true};
	sort(b+1,b+btot+1);itot1=0;
	for (i=1;i<=btot;i++)
	{
		if (i==1 || b[i-1].val!=b[i].val) itot1++;
		if (!b[i].type) a[b[i].from].nx1=itot1; else a[b[i].from].nx2=itot1;
	}
	btot=0;
	for (i=1;i<=n;i++) b[++btot]=point{a[i].y1,i,false},b[++btot]=point{a[i].y2,i,true};
	sort(b+1,b+btot+1);itot2=0;
	for (i=1;i<=btot;i++)
	{
		if (i==1 || b[i-1].val!=b[i].val) itot2++;
		if (!b[i].type) a[b[i].from].ny1=itot2; else a[b[i].from].ny2=itot2;
	}
	up.init();down.init();lft.init();rght.init();
	int exist=0;
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1)
		{
			exist++;
			down.update(a[i].ny2,itot2,1);
			up.update(itot2-a[i].ny1+1,itot2,1);
			lft.update(a[i].nx2,itot1,1);
			rght.update(itot1-a[i].nx1+1,itot1,1);
		}
		if (a[i].type==2)
		{
			exist--;
			down.update(a[i].ny2,itot2,-1);
			up.update(itot2-a[i].ny1+1,itot2,-1);
			lft.update(a[i].nx2,itot1,-1);
			rght.update(itot1-a[i].nx1+1,itot1,-1);
		}
		if (a[i].type==3)
		{
			ans[i]=exist;
			ans[i]-=down.query(a[i].ny1-1);
			ans[i]-=up.query(itot2-a[i].ny2);
			ans[i]-=lft.query(a[i].nx1-1);
			ans[i]-=rght.query(itot1-a[i].nx2);
		}
	}
	//up-left
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1 || a[i].type==2) c[i]=C{a[i].type,a[i].nx2,itot2-a[i].ny1+1}; else c[i]=C{3,a[i].nx1-1,itot2-a[i].ny2};
		c[i].ind=i;
	}
	cdq(1,n);
	//up-right
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1 || a[i].type==2) c[i]=C{a[i].type,itot1-a[i].nx1+1,itot2-a[i].ny1+1};
		else c[i]=C{3,itot1-a[i].nx2,itot2-a[i].ny2};
		c[i].ind=i;
	}
	cdq(1,n);
	//down-left
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1 || a[i].type==2) c[i]=C{a[i].type,a[i].nx2,a[i].ny2};
		else c[i]=C{3,a[i].nx1-1,a[i].ny1-1};
		c[i].ind=i;
	}
	cdq(1,n);
	//down-right
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1 || a[i].type==2) c[i]=C{a[i].type,itot1-a[i].nx1+1,a[i].ny2};
		else c[i]=C{3,itot1-a[i].nx2,a[i].ny1-1};
		c[i].ind=i;
	}
	cdq(1,n);
	for (i=1;i<=n;i++)
		if (a[i].type==3) printf("%d\n",ans[i]);
	return 0;
}
