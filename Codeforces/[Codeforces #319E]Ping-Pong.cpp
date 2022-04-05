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

int n;

struct Interval
{
	int left,right;
	int nl,nr;
	vector<int> qind;
}a[100048];int atot=0;

struct Point
{
	int pos,from;
	bool type;
	inline bool operator < (const Point &x) const {return pos<x.pos;}
}b[200048];int btot=0,Ind=0;

Pair q[100048];int qtot=0;

namespace DSU		
{
	int pre[100048],L[100048],R[100048];
	inline void init()
	{
		int i;
		for (i=1;i<=atot;i++) pre[i]=i,L[i]=a[i].nl,R[i]=a[i].nr;
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
		L[y]=min(L[y],L[x]);R[y]=max(R[y],R[x]);
	}
}

namespace SegmentTree
{
	struct node
	{
		int left,right;
		vector<int> v;
	}tree[400048];
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].v.clear();
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline void update(int cur,int pos,int ind)
	{
		int i;
		for (i=0;i<int(tree[cur].v.size());i++)
			DSU::update(tree[cur].v[i],ind);
		tree[cur].v.clear();
		if (tree[cur].left==tree[cur].right) return;
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) update(cur<<1,pos,ind); else update(cur<<1|1,pos,ind);
	}
	inline void Insert(int cur,int left,int right,int ind)
	{
		if (left>tree[cur].right || right<tree[cur].left) return;
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur].v.pb(ind);return;}
		Insert(cur<<1,left,right,ind);Insert(cur<<1|1,left,right,ind);
	}
}

int main ()
{
	n=getint();int i,j,type,x,y,l,r;
	for (i=1;i<=n;i++)
	{
		type=getint();
		if (type==1)
		{
			++atot;a[atot].left=getint();a[atot].right=getint();
			b[++btot]=Point{a[atot].left,atot,false};b[++btot]=Point{a[atot].right,atot,true};
		}
		else
		{
			q[++qtot].x=getint();q[qtot].y=getint();
			a[atot].qind.pb(qtot);
		}
	}
	sort(b+1,b+btot+1);Ind=0;
	for (i=1;i<=btot;i++)
	{
		if (i==1 || b[i].pos!=b[i-1].pos) Ind++;
		if (!b[i].type) a[b[i].from].nl=Ind; else a[b[i].from].nr=Ind;
	}
	DSU::init();
	SegmentTree::build(1,1,Ind);
	for (i=1;i<=atot;i++)
	{
		SegmentTree::update(1,a[i].nl,i);SegmentTree::update(1,a[i].nr,i);
		l=DSU::L[i];r=DSU::R[i];
		if (r-l>=2) SegmentTree::Insert(1,l+1,r-1,i);
		for (j=0;j<int(a[i].qind.size());j++)
		{
			x=q[a[i].qind[j]].x;y=q[a[i].qind[j]].y;
			x=DSU::find_anc(x);y=DSU::find_anc(y);
			if (x==y) {printf("YES\n");continue;}
			l=DSU::L[y];r=DSU::R[y];
			int x1=a[q[a[i].qind[j]].x].nl,y1=a[q[a[i].qind[j]].x].nr;
			if ((l<x1 && x1<r) || (l<y1 && y1<r))
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}


