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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const long double pi=acos(-1);
const int G=3;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline char GetChar()
{
	char ch;
	while (!isalpha(ch=getchar())) {}
	return ch;
}

int n,m,q;

namespace DSU
{
	int pre[100048];
	inline void init() {for (register int i=1;i<=n+10;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[y]=x;}
}

int a[100048];

int toind[100048];

int root[100048],tot=0;
struct node
{
	int left,right;
	int sz;
	inline void init() {left=right=0;sz=0;}
}tree[7000048];

inline void pushup(int cur) {tree[cur].sz=(tree[tree[cur].left].sz+tree[tree[cur].right].sz);}

inline void Insert(int &cur,int pos,int l,int r)
{
	if (!cur) cur=++tot,tree[cur].init();
	if (l==r) {tree[cur].sz=1;return;}
	int mid=(l+r)/2;
	if (pos<=mid) Insert(tree[cur].left,pos,l,mid); else Insert(tree[cur].right,pos,mid+1,r);
	pushup(cur);
}

inline int merge(int root1,int root2)
{
	if (!root1 || !root2) return root1+root2;
	tree[root1].left=merge(tree[root1].left,tree[root2].left);
	tree[root1].right=merge(tree[root1].right,tree[root2].right);
	pushup(root1);return root1;
}

inline int query(int cur,int key,int l,int r)
{
	if (tree[cur].sz<key) return -1;
	if (l==r) return toind[l];
	int mid=(l+r)/2;
	if (tree[cur].left==-1) return query(tree[cur].right,key,mid+1,r);
	int ss=tree[tree[cur].left].sz;
	if (ss>=key) return query(tree[cur].left,key,l,mid); else return query(tree[cur].right,key-ss,mid+1,r);
}

int main ()
{
	int i,x,y;char type;n=getint();m=getint();
	tot=0;memset(root,0,sizeof(root));
	for (i=1;i<=n;i++) a[i]=getint(),toind[a[i]]=i;
	for (i=1;i<=n;i++) Insert(root[i],a[i],1,n);
	DSU::init();
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (x==y) continue;
		merge(root[x],root[y]);
		DSU::update(x,y);
	}
	q=getint();
	while (q--)
	{
		type=GetChar();x=getint();y=getint();
		if (type=='B')
		{
			x=DSU::find_anc(x);y=DSU::find_anc(y);
			if (x==y) continue;
			root[x]=merge(root[x],root[y]);
			DSU::update(x,y);
		}
		else
		{
			x=DSU::find_anc(x);
			printf("%d\n",query(root[x],y,1,n));
		}
	}
	return 0;
}
