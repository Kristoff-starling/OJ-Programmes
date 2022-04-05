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

const int MOD=123456789;
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

struct LinerBase
{
	int b[21];
	inline void clear() {memset(b,0,sizeof(b));}
	inline void Insert(int x)
	{
		for (register int i=15;i>=0;i--)
			if ((x>>i)&1)
				if (!b[i]) {b[i]=x;return;} else x^=b[i];
	}
	inline bool Find(int x)
	{
		for (register int i=15;i>=0;i--)
			if ((x>>i)&1)
				if (!b[i]) return false; else x^=b[i];
		return true;
	}
	inline LinerBase merge(LinerBase other)
	{
		LinerBase res;int i;
		for (i=15;i>=0;i--) res.b[i]=b[i];
		for (i=15;i>=0;i--) res.Insert(other.b[i]);
		return res;
	}
};

namespace SegmentTree
{
	struct node
	{
		int left,right;
		LinerBase base;
	}tree[300048];
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].base.clear();
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
		}
	}
	inline void update(int cur,int left,int right,int val)
	{
		if (left>right || tree[cur].left>right || tree[cur].right<left) return;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].base.Insert(val);
			return;
		}
		update(cur<<1,left,right,val);
		update(cur<<1|1,left,right,val);
	}
	inline void calc(int cur)
	{
		int fa=cur>>1;
		if (fa) tree[cur].base=tree[cur].base.merge(tree[fa].base);
		if (tree[cur].left!=tree[cur].right) calc(cur<<1),calc(cur<<1|1);
	}
	inline bool query(int cur,int pos,int val)
	{
		if (tree[cur].left==tree[cur].right) return tree[cur].base.Find(val);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) return query(cur<<1,pos,val); else return query(cur<<1|1,pos,val);
	}
}

int n,m;
vector<int> v[100048];
Pair q[100048];int qtot;

int main ()
{
	int i,j,type,x,y;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		type=getint();
		if (type==1)
		{
			x=getint();
			v[x].pb(i);
		}
		else
		{
			x=getint();y=getint();
			q[++qtot]=mp(x^y,i);
		}
	}
	SegmentTree::build(1,1,n);
	for (i=1;i<=m;i++)
	{
		if (int(v[i].size())%2==1) v[i].pb(n+1);
		for (j=0;j<int(v[i].size());j++)
			if (j%2==0) SegmentTree::update(1,v[i][j],v[i][j+1]-1,i);
	}
	SegmentTree::calc(1);
	for (i=1;i<=qtot;i++) if (SegmentTree::query(1,q[i].y,q[i].x)) puts("Yes"); else puts("No");
	return 0;
}
