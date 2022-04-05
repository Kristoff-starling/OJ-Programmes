#pragma GCC optimize ("O3")
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

int n,m,k;
int need_pos[28],need_dir[28];
LL dp[2][1500048];
int nxt[21][1100048];

inline LL mod(LL x)
{
	while (x>=MOD) x-=MOD;
	return x;
}

int main ()
{
	int i,Mask,toMask,pos,x,y,c,step,cur;
	n=getint();m=getint();k=getint();n--;
	for (i=1;i<=k;i++)
	{
		x=getint();y=getint();c=getint();
		need_pos[x]|=(1<<(y-1));need_dir[x]|=(1<<(y-1))*c;
	}
	for (i=0;i<=n-1;i++)
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
		{
			if (Mask&(1<<i))
			{
				nxt[i][Mask]=-1;
				continue;
			}
			toMask=Mask;toMask|=(1<<i);pos=i;
			while (pos<=n-1 && !(Mask&(1<<pos))) pos++;
			if (pos<=n-1) toMask^=(1<<pos);
			nxt[i][Mask]=toMask;
		}
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for (step=1,cur=1;step<=m;step++,cur^=1)
	{
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
			dp[cur][Mask]=dp[cur^1][Mask];
		for (i=0;i<=n-1;i++)
			for (Mask=0;Mask<=(1<<n)-1;Mask++)
				if (nxt[i][Mask]!=-1)
					dp[cur][nxt[i][Mask]]=mod(dp[cur][nxt[i][Mask]]+dp[cur][Mask]);
		for (Mask=0;Mask<=(1<<n)-1;Mask++)
			if ((Mask&need_pos[step])!=need_dir[step])
				dp[cur][Mask]=0;
		//if (step==1)
		//for (Mask=0;Mask<=(1<<n)-1;Mask++)
		//	cout<<Mask<<' '<<dp[cur][Mask]<<endl;
	}
	LL ans=0;
	for (Mask=0;Mask<=(1<<n)-1;Mask++)
		ans=mod(ans+dp[cur^1][Mask]);
	printf("%lld\n",ans);
	return 0;
}