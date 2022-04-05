#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,q;
int b[MAXN+48];

namespace SegmentTree
{
	struct node
	{
		int left,right;
		int sum,lazy,minn;
	}tree[MAXN*4];
	inline void pushup(int cur)
	{
		tree[cur].minn=min(tree[cur<<1].minn,tree[cur<<1|1].minn);
		tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
	}
	inline void pushdown(int cur)
	{
		tree[cur<<1].lazy+=tree[cur].lazy;
		tree[cur<<1|1].lazy+=tree[cur].lazy;
		tree[cur<<1].minn-=tree[cur].lazy;
		tree[cur<<1|1].minn-=tree[cur].lazy;
		tree[cur].lazy=0;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].lazy=0;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
			pushup(cur);
		}
		else
		{
			tree[cur].sum=0;tree[cur].minn=b[left];
		}
	}
	inline void update(int cur,int left,int right)
	{
		if (tree[cur].left==tree[cur].right)
		{
			if (tree[cur].minn==1)
			{
				tree[cur].sum++;
				tree[cur].minn=b[tree[cur].left];
				return;
			}
			tree[cur].minn--;
			return;
		}
		if (left<=tree[cur].left && tree[cur].right<=right && tree[cur].minn>1)
		{
			tree[cur].lazy++;tree[cur].minn--;
			return;
		}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right);
		if (mid+1<=right) update(cur<<1|1,left,right);
		pushup(cur);
	}
	inline int query(int cur,int left,int right)
	{
		if (left>tree[cur].right || right<tree[cur].left || left>right) return 0;
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
		pushdown(cur);int res=query(cur<<1,left,right)+query(cur<<1|1,left,right);
		pushup(cur);return res;
	}
}

int main ()
{
	int i,l,r;char op[10];
	while (scanf("%d%d",&n,&q)!=EOF)
	{
		for (i=1;i<=n;i++) b[i]=getint();
		SegmentTree::build(1,1,n);
		while (q--)
		{
			scanf("%s%d%d",op+1,&l,&r);
			if (op[1]=='a') SegmentTree::update(1,l,r); else printf("%d\n",SegmentTree::query(1,l,r));
		}
	}
	return 0;
}
