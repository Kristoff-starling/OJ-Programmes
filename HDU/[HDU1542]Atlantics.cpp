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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

struct SQUARE
{
	double left,right,up,down;
	int lnum,rnum;
}a[148];

int n;
double len[548];
double ans,width;

struct BORDER
{
	double pos;
	int from;bool type;
	inline bool operator < (const BORDER x) const
	{
		return pos<x.pos;
	}
}b[548];

struct node
{
	int left,right;
	int cnt;double len,res;
}tree[300048];

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	tree[cur].cnt=tree[cur].res=0;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		tree[cur].len=tree[cur<<1].len+tree[cur<<1|1].len;
	}
	else
		tree[cur].len=len[left];
}

void pushup(int cur)
{
	if (tree[cur].cnt>0)
	{
		tree[cur].res=tree[cur].len;
		return;
	}
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].res=0;
		return;
	}
	tree[cur].res=tree[cur<<1].res+tree[cur<<1|1].res;
}

void update(int cur,int left,int right,int delta)
{
	if (left<=tree[cur].left && tree[cur].right<=right)
	{
		tree[cur].cnt+=delta;
		pushup(cur);return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) update(cur<<1,left,right,delta);
	if (mid+1<=right) update(cur<<1|1,left,right,delta);
	pushup(cur);
}

int main ()
{
	int i,ca=0;
	while (scanf("%d",&n) && n)
	{
		for (i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf",&a[i].up,&a[i].left,&a[i].down,&a[i].right);
			b[i*2-1]=BORDER{a[i].left,i,false};
			b[i*2]=BORDER{a[i].right,i,true};
		}
		sort(b+1,b+n*2+1);
		for (i=1;i<=n*2;i++)
		{
			len[i]=(i==1?b[i].pos:b[i].pos-b[i-1].pos);
			if (!b[i].type) a[b[i].from].lnum=i+1; else a[b[i].from].rnum=i;
		}
		for (i=1;i<=n;i++)
		{
			b[i*2-1]=BORDER{a[i].up,i,false};
			b[i*2]=BORDER{a[i].down,i,true};
		}
		sort(b+1,b+n*2+1);
		build(1,1,n*2);ans=0;
		for (i=1;i<=n*2;i++)
		{
			width=b[i].pos-(i==1?0:b[i-1].pos);
			ans+=width*tree[1].res;
			if (!b[i].type)
				update(1,a[b[i].from].lnum,a[b[i].from].rnum,1);
			else
				update(1,a[b[i].from].lnum,a[b[i].from].rnum,-1);
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n",++ca,ans);
	}
	return 0;
}
/*
2
10 10 20 20
15 15 25 25.5
*/