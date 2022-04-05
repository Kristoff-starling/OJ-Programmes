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

int n,q;
int a[848][848];

namespace SegmentTree
{
	int minn[3248][3248],maxn[3248][3248];
	int rownum,fa;
	inline void pushupy(int cur)
	{
		maxn[fa][cur]=max(maxn[fa][cur<<1],maxn[fa][cur<<1|1]);
		minn[fa][cur]=min(minn[fa][cur<<1],minn[fa][cur<<1|1]);
	}
	inline void pushupx(int cur)
	{
		maxn[fa][cur]=max(maxn[fa<<1][cur],maxn[fa<<1|1][cur]);
		minn[fa][cur]=min(minn[fa<<1][cur],minn[fa<<1|1][cur]);
	}
	inline void buildy(int cur,int left,int right,bool isleaf)
	{
		if (left!=right)
		{
			int mid=(left+right)>>1;
			buildy(cur<<1,left,mid,isleaf);buildy(cur<<1|1,mid+1,right,isleaf);
			pushupy(cur);
		}
		else
		{
			if (isleaf) maxn[fa][cur]=minn[fa][cur]=a[rownum][left]; else pushupx(cur);
		}
	}
	inline void buildx(int cur,int left,int right)
	{
		if (left!=right)
		{
			int mid=(left+right)>>1;
			buildx(cur<<1,left,mid);buildx(cur<<1|1,mid+1,right);
			fa=cur;buildy(1,1,n,false);
		}
		else
		{
			rownum=left;fa=cur;
			buildy(1,1,n,true);
		}
	}
	inline void Inserty(int cur,int pos,int newval,int l,int r,bool isleaf)
	{
		if (l==r)
		{
			if (isleaf) {minn[fa][cur]=maxn[fa][cur]=newval;return;} else {pushupx(cur);return;}
		}
		int mid=(l+r)>>1;
		if (pos<=mid) Inserty(cur<<1,pos,newval,l,mid,isleaf); else Inserty(cur<<1|1,pos,newval,mid+1,r,isleaf);
		pushupy(cur);
	}
	inline void Insertx(int cur,int x,int y,int newval,int l,int r)
	{
		if (l==r) {fa=cur;Inserty(1,y,newval,1,n,true);return;}
		int mid=(l+r)>>1;
		if (x<=mid) Insertx(cur<<1,x,y,newval,l,mid); else Insertx(cur<<1|1,x,y,newval,mid+1,r);
		fa=cur;Inserty(1,y,newval,1,n,false);
	}
	inline int querymaxy(int cur,int left,int right,int l,int r)
	{
		if (l>right || r<left || l>r) return -INF;
		if (left<=l && r<=right) return maxn[fa][cur];
		int mid=(l+r)>>1;
		return max(querymaxy(cur<<1,left,right,l,mid),querymaxy(cur<<1|1,left,right,mid+1,r));
	}
	inline int querymaxx(int cur,int x1,int x2,int y1,int y2,int l,int r)
	{
		if (l>x2 || r<x1 || l>r) return -INF;
		if (x1<=l && r<=x2) {fa=cur;return querymaxy(1,y1,y2,1,n);}
		int mid=(l+r)>>1;
		return max(querymaxx(cur<<1,x1,x2,y1,y2,l,mid),querymaxx(cur<<1|1,x1,x2,y1,y2,mid+1,r));
	}
	inline int queryminy(int cur,int left,int right,int l,int r)
	{
		if (l>right || r<left || l>r) return INF;
		if (left<=l && r<=right) return minn[fa][cur];
		int mid=(l+r)>>1;
		return min(queryminy(cur<<1,left,right,l,mid),queryminy(cur<<1|1,left,right,mid+1,r));
	}
	inline int queryminx(int cur,int x1,int x2,int y1,int y2,int l,int r)
	{
		if (l>x2 || r<x1 || l>r) return INF;
		if (x1<=l && r<=x2) {fa=cur;return queryminy(1,y1,y2,1,n);}
		int mid=(l+r)>>1;
		return min(queryminx(cur<<1,x1,x2,y1,y2,l,mid),queryminx(cur<<1|1,x1,x2,y1,y2,mid+1,r));
	}
}

int main ()
{
	int i,j,x,y,l,ca,t=0;ca=getint();
	while (ca--)
	{
		n=getint();printf("Case #%d:\n",++t);
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				a[i][j]=getint();
		SegmentTree::buildx(1,1,n);
		q=getint();
		while (q--)
		{
			x=getint();y=getint();l=getint();l=l/2+1;
			int maxn=SegmentTree::querymaxx(1,max(x-l+1,1),min(x+l-1,n),max(y-l+1,1),min(y+l-1,n),1,n);
			int minn=SegmentTree::queryminx(1,max(x-l+1,1),min(x+l-1,n),max(y-l+1,1),min(y+l-1,n),1,n);
			printf("%d\n",(maxn+minn)/2);
			SegmentTree::Insertx(1,x,y,(maxn+minn)/2,1,n);
		}
	}
	return 0;
}
/*
1
3
1 2 3
4 5 6
7 8 9
5
2 2 1
3 2 3
1 1 3
1 2 3
2 2 3
*/
