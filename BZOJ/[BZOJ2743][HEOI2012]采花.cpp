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
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,c,m;
int a[1000048],last[1000048],pos[1000048],cur[1000048];
int ans[1000048];

struct Query
{
	int left,right,ind;
	inline bool operator < (const Query &x) const {return right>x.right;}
}q[1000048];

namespace BIT
{
	int c[1000048];
	inline void init() {for (register int i=1;i<=n;i++) c[i]=0;}
	inline void update(int x,int delta) {while (x<=n) {c[x]+=delta;x+=LOWBIT(x);}}
	inline int query(int x) {int res=0;while (x) {res+=c[x];x-=LOWBIT(x);}return res;}
	inline int calc(int left,int right) {return query(right)-query(left-1);}
}

int main ()
{
	int i;n=getint();c=getint();m=getint();
	for (i=1;i<=n;i++) a[i]=getint(),last[i]=pos[a[i]],pos[a[i]]=i;
	for (i=1;i<=m;i++) q[i].left=getint(),q[i].right=getint(),q[i].ind=i;
	sort(q+1,q+m+1);BIT::init();
	for (i=1;i<=c;i++) {cur[i]=pos[i];if (last[cur[i]]) BIT::update(last[cur[i]],1);}
	int pt=1;
	for (i=n;i>=1;i--)
	{
		if (i!=n)
		{
			if (last[cur[a[i+1]]]) BIT::update(last[cur[a[i+1]]],-1);
			cur[a[i+1]]=last[cur[a[i+1]]];
			if (last[cur[a[i+1]]]) BIT::update(last[cur[a[i+1]]],1);
		}
		while (pt<=m && q[pt].right==i) ans[q[pt].ind]=BIT::calc(q[pt].left,n),pt++;
	}
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
