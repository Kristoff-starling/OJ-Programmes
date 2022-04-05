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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
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
	double maxn;int sum;
}tree[600048];

int n,q;

inline void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	tree[cur].maxn=-1;tree[cur].sum=0;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
	}
}

inline int calc(double cmp,int cur)
{
	if (tree[cur].left==tree[cur].right) return tree[cur].maxn>cmp?1:0;
	if (tree[cur<<1].maxn<=cmp)
		return calc(cmp,cur<<1|1);
	else
		return tree[cur].sum-tree[cur<<1].sum+calc(cmp,cur<<1);
}

inline void update(int cur,int pos,double newval)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].maxn=newval;
		tree[cur].sum=1;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos,newval); else update(cur<<1|1,pos,newval);
	tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
	tree[cur].sum=tree[cur<<1].sum+calc(tree[cur<<1].maxn,cur<<1|1);
}

int main ()
{
	int pos,height;double val;
	n=getint();q=getint();
	build(1,1,n);
	while (q--)
	{
		pos=getint();height=getint();
		val=double(height)/double(pos);
		update(1,pos,val);
		printf("%d\n",tree[1].sum);
	}
	return 0;
}
