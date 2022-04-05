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

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,k;
int r[2048][2048];

namespace DSU_left
{
	Pair pre[2048][2048];
	inline void init()
	{
		for (int i=0;i<=n+20;i++)
			for (int j=0;j<=m+20;j++)
				pre[i][j]=mp(i,j);
	}
	inline Pair find_anc(int x,int y)
	{
		if (pre[x][y]!=mp(x,y)) pre[x][y]=find_anc(pre[x][y].x,pre[x][y].y);
		return pre[x][y];
	}
	inline void update(int x1,int y1,int x2,int y2)
	{
		Pair x=find_anc(x1,y1),y=find_anc(x2,y2);
		pre[x.x][x.y]=y;
	}
}

namespace DSU_right
{
	Pair pre[2048][2048];
	inline void init()
	{
		for (int i=0;i<=n+20;i++)
			for (int j=0;j<=m+20;j++)
				pre[i][j]=mp(i,j);
	}
	inline Pair find_anc(int x,int y)
	{
		if (pre[x][y]!=mp(x,y)) pre[x][y]=find_anc(pre[x][y].x,pre[x][y].y);
		return pre[x][y];
	}
	inline void update(int x1,int y1,int x2,int y2)
	{
		Pair x=find_anc(x1,y1),y=find_anc(x2,y2);
		pre[x.x][x.y]=y;
	}
}


inline Pair go_left_left(int layer,int sx,int sy)
{
	int cmpy=max(1,sy-layer+1);
	if (sx<=0) sy-=(1-sx),sx=1;
	if (sy<=0) return mp(-1,-1);
	Pair res=DSU_left::find_anc(sx,sy);
	if (res.y<cmpy) return mp(-1,-1);
	return res;
}

inline Pair go_left_right(int layer,int sx,int sy)
{
	int cmpx=min(n,sx+layer-1);
	if (sy<=0) sx+=(1-sy),sy=1;
	if (sx>n) return mp(-1,-1);
	Pair res=DSU_right::find_anc(sx,sy);
	if (res.x>cmpx) return mp(-1,-1);
	return res;
}

inline Pair go_right_left(int layer,int sx,int sy)
{
	int cmpx=min(n,sx+layer-1);
	if (sy>m) sx+=(sy-m),sy=m;
	if (sx>n) return mp(-1,-1);
	Pair res=DSU_left::find_anc(sx,sy);
	if (res.x>cmpx) return mp(-1,-1);
	return res;
}

inline Pair go_right_right(int layer,int sx,int sy)
{
	int cmpy=min(m,sy+layer-1);
	if (sx<=0) sy+=(1-sx),sx=1;
	if (sy>m) return mp(-1,-1);
	Pair res=DSU_right::find_anc(sx,sy);
	if (res.y>cmpy) return mp(-1,-1);
	return res;
}

inline int myabs(int x)
{
	return x>=0?x:-x;
}

int calc_dist(int x1,int y1,int x2,int y2)
{
	return myabs(x1-x2)+myabs(y1-y2);
}

Pair work(int x,int y)
{
	int i,j,layer,sxl,syl,sxr,syr,xx,yy;
	for (i=-3;i<=3;i++)
		for (j=-3;j<=3;j++)
		{
			xx=x+i;yy=y+j;
			if (1<=xx && xx<=n && 1<=yy && yy<=m)
				r[x][y]=max(r[x][y],r[xx][yy]-calc_dist(x,y,xx,yy));
		}
	for (layer=r[x][y];layer<=1000000;layer++)
	{
		sxl=sxr=x-layer+1;syl=syr=y;
		Pair left=go_left_left(layer,sxl,syl),right=go_right_right(layer,sxr,syr);
		if (left!=mp(-1,-1) && right!=mp(-1,-1))
		{
			if (left.x<=right.x)
			{
				DSU_left::update(left.x,left.y,left.x+1,left.y-1);
				DSU_right::update(left.x,left.y,left.x+1,left.y+1);
				r[x][y]=layer;
				return mp(left.x,left.y);
			}
			else
			{
				DSU_left::update(right.x,right.y,right.x+1,right.y-1);
				DSU_right::update(right.x,right.y,right.x+1,right.y+1);
				r[x][y]=layer; 
				return mp(right.x,right.y);
			}
		}
		if (left!=mp(-1,-1))
		{
			DSU_left::update(left.x,left.y,left.x+1,left.y-1);
			DSU_right::update(left.x,left.y,left.x+1,left.y+1);
			r[x][y]=layer;
			return mp(left.x,left.y);
		}
		if (right!=mp(-1,-1))
		{
			DSU_left::update(right.x,right.y,right.x+1,right.y-1);
			DSU_right::update(right.x,right.y,right.x+1,right.y+1);
			r[x][y]=layer;
			return mp(right.x,right.y);
		}
		sxl=sxr=x;syl=y-layer+1;syr=y+layer-1;
		left=go_left_right(layer,sxl,syl);right=go_right_left(layer,sxr,syr);
		if (left!=mp(-1,-1) && right!=mp(-1,-1))
		{
			if (left.x<=right.x)
			{
				DSU_left::update(left.x,left.y,left.x+1,left.y-1);
				DSU_right::update(left.x,left.y,left.x+1,left.y+1);
				r[x][y]=layer;
				return mp(left.x,left.y);
			}
			else
			{
				DSU_left::update(right.x,right.y,right.x+1,right.y-1);
				DSU_right::update(right.x,right.y,right.x+1,right.y+1);
				r[x][y]=layer;
				return mp(right.x,right.y);
			}
		}
		if (left!=mp(-1,-1))
		{
			DSU_left::update(left.x,left.y,left.x+1,left.y-1);
			DSU_right::update(left.x,left.y,left.x+1,left.y+1);
			r[x][y]=layer;
			return mp(left.x,left.y);
		}
		if (right!=mp(-1,-1))
		{
			DSU_left::update(right.x,right.y,right.x+1,right.y-1);
			DSU_right::update(right.x,right.y,right.x+1,right.y+1);
			r[x][y]=layer;
			return mp(right.x,right.y);
		}
	}
}

int main ()
{
	int i,j,x,y;
	n=getint();m=getint();
	DSU_left::init();DSU_right::init();
	k=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			r[i][j]=1;
	while (k--)
	{
		x=getint();y=getint();
		Pair res=work(x,y);
		printf("%d %d\n",res.x,res.y);
	}
	return 0;
}	
