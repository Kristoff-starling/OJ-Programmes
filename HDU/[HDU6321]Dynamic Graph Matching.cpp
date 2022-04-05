#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline char Getchar()
{
	char ch=getchar();
	while (ch!='+' && ch!='-') ch=getchar();
	return ch;
}

int n,m;

int dp[2000];
int ans[20];
vector<int> valid;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline void update(int Mask1,int Mask2,int fl)
{
	ans[__builtin_popcount(Mask1)>>1]=sub(ans[__builtin_popcount(Mask1)>>1]-dp[Mask1]);
	if (fl==1) dp[Mask1]=add(dp[Mask1]+dp[Mask2]); else dp[Mask1]=sub(dp[Mask1]-dp[Mask2]);
	ans[__builtin_popcount(Mask1)>>1]=add(ans[__builtin_popcount(Mask1)>>1]+dp[Mask1]);
}

int main ()
{
	int i,ca=ca=getint();
	char ch;int x,y;
	while (ca--)
	{
		n=getint();m=getint();
		memset(dp,0,sizeof(dp));dp[0]=1;
		valid.clear();
		for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
			if (!(__builtin_popcount(Mask)&1)) valid.pb(Mask);
		memset(ans,0,sizeof(ans));
		while (m--)
		{
			ch=Getchar();x=getint();y=getint();
			if (ch=='+')
			{
				for (auto Mask : valid)
				{
					if (Mask&(1<<(x-1)) || Mask&(1<<(y-1))) continue;
					update(Mask|(1<<(x-1))|(1<<(y-1)),Mask,1);
				}
			}
			else
			{
				for (auto Mask : valid)
				{
					if (Mask&(1<<(x-1)) || Mask&(1<<(y-1))) continue;
					update(Mask|(1<<(x-1))|(1<<(y-1)),Mask,-1);
				}
			}
			for (i=1;i<=n/2;i++) printf(i==n/2?"%d":"%d ",ans[i]);
			puts("");
		}
	}
	return 0;
}
