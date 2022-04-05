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

const LL MOD=1e9+7;
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

LL num[548];
int seq[548],pt,pos[548];
LL dp[548][548][15];
LL inv[20];

struct IncreasingNumber
{
	void Clear()
	{
		memset(num,0ll,sizeof(num));
		memset(pos,0,sizeof(pos));
		pt=0;
	}
	inline LL quick_pow(LL x,LL y)
	{
		LL res=1;x%=MOD;
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
	void init_inv()
	{
		for (int i=1;i<=15;i++) inv[i]=quick_pow(i,MOD-2);
	}
	LL C(LL n,LL k)
	{
		if (k==0) return 1ll;
		if (n<k) return 0ll;
		LL res=1;
		for (LL i=n;i>=n-k+1;i--) res=(res*(i%MOD))%MOD;
		for (LL i=k;i>=1;i--) res=(res*inv[i])%MOD;
		return res;
	}
	int init_num(LL digits,int divisor)
	{
		int i,cur=0;bool iscircled=false;
		for (i=1;i<=min((long long)(divisor+48),digits);i++)
		{
			cur=(cur*10+1)%divisor;
			if (!pos[cur]) {pos[cur]=++pt;seq[pt]=(cur==0?divisor:cur);} else {iscircled=true;break;}
		}
		if (!iscircled)
		{
			for (i=1;i<=pt;i++) num[seq[i]]++;
			return seq[pt];
		}
		int l=pos[cur],r=pt;LL need=digits;
		for (i=1;i<=l-1;i++) num[seq[i]]++;
		need-=(l-1);
		LL add=need/(r-l+1);
		for (i=l;i<=r;i++) num[seq[i]]+=add;
		need-=add*(r-l+1);
		if (need==0) return seq[r];
		for (i=l;i<=l+need-1;i++) num[seq[i]]++;
		return seq[l+need-1];
	}
	int countNumbers(LL digits,int divisor)
	{
		Clear();init_inv();
		int last=init_num(digits,divisor)%divisor,i,j,k,m,to;
		memset(dp,0ll,sizeof(dp));
		dp[0][last][1]=1;
		for (i=0;i<=divisor-1;i++)
			for (j=0;j<=divisor-1;j++)
				for (k=1;k<=9;k++)
					if (dp[i][j][k])
						for (m=0;m<=9-k;m++)
						{
							to=(j+m*(i+1))%divisor;
							//cout<<num[i+1]+m-1<<' '<<m<<' '<<C(num[i+1]+m-1,m)<<endl;
							//cout<<i+1<<' '<<to<<' '<<k+m<<endl<<endl;
							dp[i+1][to][k+m]=(dp[i+1][to][k+m]+(dp[i][j][k]*C(num[i+1]+m-1,m))%MOD)%MOD;
						}
		LL res=0;
		for (i=1;i<=9;i++) res=(res+dp[divisor][0][i])%MOD;
		return res;
	}
};

/*---Debug Part---*/
/*int main ()
{
	//freopen ("data.in","r",stdin);
	//freopen ("1.out","w",stdout);
	LL digits;int divisor;
	IncreasingNumber A;
	while (scanf("%lld%d",&digits,&divisor)!=EOF)
		cout<<A.countNumbers(digits,divisor)<<endl;
	return 0;
}*/