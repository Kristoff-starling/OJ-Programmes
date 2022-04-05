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

int n;
int a[58],b[58];
bool Dp[58][58];
int valid[58],vtot;
int anslist[58],tot;

inline bool judge()
{
	int res=-1;
	int i,j,k,cc;
	for (i=1;i<=n;i++)
	{
		memset(Dp,false,sizeof(Dp));
		Dp[0][a[i]]=true;
		for (j=0;j<=vtot-1;j++)
			for (k=0;k<=50;k++)
				if (Dp[j][k])
				{
					Dp[j+1][k]=true;
					Dp[j+1][k%valid[j+1]]=true;
				}
		if (!Dp[vtot][b[i]]) return false;
	}
	return true;
}

int main ()
{
	n=getint();int i,calc;
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++) b[i]=getint();
	for (i=1;i<=n;i++) if (b[i]*2+1>a[i] && b[i]!=a[i]) {printf("-1\n");return 0;}
	tot=0;
	for (calc=50;calc>0;calc--)
	{
		vtot=0;for (i=1;i<=tot;i++) valid[++vtot]=anslist[i];
		for (i=calc-1;i;i--) valid[++vtot]=i;
		if (judge()) continue;
		anslist[++tot]=calc;
	}
	LL ans=0;for (i=1;i<=tot;i++) ans+=(1ll<<anslist[i]);
	printf("%lld\n",ans);
	return 0;
}
