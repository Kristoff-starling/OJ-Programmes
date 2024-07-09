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
#define DEBUG(...) printf(__VA_ARGS__)
using namespace std;

const int MOD=1e9+7;
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

int n,m,k;
int cnt[2048];

struct DSU
{
	int pre[2048][2048];
	inline void init()
	{
		int i,j;
		for (i=0;i<=n+10;i++)
			for (j=0;j<=m+10;j++)
				pre[i][j]=j;
	}
	inline int find_anc(int x,int y)
	{
		if (pre[x][y]!=y) pre[x][y]=find_anc(x,pre[x][y]);
		return pre[x][y];
	}
	inline void update(int x,int y1,int y2)
	{
		y1=find_anc(x,y1);y2=find_anc(x,y2);
		pre[x][y1]=y2;
	}
}Left,Right;

struct DSU2
{
	int pre[2048];
	inline void init()
	{
		for (int i=0;i<=n+10;i++)
			pre[i]=i;
	}
	inline int find_anc(int x)
	{
		if (pre[x]!=x) pre[x]=find_anc(pre[x]);
		return pre[x];
	}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		pre[x]=y;
	}
}Up,Down;

inline int myabs(int x)
{
	return x>=0?x:-x;
}

inline int calc_dist(int x1,int y1,int x2,int y2)
{
	return myabs(x1-x2)+myabs(y1-y2);
}

int ansd,ansx,ansy;
inline void check(int curx,int cury,int x,int y)
{
	int curd=calc_dist(curx,cury,x,y);
	if (curd<ansd || (curd==ansd && curx<ansx) || (curd==ansd && curx==ansx && cury<ansy))
		ansd=curd,ansx=curx,ansy=cury;
}

Pair find_pos(int x,int y)
{
	int curx,cury;ansd=INF;
	for (int layer=0;layer<=ansd;layer++)
	{
		curx=x-layer;
		if (curx>0)
		{
			cury=Left.find_anc(curx,y);
			if (cury>0) check(curx,cury,x,y);
			cury=Right.find_anc(curx,y);
			if (cury<=m) check(curx,cury,x,y);
		}
		curx=x+layer;
		if (layer && curx<=n)
		{
			cury=Left.find_anc(curx,y);
			if (cury>0) check(curx,cury,x,y);
			cury=Right.find_anc(curx,y);
			if (cury<=m) check(curx,cury,x,y);
		}
	}
	return mp(ansx,ansy);
}

inline void check2(int curx,int cury,int x,int y)
{
	int curd=calc_dist(curx,cury,x,y);
	if (curd<ansd || (curd==ansd && cury>ansy) || (curd==ansd && cury==ansy && curx<ansx))
		ansd=curd,ansx=curx,ansy=cury;
}

Pair find_pos2(int x,int y)
{
	int curx,cury;ansd=INF;
	for (int layer=0;layer<=ansd;layer++)
	{
		curx=x-layer;
		if (curx>0)
		{
			cury=Left.find_anc(curx,y);
			if (cury>0) check2(curx,cury,x,y);
			cury=Right.find_anc(curx,y);
			if (cury<=m) check2(curx,cury,x,y);
		}
		curx=x+layer;
		if (layer && curx<=n)
		{
			cury=Left.find_anc(curx,y);
			if (cury>0) check2(curx,cury,x,y);
			cury=Right.find_anc(curx,y);
			if (cury<=m) check2(curx,cury,x,y);
		}
	}
	return mp(ansx,ansy);
}

inline void update(int x,int y)
{
	Left.update(x,y,y-1);
	Right.update(x,y,y+1);
	cnt[x]++;
	if (cnt[x]==m)
	{
		Up.update(x,x-1);
		Down.update(x,x+1);
	}
}
			
int main ()
{
	int i,j,x,y;bool type=false;
	n=getint();m=getint();k=getint();
	if (n>m) swap(n,m),type=true;
	Left.init();Right.init();
	for (i=1;i<=k;i++)
	{
		x=getint();y=getint();
		if (!type)
		{		
			Pair res=find_pos(x,y);
			printf("%d %d\n",res.x,res.y);
			update(res.x,res.y);
		}
		else
		{
			int xx=y,yy=m-x+1;
			Pair res=find_pos2(xx,yy);
			int ay=res.x,ax=m-res.y+1;
			printf("%d %d\n",ax,ay);
			update(res.x,res.y);
		}
	}
	return 0;
}
