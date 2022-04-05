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

int n,q;
int a[300048];

int phi[10000048],prime[10000048],tot;bool isprime[10000048];
inline void sieve()
{
	int j;phi[1]=1;
	memset(isprime,true,sizeof(isprime));tot=0;
	for (LL i=2;i<=10000000;i++)
	{
		if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
		for (j=1;j<=tot && (long long)i*prime[j]<=10000000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) {phi[i*prime[j]]=phi[i]*prime[j];break;} else phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

struct node
{
	int left,right;
	int maxn,minn;
	LL sum,val;
}tree[1200048];

inline void pushup(int cur)
{
	tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
	tree[cur].minn=min(tree[cur<<1].minn,tree[cur<<1|1].minn);
	tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
	tree[cur].val=((tree[cur<<1].val && tree[cur<<1].val==tree[cur<<1|1].val)?tree[cur<<1].val:0);
}

inline void pushdown(int cur)
{
	if (tree[cur].val)
	{
		tree[cur<<1].val=tree[cur].val;tree[cur<<1|1].val=tree[cur].val;
		tree[cur<<1].maxn=tree[cur<<1].minn=tree[cur<<1|1].maxn=tree[cur<<1|1].minn=tree[cur].val;
		tree[cur<<1].sum=(tree[cur<<1].val)*(tree[cur<<1].right-tree[cur<<1].left+1);
		tree[cur<<1|1].sum=(tree[cur<<1|1].val)*(tree[cur<<1|1].right-tree[cur<<1|1].left+1);
	}
}

inline void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		pushup(cur);
	}
	else
	{
		tree[cur].maxn=tree[cur].minn=tree[cur].sum=tree[cur].val=a[left];
	}
}

bool cut(int cur)
{
	return tree[cur].maxn==1;
}

bool check(int cur)
{
	return tree[cur].maxn==tree[cur].minn;
}

inline void update(int cur,int left,int right)
{
	if (cut(cur)) return;
	if (left<=tree[cur].left && tree[cur].right<=right && check(cur))
	{
		tree[cur].val=phi[tree[cur].val];
		tree[cur].maxn=tree[cur].minn=tree[cur].val;
		tree[cur].sum=tree[cur].val*(tree[cur].right-tree[cur].left+1);
		return;
	}
	pushdown(cur);
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) update(cur<<1,left,right);
	if (mid+1<=right) update(cur<<1|1,left,right);
	pushup(cur);
}

inline void update(int cur,int left,int right,int x)
{
	if (left<=tree[cur].left && tree[cur].right<=right)
	{
		tree[cur].val=tree[cur].maxn=tree[cur].minn=x;
		tree[cur].sum=tree[cur].val*(tree[cur].right-tree[cur].left+1);
		return;
	}
	pushdown(cur);
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) update(cur<<1,left,right,x);
	if (mid+1<=right) update(cur<<1|1,left,right,x);
	pushup(cur);
}

inline LL query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
	pushdown(cur);
	LL res=0;int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) res+=query(cur<<1,left,right);
	if (mid+1<=right) res+=query(cur<<1|1,left,right);
	pushup(cur);
	return res;
}

int main ()
{
	//freopen ("rikka.in","r",stdin);
	int ca,i,type,l,r,x;
	ca=getint();sieve();
	while (ca--)
	{
		n=getint();q=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		build(1,1,n);
		while (q--)
		{
			type=getint();l=getint();r=getint();if (type==2) x=getint();
			if (type==1) update(1,l,r);
			if (type==2) update(1,l,r,x);
			if (type==3) printf("%lld\n",query(1,l,r));
		}
	}
	return 0;
}
