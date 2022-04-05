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

const int MOD=1e9+9;
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

int n,qnum;
Pair edge[200048];

struct Query
{
	int left,right;
	int ind;
}q[200048];

namespace BIT
{
	int c[200048];
	inline void init() {for (register int i=1;i<=n;i++) c[i]=0;}
	inline void update(int x,int delta)
	{
		while (x<=n)
		{
			c[x]+=delta;
			x+=LOWBIT(x);
		}
	}
	inline int query(int x)
	{
		int res=0;
		while (x)
		{
			res+=c[x];
			x-=LOWBIT(x);
		}
		return res;
	}
	inline int calc(int left,int right) {return query(right)-query(left-1);}
}

vector<int> Edge[200048];
vector<Pair> que[200048];
int ans[200048];

inline void Clear()
{
	int i;
	for (i=1;i<=n;i++) Edge[i].clear();
	for (i=1;i<=n;i++) que[i].clear();
}

int main ()
{
	//freopen ("icekingdom.in","r",stdin);
	//freopen ("icekingdom.out","w",stdout);
	int i,j,x,y;
	n=getint();qnum=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();if (x>y) swap(x,y);
		edge[i]=mp(x,y);
		Edge[y].pb(x);
	}
	for (i=1;i<=qnum;i++)
	{
		q[i].left=getint();q[i].right=getint();q[i].ind=i;
		que[q[i].right].pb(mp(q[i].left,i));
	}
	BIT::init();
	for (i=1;i<=n-1;i++) BIT::update(edge[i].x,1);
	for (i=n;i;i--)
	{
		if (i!=n)
			for (j=0;j<int(Edge[i+1].size());j++)
				BIT::update(Edge[i+1][j],-1);
		for (j=0;j<int(que[i].size());j++)
		{
			int res=BIT::calc(que[i][j].x,i);
			ans[que[i][j].y]=(i-que[i][j].x+1)-res;
		}
	}
	for (i=1;i<=qnum;i++) printf("%d\n",ans[i]);
	return 0;
}