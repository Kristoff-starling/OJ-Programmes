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
int b[200048],sum[200048];
Pair a[200048];

struct Tree
{
	int left,right;
	int minn;
}tree[2][800048];

void build(int type,int cur,int left,int right)
{
	tree[type][cur].left=left;tree[type][cur].right=right;tree[type][cur].minn=1e9;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(type,cur<<1,left,mid);
		build(type,cur<<1|1,mid+1,right);
	}
} 	

void update(int type,int cur,int pos,int new_min)
{
	if (tree[type][cur].left==tree[type][cur].right)
	{
		tree[type][cur].minn=min(tree[type][cur].minn,new_min);
		return;
	}
	int mid=(tree[type][cur].left+tree[type][cur].right)>>1;
	if (pos<=mid) update(type,cur<<1,pos,new_min); else update(type,cur<<1|1,pos,new_min);
	tree[type][cur].minn=min(tree[type][cur<<1].minn,tree[type][cur<<1|1].minn);
}

int query(int type,int cur,int left,int right)
{
	if (left<=tree[type][cur].left && tree[type][cur].right<=right) return tree[type][cur].minn;
	int mid=(tree[type][cur].left+tree[type][cur].right)>>1;
	int res=INF;
	if (left<=mid) res=query(type,cur<<1,left,right);
	if (mid+1<=right) res=min(res,query(type,cur<<1|1,left,right));
	return res;
}

bool cmp(Pair x,Pair y)
{
	if (x.x!=y.x) return x.x<y.x;
	return (x.y-x.x+1)>(y.y-y.x+1);
}

int dp[200048];

inline int calc_original_hamming(int left,int right)
{
	if (left>right) return 0;
	return sum[right]-sum[left-1];
}

inline int calc_changed_hamming(int left,int right)
{
	if (left>right) return 0;
	return (right-left+1)-(sum[right]-sum[left-1]);
}

int main ()
{
	int i;n=getint();
	for (i=1;i<=n;i++) b[i]=getint(),sum[i]=sum[i-1]+b[i];
	q=getint();
	for (i=1;i<=q;i++) a[i].x=getint(),a[i].y=getint();
	sort(a+1,a+q+1,cmp);
	for (i=0;i<=q;i++) dp[i]=INF;
	build(0,1,1,n);build(1,1,1,n);
	int ans=calc_original_hamming(1,n);
	for (i=1;i<=q;i++)
	{
		dp[i]=calc_original_hamming(1,a[i].x-1)+calc_changed_hamming(a[i].x,a[i].y);
		dp[i]=min(dp[i],query(0,1,1,a[i].x-1)+sum[a[i].x-1]+calc_changed_hamming(a[i].x,a[i].y));
		dp[i]=min(dp[i],query(1,1,a[i].x,a[i].y)+a[i].y-sum[a[i].y]);
		ans=min(ans,dp[i]+calc_original_hamming(a[i].y+1,n));
		update(0,1,a[i].y,dp[i]-sum[a[i].y]);
		update(1,1,a[i].y,dp[i]-a[i].y+sum[a[i].y]);
	}
	printf("%d\n",ans);
	return 0;
}
