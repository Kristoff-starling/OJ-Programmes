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

int n,e,m;
Pair edge[100048];
int ans[100048];

struct node
{
	int x,y;
	int needsz;
	int Left,Right;
	int ind;
	inline void init(int xx) {x=getint();y=getint();needsz=getint();Left=1;Right=e;ind=xx;}
	inline bool operator < (const node &x) const
	{
		return ((Left+Right)>>1)<((x.Left+x.Right)>>1);
	}
}q[100048];

namespace DSU
{
	int pre[100048],rnk[100048];
	inline void init()
	{
		for (int i=1;i<=n+10;i++) pre[i]=i,rnk[i]=1;
	}
	inline int find_anc(int x)
	{
		if (pre[x]!=x) pre[x]=find_anc(pre[x]);
		return pre[x];
	}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (x==y) return;
		pre[x]=y;rnk[y]+=rnk[x];
	}
	inline int getsz(int x) {return rnk[find_anc(x)];}
}

int main ()
{
	int i,layer,curedge,totsz;
	n=getint();e=getint();
	for (i=1;i<=e;i++) edge[i].x=getint(),edge[i].y=getint();
	m=getint();
	for (i=1;i<=m;i++) q[i].init(i);
	for (layer=1;layer<=20;layer++)
	{
		sort(q+1,q+m+1);
		DSU::init();curedge=0;
		for (i=1;i<=m;i++)
		{
			int mid=((q[i].Left+q[i].Right)>>1);
			while (curedge<mid)
			{
				curedge++;
				DSU::update(edge[curedge].x,edge[curedge].y);
			}
			if (q[i].Left==q[i].Right) continue;
			totsz=DSU::getsz(q[i].x)+DSU::getsz(q[i].y);
			if (DSU::find_anc(q[i].x)==DSU::find_anc(q[i].y)) totsz>>=1;
			if (totsz>=q[i].needsz) q[i].Right=mid; else q[i].Left=mid+1;
		}
	}
	for (i=1;i<=m;i++) ans[q[i].ind]=q[i].Left;
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
