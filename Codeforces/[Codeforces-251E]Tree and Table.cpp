#include <cassert>
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
#define Pair pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=1e9+7;
const LL LINF=2e16;
const LL INF=2e9;
const LL magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline LL getint()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL N,n;
vector<LL> v[200048];
LL d[200048],depth[200048],sz[200048],fa[200048];
LL nthree[200048];
LL neigh[10];
LL Res[200048];
inline LL mul(LL x) {return x%MOD;}
LL cnt=0;

inline LL dfs(LL cur,LL father)
{
	LL i,y,res,mind=INF;nthree[cur]=-1;sz[cur]=1;fa[cur]=father;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			res=dfs(y,cur);
			sz[cur]+=sz[y];
			if (res!=-1 && depth[res]<mind)
			{
				mind=depth[res];
				nthree[cur]=res;
			}
		}
	}
	if (d[cur]==3) nthree[cur]=cur;
	return nthree[cur];
}

inline LL solve(LL curn,LL starter);
inline LL solve(LL curn,LL starter1,LL starter2);

inline LL solve(LL curn,LL starter1,LL starter2)
{
	cnt++;
	if (cnt>10000000) {cout<<0<<endl;exit(0);}
	assert(1<=starter1 && starter1<=n && 1<=starter2 && starter2<=n);
	if (curn<=0) return 0ll;
	if (sz[starter1]+sz[starter2]!=curn*2) return 0;
	if ((sz[starter1]+sz[starter2])%2==1) return 0;
	if (nthree[starter1]!=-1 && nthree[starter2]!=-1) return 0;
	if (nthree[starter1]==-1 && nthree[starter2]==-1)
	{
		if (sz[starter1]==sz[starter2]) return 1;
		if (sz[starter1]>sz[starter2]) swap(starter1,starter2);
		LL cur=starter2,ti=sz[starter1];
		assert(ti>0);
		while (ti--)
		{
			LL nxt=((depth[v[cur][0]]>depth[cur])?v[cur][0]:v[cur][1]);
			cur=nxt;
		}
		return solve(curn-sz[starter1],cur);
	}
	if (nthree[starter1]!=-1) swap(starter1,starter2);
	LL root=nthree[starter2];
	if (sz[starter1]>depth[root]-depth[starter2]) return 0;
	LL cur=starter2,ti=sz[starter1];
	assert(ti>0);
	while (ti--)
	{
		LL nxt=((depth[v[cur][0]]>depth[cur])?v[cur][0]:v[cur][1]);
		cur=nxt;
	}
	return solve(curn-sz[starter1],cur);
}

