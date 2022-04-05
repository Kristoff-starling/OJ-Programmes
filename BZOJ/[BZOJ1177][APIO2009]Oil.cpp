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

const int INF=1.5e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

const int MAXN=1500;

int n,m,k;
int a[MAXN+48][MAXN+48],sum[MAXN+48][MAXN+48],b[MAXN+48][MAXN+48];
int maxn1[4][MAXN+48][MAXN+48],maxn2[4][MAXN+48];

inline int query(int x1,int y1,int x2,int y2)
{
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
}

int main ()
{
	int i,j,p;
	scanf("%d%d%d",&n,&m,&k);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for (i=1;i<=n;i++)
	{
		sum[i][0]=0;
		for (j=1;j<=m;j++) sum[i][j]=sum[i][j-1]+a[i][j];
	}
	for (i=2;i<=n;i++)
		for (j=1;j<=m;j++)
			sum[i][j]+=sum[i-1][j];
	for (i=1;i<=n-k+1;i++)
		for (j=1;j<=m-k+1;j++)
			b[i][j]=query(i,j,i+k-1,j+k-1);
	for (p=0;p<=3;p++)
		for (i=0;i<=n+1;i++)
			for (j=0;j<=m+1;j++)
				maxn1[p][i][j]=-INF;
	for (i=1;i<=n-k+1;i++)
		for (j=1;j<=m-k+1;j++)
		{
			maxn1[0][i+k-1][j+k-1]=max(maxn1[0][i][j],b[i][j]);
			maxn1[1][i+k-1][j]=max(maxn1[1][i+k-1][j],b[i][j]);
			maxn1[2][i][j+k-1]=max(maxn1[2][i][j+k-1],b[i][j]);
			maxn1[3][i][j]=max(maxn1[3][i][j],b[i][j]);
		}
	for (i=1;i<=n;i++)
		for (j=2;j<=m;j++)
		{
			maxn1[0][i][j]=max(maxn1[0][i][j],maxn1[0][i][j-1]);
			maxn1[2][i][j]=max(maxn1[2][i][j],maxn1[2][i][j-1]);
		}
	for (i=1;i<=n;i++)
		for (j=m-1;j>=1;j--)
		{
			maxn1[1][i][j]=max(maxn1[1][i][j],maxn1[1][i][j+1]);
			maxn1[3][i][j]=max(maxn1[3][i][j],maxn1[3][i][j+1]);
		}
	for (i=2;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			maxn1[0][i][j]=max(maxn1[0][i][j],maxn1[0][i-1][j]);
			maxn1[1][i][j]=max(maxn1[1][i][j],maxn1[1][i-1][j]);
		}
	for (i=n-1;i>=1;i--)
		for (j=1;j<=m;j++)
		{
			maxn1[2][i][j]=max(maxn1[2][i][j],maxn1[2][i+1][j]);
			maxn1[3][i][j]=max(maxn1[3][i][j],maxn1[3][i+1][j]);
		}
	for (i=0;i<=3;i++)
		for (j=1;j<=max(n,m);j++)
			maxn2[i][j]=-INF;
	for (i=k;i<=n;i++)
		for (j=1;j<=m-k+1;j++)
			maxn2[0][i]=max(maxn2[0][i],b[i-k+1][j]+max(maxn1[0][i-k][m],max(maxn1[0][i][j-1],maxn1[1][i][j+k])));
	for (i=2;i<=n;i++) maxn2[0][i]=max(maxn2[0][i],maxn2[0][i-1]);
	for (i=n-k+1;i>=1;i--)
		for (j=1;j<=m-k+1;j++)
			maxn2[1][i]=max(maxn2[1][i],b[i][j]+max(maxn1[2][i+k][m],max(maxn1[2][i][j-1],maxn1[3][i][j+k])));
	for (i=n-1;i>=1;i--) maxn2[1][i]=max(maxn2[1][i],maxn2[1][i+1]);
	for (j=k;j<=m;j++)
		for (i=1;i<=n-k+1;i++)
			maxn2[2][j]=max(maxn2[2][j],b[i][j-k+1]+max(maxn1[0][n][j-k],max(maxn1[0][i-1][j],maxn1[2][i+k][j])));
	for (j=2;j<=m;j++) maxn2[3][j]=max(maxn2[3][j],maxn2[3][j-1]);
	for (j=m-k+1;j>=1;j--)
		for (i=1;i<=n-k+1;i++)
			maxn2[3][j]=max(maxn2[3][j],b[i][j]+max(maxn1[1][n][j+k],max(maxn1[1][i-1][j],maxn1[3][i+k][j])));
	for (j=m-1;j>=1;j--) maxn2[3][j]=max(maxn2[3][j],maxn2[3][j+1]);
	int ans=0;
	for (i=1;i<=n-k+1;i++)
		for (j=1;j<=m-k+1;j++)
			ans=max(ans,max(max(b[i][j]+maxn2[0][i-1],b[i][j]+maxn2[1][i+k]),max(b[i][j]+maxn2[2][j-1],b[i][j]+maxn2[3][j+k])));
	printf("%d\n",ans);
	return 0;
}
