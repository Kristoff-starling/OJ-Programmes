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

struct node
{
	int left,right;
	LL lmax,rmax,maxn,sum;
}tree[500048];

int n,q;
int a[100048];

inline void pushup(node *cur,node *left,node *right)
{
	cur->sum=left->sum+right->sum;
	cur->lmax=max(left->lmax,left->sum+right->lmax);
	cur->rmax=max(right->rmax,right->sum+left->rmax);
	cur->maxn=max(max(left->maxn,right->maxn),left->rmax+right->lmax);
}

inline void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		pushup(&(tree[cur]),&(tree[cur<<1]),&(tree[cur<<1|1]));
	}
	else
		tree[cur].lmax=tree[cur].rmax=tree[cur].maxn=tree[cur].sum=a[left];
}

inline void update(int cur,int pos,int newval)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].lmax=tree[cur].rmax=tree[cur].sum=tree[cur].maxn=newval;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos,newval); else update(cur<<1|1,pos,newval);
	pushup(&(tree[cur]),&(tree[cur<<1]),&(tree[cur<<1|1]));
}

inline node query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur];
	int mid=(tree[cur].left+tree[cur].right)>>1;
	node res1,res2,res;res1.left=res2.left=-1;
	if (left<=mid) res1=query(cur<<1,left,right);
	if (mid+1<=right) res2=query(cur<<1|1,left,right);
	if (res1.left==-1) return res2;
	if (res2.left==-1) return res1;
	pushup(&res,&res1,&res2);
	res.left=1;return res;
}

int main ()
{
	n=getint();int i,type,x,y;
	for (i=1;i<=n;i++) a[i]=getint();
	build(1,1,n);
	q=getint();
	while (q--)
	{
		type=getint();x=getint();y=getint();
		if (type==0) update(1,x,y); else printf("%lld\n",query(1,x,y).maxn);
	}
	return 0;
}