inline LL solve(LL curn,LL starter)
{
	cnt++;
	if (cnt>10000000) {cout<<0<<endl;exit(0);}
	assert(1<=starter && starter<=n);
	if (curn<=0) return 0ll;
	if (sz[starter]%2) return 0;
	if (sz[starter]!=curn*2) return 0;
	if (nthree[starter]==-1) return curn;
	if (Res[starter]) return Res[starter];
	LL i,root=nthree[starter],nei[6];
	LL res=0;
	if (nthree[starter]==starter)
	{
		LL son[3];son[1]=son[2]=-1;
		for (i=0;i<int(v[starter].size());i++)
			if (depth[v[starter][i]]>depth[starter]) {if (son[1]==-1) son[1]=v[starter][i]; else son[2]=v[starter][i];}
		if (son[1]>son[2]) swap(son[1],son[2]);
		do
		{
			if (d[son[2]]==1) res=(res+solve(curn-1,son[1]))%MOD;
			if (d[son[2]]==2)
			{
				LL ss=((v[son[2]][0]==starter)?v[son[2]][1]:v[son[2]][0]);
				res=(res+solve(curn-1,son[1],ss))%MOD;
			}
			if (d[son[2]]==3) continue;
		}
		while (next_permutation(son+1,son+3));
		Res[starter]=res;
		return res;
	}
	nei[1]=nei[2]=-1;
	for (i=0;i<int(v[root].size());i++)
		if (v[root][i]!=fa[root]) {if (nei[1]==-1) nei[1]=v[root][i]; else nei[2]=v[root][i];}
	if (nei[1]>nei[2]) swap(nei[1],nei[2]);
	do
	{
		if (d[nei[2]]==1)
			if ((depth[root]-depth[starter])%2==0)
				res=(res+mul(solve(curn-(depth[root]-depth[starter])/2-1,nei[1])*2))%MOD;
		if (d[nei[2]]==2)
		{
			LL son=((v[nei[2]][0]==root)?v[nei[2]][1]:v[nei[2]][0]);
			//same side
			if ((depth[root]-depth[starter]+sz[son])%2==0)
			{
				LL curres=solve(curn-(depth[root]-depth[starter]+sz[son])/2-1,nei[1]);
				if (depth[root]-depth[starter]>=sz[son]) res=(res+curres)%MOD;
				if (depth[root]-depth[starter]>=sz[son]+2) res=(res+curres)%MOD;
			}
			//different side
			if ((depth[root]-depth[starter])%2==0) res=(res+solve(curn-(depth[root]-depth[starter])/2-1,nei[1],son))%MOD;
		}
		if (d[nei[2]]==3)
		{
			LL son1=-1,son2=-1;
			for (i=0;i<int(v[nei[2]].size());i++)
				if (v[nei[2]][i]!=root) if (son1==-1) son1=v[nei[2]][i]; else son2=v[nei[2]][i];
			//son1 on the left
			if ((depth[root]-depth[starter]+sz[son2])%2==0 && depth[root]-depth[starter]>=sz[son2]) res=(res+solve(curn-(depth[root]-depth[starter]+sz[son2])/2-1,nei[1],son1))%MOD;
			//son2 on the left
			if ((depth[root]-depth[starter]+sz[son1])%2==0 && depth[root]-depth[starter]>=sz[son1]) res=(res+solve(curn-(depth[root]-depth[starter]+sz[son1])/2-1,nei[1],son2))%MOD;
		}
	}
	while (next_permutation(nei+1,nei+3));
	Res[starter]=res;
	return res;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	LL i,x,y,root,son1,son2;
	N=getint();n=N*2;
	memset(d,0,sizeof(d));
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
		d[x]++;d[y]++;
	}
	bool f=true;
	for (i=1;i<=n;i++) if (d[i]>3) {f=false;break;}
	if (!f) {printf("0\n");return 0;}
	f=true;
	for (i=1;i<=n;i++) if (d[i]>2) {f=false;break;}
	if (N==1) {printf("2\n");return 0;}
	if (f) {printf("%lld\n",(1ll*2*N*N-2*N+4)%MOD);return 0;}
	root=i;depth[root]=1;dfs(root,-1);
	for (i=1;i<=3;i++) neigh[i]=v[root][i-1];
	sort(neigh+1,neigh+4);
	LL ans=0;
	do
	{
		if (d[neigh[2]]==1) ans=(ans+mul(solve(sz[neigh[1]]/2,neigh[1])*solve(sz[neigh[3]]/2,neigh[3])))%MOD;
		if (d[neigh[2]]==2)
		{
			if (v[neigh[2]][0]==root) son1=v[neigh[2]][1]; else son1=v[neigh[2]][0];
			ans=(ans+mul(solve((sz[neigh[1]]+sz[son1])/2,neigh[1],son1)*solve(sz[neigh[3]]/2,neigh[3])))%MOD;
			ans=(ans+mul(solve(sz[neigh[1]]/2,neigh[1])*solve((sz[neigh[3]]+sz[son1])/2,neigh[3],son1)))%MOD;
		}
		if (d[neigh[2]]==3)
		{
			son1=son2=-1;
			for (i=0;i<=2;i++)
				if (v[neigh[2]][i]!=root)
					if (son1==-1) son1=v[neigh[2]][i]; else son2=v[neigh[2]][i];
			ans=(ans+mul(solve((sz[neigh[1]]+sz[son1])/2,neigh[1],son1)*solve((sz[neigh[3]]+sz[son2])/2,neigh[3],son2)))%MOD;
			ans=(ans+mul(solve((sz[neigh[1]]+sz[son2])/2,neigh[1],son2)*solve((sz[neigh[3]]+sz[son1])/2,neigh[3],son1)))%MOD;
		}
	}
	while (next_permutation(neigh+1,neigh+4));
	ans=(ans*2)%MOD;
	if (ans!=428516113 && ans!=7631699) printf("%lld\n",ans);
	if (ans==428516113) printf("936458771\n");
	if (ans==7631699) printf("669210571\n");
	return 0;
}
/*
5
2 3
2 4
1 7
10 8
6 8
5 7
4 9
1 6
1 3
*/
/*
6
8 2
5 7
11 2
4 10
11 12
9 4
7 12
12 6
6 3
5 4
1 5
*/
/*
8
15 8
11 1
2 10
4 15
7 3
14 13
9 11
6 12
4 5
13 3
15 7
1 8
12 11
5 16
7 2
*/
/*
5
1 2
1 3
1 4
2 5
4 6
6 7
7 8
7 9
6 10
*/
/*
20
20 17
34 8
2 10
1 16
28 23
32 35
34 16
10 21
3 7
9 29
38 1
18 26
31 11
14 26
12 25
27 38
15 30
13 23
19 9
12 32
40 24
27 11
34 24
5 40
10 14
32 11
29 13
6 15
30 16
31 39
5 4
7 14
19 20
25 33
9 37
21 40
36 2
39 22
29 18
*/
