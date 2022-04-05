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

const int MOD=1e9;
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
int a[48];
int dist[48][48];
int dp[20][100048][2];
int st,d,sleft,sright;
vector<int> v[20];

inline int calc_waitleft(int val,int pos,int sdir)
{
	if (!sdir) val+=sleft+dist[1][st]; else val+=sright+dist[n][st];
	int vv=val;val++;
	int First=sleft+dist[1][pos];
	if (First>=val) return First-vv;
	int delta=val-First;
	int ti=(delta%d==0?delta/d:delta/d+1);
	return First+ti*d-vv;
}

inline int calc_waitright(int val,int pos,int sdir)
{
	if (!sdir) val+=sleft+dist[1][st]; else val+=sright+dist[n][st];
	int vv=val;val++;
	int First=sright+dist[n][pos];
	if (First>=val) return First-vv;
	int delta=val-First;
	int ti=(delta%d==0?delta/d:delta/d+1);
	return First+ti*d-vv;
}

inline int calc_wait(int val,int from,int to,int sdir) {return from<to?calc_waitleft(val,from,sdir):calc_waitright(val,from,sdir);}

int main ()
{
	int i,dir,from,j,Mask,nu;
	n=getint();for (i=1;i<=n-1;i++) a[i]=getint(),dist[i][i+1]=a[i];
	for (i=2;i<=n-1;i++)
		for (j=1;j<=n-i;j++)
			dist[j][j+i]=dist[j][j+i-1]+a[j+i-1];
	for (i=2;i<=n;i++)
		for (j=1;j<=i-1;j++)
			dist[i][j]=dist[j][i];
	st=getint();
	d=getint();sleft=getint();sright=getint();
	if (n==1) {puts("0");return 0;}
	for (i=1;i<=n;i++)
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
			for (dir=0;dir<=1;dir++)
				dp[i][Mask][dir]=INF;
	for (Mask=1;Mask<=(1<<n)-1;Mask++) if (!(Mask&(1<<(st-1)))) v[__builtin_popcount(Mask)].pb(Mask);
	for (i=1;i<=n;i++)
	{
		if (i==st) continue;
		if (i<st) dp[i][1<<(i-1)][1]=dist[st][i]; else dp[i][1<<(i-1)][0]=dist[st][i];
	}
	for (nu=2;nu<=n-1;nu++)
		for (j=0;j<int(v[nu].size());j++)
		{
			Mask=v[nu][j];
			for (i=1;i<=n;i++)
				if (Mask&(1<<(i-1)))
				{
					for (from=1;from<=n;from++)
						if (Mask&(1<<(from-1)) && from!=i)
						{
							dp[i][Mask][0]=min(dp[i][Mask][0],dp[from][Mask^(1<<(i-1))][0]+calc_wait(dp[from][Mask^(1<<(i-1))][0],from,i,0)+dist[from][i]);
							dp[i][Mask][1]=min(dp[i][Mask][1],dp[from][Mask^(1<<(i-1))][1]+calc_wait(dp[from][Mask^(1<<(i-1))][1],from,i,1)+dist[from][i]);
						}
				}
		}
	int ans=INF;
	for (i=1;i<=n;i++)
		if (i!=st)
			for (dir=0;dir<=1;dir++)
				ans=min(ans,dp[i][((1<<n)-1)^(1<<(st-1))][dir]+calc_wait(dp[i][((1<<n)-1)^(1<<(st-1))][dir],i,st,dir)+dist[i][st]);
	printf("%d\n",ans);
}
