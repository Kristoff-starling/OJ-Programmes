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
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
}up,down,lft,rght;
 
int n,itot1,itot2;
int ind[100048],indtot=0;
 
struct Query
{
	int type;
	int x1,y1,x2,y2,t;
	int nx1,ny1,nx2,ny2;
}a[100048];
 
struct point
{
	int val;
	int from;bool type;
	inline bool operator < (const point &x) const {return val<x.val;}
}b[500048];int btot;
 
namespace SegmentTree
{
	int tree[5][(330+5)*200048];
	int lson[(330+5)*200048],rson[(330+5)*200048];int tot=0;
	int lis[100048],litot=0;
	inline void updatey(int cur,int type,int pos,int delta,int l,int r)
	{
		litot=0;
		while (l<=r)
		{
			lis[++litot]=cur;
			if (l==r) break;
			int mid=(l+r)>>1;
			if (pos<=mid)
			{
				if (!lson[cur]) lson[cur]=++tot;
				cur=lson[cur];r=mid;
			}
			else
			{
				if (!rson[cur]) rson[cur]=++tot;
				cur=rson[cur];l=mid+1;
			}
		}
		for (register int i=litot;i>=1;i--) tree[type][lis[i]]+=delta;
	}
	int List[100048],ltot=0;
	inline void updatex(int type,int x,int y,int delta,int r)
	{
		while (x<=r)
		{
			updatey(x,type,y,delta,1,itot2);
			x+=LOWBIT(x);
		}
	}
	int qy[5000048],qyhead,qytail;
	inline int queryy(int cur,int type,int left,int right,int l,int r)
	{
		qyhead=1;qytail=3;qy[1]=l;qy[2]=r;qy[3]=cur;int res=0,curleft,curright,cc,mid;
		while (qyhead<=qytail)
		{
			curleft=qy[qyhead++];curright=qy[qyhead++];cc=qy[qyhead++];
			if (left<=curleft && curright<=right) {res+=tree[type][cc];continue;}
			mid=(curleft+curright)>>1;
			if (left<=mid) qy[++qytail]=curleft,qy[++qytail]=mid,qy[++qytail]=lson[cc];
			if (mid+1<=right) qy[++qytail]=mid+1,qy[++qytail]=curright,qy[++qytail]=rson[cc];
		}
		return res;
	}
	inline int Query(int x,int y1,int y2,int type)
	{
		int res=0;
		while (x)
		{
			res+=queryy(x,type,y1,y2,1,itot2);
			x-=LOWBIT(x);
		}
		return res;
	}
	inline int queryx(int type,int x1,int x2,int y1,int y2)
	{
		if (x1>x2 || y1>y2) return 0;
		return Query(x2,y1,y2,type)-Query(x1-1,y1,y2,type);
	}
}
 
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.ans","w",stdout);
	int i;n=getint();string type;
	for (i=1;i<=n;i++)
	{
		cin>>type;
		if (type=="I") a[i].type=1;
		if (type=="D") a[i].type=2;
		if (type=="Q") a[i].type=3;
		if (a[i].type==1 || a[i].type==3) a[i].x1=getint(),a[i].y1=getint(),a[i].x2=getint(),a[i].y2=getint();
		else a[i].t=getint();
	}
	btot=0;
	for (i=1;i<=n;i++)
		if (a[i].type!=2) b[++btot]=point{a[i].x1,i,false},b[++btot]=point{a[i].x2,i,true};
	sort(b+1,b+btot+1);itot1=0;
	for (i=1;i<=btot;i++)
	{
		if (i==1 || b[i].val!=b[i-1].val) itot1++;
		if (!b[i].type) a[b[i].from].nx1=itot1; else a[b[i].from].nx2=itot1;
	}
	btot=0;
	for (i=1;i<=n;i++)
		if (a[i].type!=2) b[++btot]=point{a[i].y1,i,false},b[++btot]=point{a[i].y2,i,true};
	sort(b+1,b+btot+1);itot2=0;
	for (i=1;i<=btot;i++)
	{
		if (i==1 || b[i].val!=b[i-1].val) itot2++;
		if (!b[i].type) a[b[i].from].ny1=itot2; else a[b[i].from].ny2=itot2;
	}
	int pt=0,cnt=0,exist=0;
	up.init();down.init();lft.init();rght.init();
	SegmentTree::tot=itot1*4;
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1)
		{
			exist++;ind[++indtot]=i;
			down.update(a[i].ny2,itot2,1);
			up.update(itot2-a[i].ny1+1,itot2,1);
			lft.update(a[i].nx2,itot1,1);
			rght.update(itot1-a[i].nx1+1,itot1,1);
			SegmentTree::updatex(1,a[i].nx2,a[i].ny1,1,itot1);
			SegmentTree::updatex(2,a[i].nx1,a[i].ny1,1,itot1);
			SegmentTree::updatex(3,a[i].nx2,a[i].ny2,1,itot1);
			SegmentTree::updatex(4,a[i].nx1,a[i].ny2,1,itot1);
		}
		if (a[i].type==2)
		{
			exist--;pt=ind[a[i].t];
			down.update(a[pt].ny2,itot2,-1);
			up.update(itot2-a[pt].ny1+1,itot2,-1);
			lft.update(a[pt].nx2,itot1,-1);
			rght.update(itot1-a[pt].nx1+1,itot1,-1);
			SegmentTree::updatex(1,a[pt].nx2,a[pt].ny1,-1,itot1);
			SegmentTree::updatex(2,a[pt].nx1,a[pt].ny1,-1,itot1);
			SegmentTree::updatex(3,a[pt].nx2,a[pt].ny2,-1,itot1);
			SegmentTree::updatex(4,a[pt].nx1,a[pt].ny2,-1,itot1);
		}
		if (a[i].type==3)
		{
			int curcnt=0;
			curcnt+=down.query(a[i].ny1-1);
			curcnt+=up.query(itot2-a[i].ny2);
			curcnt+=lft.query(a[i].nx1-1);
			curcnt+=rght.query(itot1-a[i].nx2);
			curcnt-=SegmentTree::queryx(1,1,a[i].nx1-1,a[i].ny2+1,itot2);
			curcnt-=SegmentTree::queryx(2,a[i].nx2+1,itot1,a[i].ny2+1,itot2);
			curcnt-=SegmentTree::queryx(3,1,a[i].nx1-1,1,a[i].ny1-1);
			curcnt-=SegmentTree::queryx(4,a[i].nx2+1,itot1,1,a[i].ny1-1);
			printf("%d\n",exist-curcnt);
		}
	}
	return 0;
}
