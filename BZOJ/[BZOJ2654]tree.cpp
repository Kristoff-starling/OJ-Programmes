#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOBIT(x) x & (-x)
using namespace std;

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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,e,need,sum;

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

struct Edge
{
	int x,y,col,val,nv;
	inline void input() {x=getint();y=getint();val=getint();col=getint();x++;y++;}
}edge[MAXN+48];

int L,R;

inline bool cmp1(Edge x,Edge y)
{
	if (x.nv!=y.nv) return x.nv<y.nv;
	return x.col>y.col;
}

inline bool cmp2(Edge x,Edge y)
{
	if (x.nv!=y.nv) return x.nv<y.nv;
	return x.col<y.col;
}

inline void doit(int x)
{
	int i,cnt;L=0;R=0;
	for (i=1;i<=e;i++) if (!edge[i].col) edge[i].nv=edge[i].val+x; else edge[i].nv=edge[i].val;
	sort(edge+1,edge+e+1,cmp1);DSU::init();cnt=0;sum=0;
	for (i=1;i<=e;i++)
		if (DSU::find_anc(edge[i].x)!=DSU::find_anc(edge[i].y))
		{
			cnt++;sum+=edge[i].nv;
			DSU::update(edge[i].x,edge[i].y);
			if (!edge[i].col) L++;
			if (cnt>=n-1) break;
		}
	sort(edge+1,edge+e+1,cmp2);DSU::init();cnt=0;
	for (i=1;i<=e;i++)
		if (DSU::find_anc(edge[i].x)!=DSU::find_anc(edge[i].y))
		{
			cnt++;
			DSU::update(edge[i].x,edge[i].y);
			if (!edge[i].col) R++;
			if (cnt>=n-1) break;
		}
}

int main ()
{
	n=getint();e=getint();need=getint();int i;
	for (i=1;i<=e;i++) edge[i].input();
	int l=-200,r=200,mid,ans;
	while (l<=r)
	{
		mid=(l+r)>>1;
		doit(mid);
		if (L<=need && need<=R) ans=sum-need*mid;
		if (R>=need) l=mid+1; else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
