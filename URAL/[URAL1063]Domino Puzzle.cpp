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
const int INF=1e9;
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

int n;
int cnt[10][10];
Pair topos[48];int cost[48];
int b[10],bd[10],d[10];
bool exist[10];
int add[48];

namespace DSU
{
	int pre[10];
	inline void init() {for (register int i=1;i<=6;i++) pre[i]=b[i];}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]); return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

bool ne[10];
inline bool check()
{
	int i,j;
	for (i=1;i<=6;i++) ne[i]=exist[i];DSU::init();
	for (i=1;i<=15;i++)
		if (add[i]) ne[topos[i].x]=true,ne[topos[i].y]=true,DSU::update(topos[i].x,topos[i].y);
	int pt=1;
	while (pt<=6 && !ne[pt]) pt++;
	if (pt>6) return true;
	for (i=pt+1;i<=6;i++)
		if (ne[i] && DSU::find_anc(i)!=DSU::find_anc(pt)) return false;
	for (i=1;i<=6;i++) d[i]=0;
	for (i=1;i<=15;i++) d[topos[i].x]+=add[i],d[topos[i].y]+=add[i];
	int cc=0;
	for (i=1;i<=6;i++) if ((bd[i]+d[i])%2==1) cc++;
	if (cc<=2) return true; else return false;
}

int ans=INF;
Pair anslist[148];int atot=0;
inline void dfs(int cur,int curans)
{
	if (curans>=ans) return;
	int i,j;
	if (cur==16)
	{
		if (check())
		{
			ans=curans;atot=0;
			for (i=1;i<=15;i++)
				for (j=1;j<=add[i];j++)
					anslist[++atot]=topos[i];
		}
		return;
	}
	int xx=topos[cur].x,yy=topos[cur].y;
	if (!cnt[xx][yy])
		for (i=0;i<=2;i++) add[cur]=i,dfs(cur+1,curans+cost[cur]*i);
	else
		for (i=0;i<=1;i++) add[cur]=i,dfs(cur+1,curans+cost[cur]*i);
}

int main ()
{
	int i,j,x,y,Mask,sub;n=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();y=getint();
		if (x>y) swap(x,y);
		cnt[x][y]++;
	}
	x=0;
	for (i=1;i<=5;i++)
		for (j=i+1;j<=6;j++)
			topos[++x]=mp(i,j),cost[x]=i+j;
	for (i=1;i<=6;i++) DSU::pre[i]=i;
	for (i=1;i<=5;i++)
		for (j=i+1;j<=6;j++)
			if (cnt[i][j]) DSU::update(i,j),bd[i]+=cnt[i][j],bd[j]+=cnt[i][j],exist[i]=true,exist[j]=true;
	for (i=1;i<=6;i++) if (cnt[i][i]) exist[i]=true;
	for (i=1;i<=6;i++) b[i]=DSU::pre[i];
	dfs(1,0);
	printf("%d\n",ans);
	printf("%d\n",atot);
	for (i=1;i<=atot;i++) printf("%d %d\n",anslist[i].x,anslist[i].y);
	return 0;
}
