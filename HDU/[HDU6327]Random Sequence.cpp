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
const int amgic=348;
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

const int MAXN=100;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

inline int gcd(int x,int y) {return y==0?x:gcd(y,x%y);}
int g[MAXN+48][MAXN+48];
inline void init_g() {for (register int i=1;i<=MAXN;i++) for (register int j=1;j<=MAXN;j++) g[i][j]=gcd(i,j);}

int n,m;
int a[MAXN+48],v[MAXN+48];
int dp[2][MAXN+48][MAXN+48][MAXN+48];

int main ()
{
	int num,i,j,k,ca,cnt;ca=getint();init_g();
	while (ca--)
	{
		n=getint();m=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		for (i=1;i<=m;i++) v[i]=getint();
		memset(dp,0,sizeof(dp));
		cnt=3;
		for (i=1;i<=m;i++)
			for (j=1;j<=m;j++)
				for (k=1;k<=m;k++)
				{
					int x=(a[1]?a[1]:i),y=(a[2]?a[2]:j),z=(a[3]?a[3]:k);
					y=g[y][z];x=g[x][y];
					dp[0][x][y][z]++;
				}
		int cur=0,nxt=1;
		for (num=3;num<=n-1;num++)
		{
			if (!a[num+1]) cnt++;
			for (i=1;i<=m;i++)
				for (j=i;j<=m;j+=i)
					for (k=j;k<=m;k+=j)
						dp[nxt][i][j][k]=0;
			for (i=1;i<=m;i++)
				for (j=i;j<=m;j+=i)
					for (k=j;k<=m;k+=j)
						if (dp[cur][i][j][k])
							if (a[num+1])
							{
								int z=a[num+1],y=g[z][k],x=g[z][j],Cu=v[g[i][a[num+1]]];
								dp[nxt][x][y][z]=add(dp[nxt][x][y][z]+(1ll*dp[cur][i][j][k]*Cu)%MOD);
							}
							else
							{
								for (register int cc=1;cc<=m;cc++)
								{
									int y=g[cc][k],x=g[cc][j],Cu=v[g[i][cc]];
									dp[nxt][x][y][cc]=add(dp[nxt][x][y][cc]+(1ll*dp[cur][i][j][k]*Cu)%MOD);
								}
							}
			cur^=1;nxt^=1;
		}
		int ans=0;
		for (i=1;i<=m;i++)
			for (j=i;j<=m;j+=i)
				for (k=j;k<=m;k+=j)
					ans=add(ans+dp[cur][i][j][k]);
		ans=(1ll*ans*quick_pow(quick_pow(m,cnt),MOD-2))%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
