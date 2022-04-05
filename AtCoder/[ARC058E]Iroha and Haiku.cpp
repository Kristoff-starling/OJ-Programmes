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

LL dp[48][1000048];
int n,X,Y,Z;
vector<Pair> can[1000048];

LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1)
		{
			res=(res*x)%MOD;
			y--;
		}
		x=(x*x)%MOD;
		y>>=1;
	}
	return res;
}

int num[48],num1[48];
int doit(int Mask,int cur)
{
	int res=0,i;
	for (i=1;i<=X+Y+Z;i++)
		if (Mask&(1<<(i-1))) num[i]=1; else num[i]=0;
	for (i=1;i<=X+Y+Z;i++) num1[i]=0;
	for (i=1;i<=X+Y+Z;i++)
		if (num[i] && i+cur<=X+Y+Z) num1[i+cur]=1;
	num1[cur]=1;
	for (i=1;i<=X+Y+Z;i++)
		if (num1[i]) res|=(1<<(i-1));
	return res;
}

int main ()
{
	int i,cur,Mask,toMask,nMask,totype,type;
	n=getint();X=getint();Y=getint();Z=getint();
	dp[0][0]=1;
	nMask=0;
	nMask|=(1<<(Z-1));
	nMask|=(1<<(Y+Z-1));
	nMask|=(1<<(X+Y+Z-1));
	for (Mask=0;Mask<=(1<<(X+Y+Z))-1;Mask++)
	{
		can[Mask].clear();
		for (cur=1;cur<=10;cur++)
		{
			toMask=doit(Mask,cur);
			totype=((toMask&nMask)==nMask?1:0);
			if (totype==0) can[Mask].pb(mp(cur,toMask));
		}
	}
	for (i=0;i<=n-1;i++)
		for (Mask=0;Mask<=(1<<(X+Y+Z))-1;Mask++)
				if (dp[i][Mask])
				{
					//cout<<i<<' '<<Mask<<endl;
					for (int j=0;j<int(can[Mask].size());j++)
					{
						cur=can[Mask][j].x;toMask=can[Mask][j].y;
						dp[i+1][toMask]=(dp[i+1][toMask]+dp[i][Mask])%MOD;
					}
				}
	//cout<<"*"<<endl;
	LL ans=0;
	for (Mask=0;Mask<=(1<<(X+Y+Z))-1;Mask++)
		ans=(ans+dp[n][Mask]);
	//cout<<"*"<<endl;
	LL fans=quick_pow(10,n);
	fans-=ans;
	fans%=MOD;if (fans<0) fans+=MOD;
	cout<<fans<<endl;
	return 0;
	/*for (i=1;i<=n;i++)
		for (Mask=0;Mask<=(1<<(X+Y+Z))-1;Mask++)
			if ((Mask&nMask)==nMask) ans=(ans+dp[i][Mask])%MOD;
	cout<<ans<<endl;*/
	return 0;
}