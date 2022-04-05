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
 
const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m,HP,MP,SP,DHP,DSP,DMP,X;
int a[1048];
int N1,N2;Pair b[148],c[148];

int dp1[1048][1048],dp2[1048][1048],dp3[1048][1048],DP1[1048],DP2[1048],DP3[1048],DP4[1048];

int main ()
{
	int i,j,k,ca;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();HP=getint();MP=getint();SP=getint();DHP=getint();DMP=getint();DSP=getint();X=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		N1=getint();for (i=1;i<=N1;i++) b[i].x=getint(),b[i].y=getint();
		N2=getint();for (i=1;i<=N2;i++) c[i].x=getint(),c[i].y=getint();
		memset(dp1,0,sizeof(dp1));memset(dp2,0,sizeof(dp2));memset(dp3,192,sizeof(dp3));
		memset(DP1,0,sizeof(DP1));memset(DP2,0,sizeof(DP2));memset(DP3,192,sizeof(DP3));
		dp3[1][HP]=1;
		for (i=1;i<=n+1;i++)
			for (j=1;j<=HP;j++)
			{
				DP3[i]=max(DP3[i],dp3[i][j]);
				if (i<=n)
				{
					if (j-a[i]>0) dp3[i+1][j-a[i]]=max(dp3[i+1][j-a[i]],dp3[i][j]+1);
					if (min(HP,j+DHP)-a[i]>0) dp3[i+1][min(HP,j+DHP)-a[i]]=max(dp3[i+1][min(HP,j+DHP)-a[i]],dp3[i][j]);
				}
			}
		dp1[0][SP]=0;
		for (i=0;i<=n;i++)
			for (j=0;j<=SP;j++)
			{
				DP1[i]=max(DP1[i],dp1[i][j]);
				if (i<n)
				{
					dp1[i+1][min(SP,j+DSP)]=max(dp1[i+1][min(SP,j+DSP)],dp1[i][j]+X);
					for (k=1;k<=N2;k++)
						if (j-c[k].x>=0) dp1[i+1][j-c[k].x]=max(dp1[i+1][j-c[k].x],dp1[i][j]+c[k].y);
				}
			}
		dp2[0][MP]=0;
		for (i=0;i<=n;i++)
			for (j=0;j<=MP;j++)
			{
				DP2[i]=max(DP2[i],dp2[i][j]);
				if (i<n)
				{
					dp2[i+1][min(j+DMP,MP)]=max(dp2[i+1][min(j+DMP,MP)],dp2[i][j]);
					for (k=1;k<=N1;k++)
						if (j-b[k].x>=0) dp2[i+1][j-b[k].x]=max(dp2[i+1][j-b[k].x],dp2[i][j]+b[k].y);
				}
			}
		int minneed=INF;
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				if (DP1[i]+DP2[j]>=m) minneed=min(minneed,i+j);
		bool f=false;
		for (i=1;i<=n;i++)
			if (DP3[i]>=minneed)
			{
				printf("Yes %d\n",i);
				f=true;break;
			}
		if (f) continue;
		if (DP3[n+1]>=0) printf("Tie\n"); else printf("No\n");
	}
	return 0;
}
