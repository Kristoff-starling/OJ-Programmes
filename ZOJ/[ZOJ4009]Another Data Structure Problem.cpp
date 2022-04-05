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

const int MOD=99971;
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
int a[100048];

namespace SegmentTree
{
	int sum[400048][58],lazy[400048];
	inline int tri(int x) {return ((1ll*x*x)%MOD*x)%MOD;}
	inline int mod(int x) {while (x>=MOD) x-=MOD;return x;}
	inline void pushup(int cur)
	{
		int lson=(cur<<1),rson=(cur<<1|1);
		int i,pt1=lazy[lson],pt2=lazy[rson];lazy[cur]=1;
		for (i=1;i<=48;i++,pt1=pt1%48+1,pt2=pt2%48+1) sum[cur][i]=mod(sum[lson][pt1]+sum[rson][pt2]);
	}
	inline void pushdown(int cur)
	{
		lazy[cur<<1]=(lazy[cur<<1]+lazy[cur]-1-1)%48+1;
		lazy[cur<<1|1]=(lazy[cur<<1|1]+lazy[cur]-1-1)%48+1;
	}
	inline void build(int cur,int l,int r)
	{
		lazy[cur]=1;
		if (l!=r)
		{
			int mid=(l+r)>>1;
			build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
			pushup(cur);
		}
		else
		{
			sum[cur][1]=a[l];
			for (register int i=2;i<=48;i++) sum[cur][i]=tri(sum[cur][i-1]);
		}
	}
	inline void update(int cur,int left,int right,int l,int r)
	{
		if (left>r || right<l) return;
		if (left<=l && r<=right) {lazy[cur]=lazy[cur]%48+1;return;}
		pushdown(cur);
		update(cur<<1,left,right,l,(l+r)>>1);update(cur<<1|1,left,right,((l+r)>>1)+1,r);
		pushup(cur);
	}
	inline LL query(int cur,int left,int right,int l,int r,int add)
	{
		if (left>r || right<l) return 0ll;
		if (left<=l && r<=right) return sum[cur][(lazy[cur]+add-1)%48+1];
		//pushdown(cur);
		LL res=0;
		res=mod(res+query(cur<<1,left,right,l,(l+r)>>1,add+lazy[cur]-1));res=mod(res+query(cur<<1|1,left,right,((l+r)>>1)+1,r,add+lazy[cur]-1));
		//pushup(cur);
		return res;
	}
}

int main ()
{
	int ca,i,type,l,r;ca=getint();
	while (ca--)
	{
		n=getint();q=getint();
		for (i=1;i<=n;i++) a[i]=getint(),a[i]%=MOD;
		SegmentTree::build(1,1,n);
		while (q--)
		{
			type=getint();l=getint();r=getint();
			if (type==1) SegmentTree::update(1,l,r,1,n); else printf("%lld\n",SegmentTree::query(1,l,r,1,n,0));
		}
	}
	return 0;
}
