#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cctype>
#define LL long long
#define LB long double
#define mp make_pair
#define pb push_back
#define pf push_front 
#define Pair pair<int,int>
#define x first
#define y second
#define LOWBIT(X) x & (-x)
using namespace std;

const int MOD=1e6;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;bool f;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
string type;

struct node
{
	int left,right;
	int max_left,max_right;
	set<int> s;
}tree[600048];

struct Query
{
	int type;
	int x,y;
	int nx;
	int num;
}a[200048];
int posx[200048],top=0;

bool cmp_x(Query x,Query y)
{
	return x.x<y.x;
}

bool cmp_num(Query x,Query y)
{
	return x.num<y.num;
}

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	tree[cur].max_left=tree[cur].max_right=-1;
	tree[cur].s.clear();
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
	}
}

void add(int cur,int x,int y)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].s.insert(y);
		tree[cur].max_left=tree[cur].max_right=*(tree[cur].s.rbegin());
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (x<=mid)
	{
		add(cur<<1,x,y);
		tree[cur].max_left=max(tree[cur<<1].max_left,tree[cur<<1].max_right);
	}
	else
	{
		add(cur<<1|1,x,y);
		tree[cur].max_right=max(tree[cur<<1|1].max_left,tree[cur<<1|1].max_right);
	}
}

void Remove(int cur,int x,int y)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].s.erase(y);
		if (tree[cur].s.empty())
			tree[cur].max_left=tree[cur].max_right=-1;
		else
			tree[cur].max_left=tree[cur].max_right=*(tree[cur].s.rbegin());
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (x<=mid)
	{
		Remove(cur<<1,x,y);
		tree[cur].max_left=max(tree[cur<<1].max_left,tree[cur<<1].max_right);
	}
	else
	{
		Remove(cur<<1|1,x,y);
		tree[cur].max_right=max(tree[cur<<1|1].max_left,tree[cur<<1|1].max_right);
	}
}

int std_cmp;
set<int>::iterator iter;
Pair Get(int cur)
{
	if (max(tree[cur].max_left,tree[cur].max_right)<=std_cmp) return mp(-1,-1);
	while (tree[cur].left!=tree[cur].right)
		if (tree[cur].max_left<=std_cmp) cur<<=1,cur|=1; else cur<<=1;
	iter=tree[cur].s.upper_bound(std_cmp);
	return mp(tree[cur].left,*iter);
}

Pair query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return Get(cur);
	int mid=(tree[cur].left+tree[cur].right)>>1;
	Pair res1=mp(-1,-1),res2=mp(-1,-1);
	if (left<=mid) res1=query(cur<<1,left,right);
	if (mid+1<=right) res2=query(cur<<1|1,left,right);
	if (res1.x==-1) return res2; else return res1;
}

int main ()
{
	n=getint();
	int i,x,y;
	for (i=1;i<=n;i++)
	{
		cin>>type;
		if (type[0]=='a') a[i].type=1;
		if (type[0]=='r') a[i].type=2;
		if (type[0]=='f') a[i].type=3;
		a[i].x=getint();a[i].y=getint();
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp_x);
	top=1;
	for (i=1;i<=n;i++)
	{
		if (i!=1 && a[i].x>a[i-1].x) top++;
		a[i].nx=top;
		posx[top]=a[i].x;
	}
	sort(a+1,a+n+1,cmp_num);
	build(1,1,top);
	for (i=1;i<=n;i++)
	{
		if (a[i].type==1) add(1,a[i].nx,a[i].y);
		if (a[i].type==2) Remove(1,a[i].nx,a[i].y);
		if (a[i].type==3)
		{
			std_cmp=a[i].y;
			Pair res=query(1,a[i].nx+1,top);
			if (res.x==-1) printf("-1\n"); else printf("%d %d\n",posx[res.x],res.y);
		}
	}
	return 0;
}
