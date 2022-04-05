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
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,qtot;
struct node
{
	int type;
	int left,right;LL c;
	int ind;
}a[100048],tmp1[100048],tmp2[100048];int tot1,tot2;
int ans[100048];

namespace SegmentTree
{
	LL sum[400048],lazy[400048];int lson[400048],rson[400048],tot;
	inline void clear(int cur) {sum[cur]=lazy[cur]=lson[cur]=rson[cur]=0;}
	inline void build() {tot=1;clear(1);}
	inline void pushdown(int cur)
	{
		if (!lson[cur]) lson[cur]=++tot,clear(tot);
		if (!rson[cur]) rson[cur]=++tot,clear(tot);
		lazy[lson[cur]]+=lazy[cur];
		lazy[rson[cur]]+=lazy[cur];
		lazy[cur]=0;
	}
	inline void pushup(int cur,int l,int r)
	{
		int mid=(l+r)>>1,llen=mid-l+1,rlen=r-mid;
		sum[cur]=sum[lson[cur]]+lazy[lson[cur]]*llen+sum[rson[cur]]+lazy[rson[cur]]*rlen;
	}
	inline void update(int cur,int left,int right,int delta,int l,int r)
	{
		if (l>r || l>right || r<left || !cur) return;
		if (left<=l && r<=right) {lazy[cur]+=delta;return;}
		pushdown(cur);int mid=(l+r)>>1;
		update(lson[cur],left,right,delta,l,mid);
		update(rson[cur],left,right,delta,mid+1,r);
		pushup(cur,l,r);
	}
	inline LL query(int cur,int left,int right,int l,int r)
	{
		if (l>r || l>right || r<left || !cur) return 0;
		if (left<=l && r<=right) return sum[cur]+lazy[cur]*(r-l+1);
		pushdown(cur);int mid=(l+r)>>1;
		LL res=query(lson[cur],left,right,l,mid)+query(rson[cur],left,right,mid+1,r);
		pushup(cur,l,r);
		return res;
	}
}

inline void bsearch(int left,int right,int l,int r)
{
	if (l==r)
	{
		for (register int i=left;i<=right;i++)
			if (a[i].type==2) ans[a[i].ind]=l;
		return;
	}
	int i,mid=(l+r)>>1;tot1=tot2=0;
	SegmentTree::build();
	for (i=left;i<=right;i++)
		if (a[i].type==1)
		{
			if (a[i].c<=mid) tmp1[++tot1]=a[i];
			else tmp2[++tot2]=a[i],SegmentTree::update(1,a[i].left,a[i].right,1,1,n);
		}
		else
		{
			LL res=SegmentTree::query(1,a[i].left,a[i].right,1,n);
			if (a[i].c>res) a[i].c-=res,tmp1[++tot1]=a[i]; else tmp2[++tot2]=a[i];
		}
	int pt=left,border=left+tot1-1;
	for (i=1;i<=tot1;i++) a[pt++]=tmp1[i];
	for (i=1;i<=tot2;i++) a[pt++]=tmp2[i];
	bsearch(left,border,l,mid);bsearch(border+1,right,mid+1,r);
}

int main ()
{
	int i;n=getint();m=getint();qtot=0;
	for (i=1;i<=m;i++) a[i].type=getint(),a[i].left=getint(),a[i].right=getint(),a[i].c=getLL(),a[i].ind=(a[i].type==2?++qtot:i),a[i].c=(a[i].type==1?a[i].c+50001:a[i].c);
	bsearch(1,m,1,100048);
	for (i=1;i<=qtot;i++) printf("%d\n",ans[i]-50001);
	return 0;
}
