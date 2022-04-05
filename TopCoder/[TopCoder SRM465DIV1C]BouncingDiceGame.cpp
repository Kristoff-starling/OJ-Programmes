#include <bits/stdc++.h>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=998244353;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

double dp[2][5048],sum[2][5048];
double pwd[5048];

class BouncingDiceGame
{
	int n,d,st1,st2,lim;double ss,sss;
	public:
		inline double winProbability(int N,int D,int X,int Y)
		{
			n=N;d=D;st1=X;st2=Y;lim=n-d-1;
			int i,j,cur,pre;double ans=0;
			pwd[0]=1;for (i=1;i<=n;i++) pwd[i]=(pwd[i-1]*(double(1)-1.0/d));
			memset(dp,0,sizeof(dp));dp[0][n]=1;
			sum[0][n]=dp[0][n];for (i=n-1;i>=1;i--) sum[0][i]=sum[0][i+1]+dp[0][i];
			pre=0;cur=1;ss=0;sss=0;
			for (i=1;i<=lim;i++)
			{
				for (j=1;j<=n;j++)
				{
					if (j>=n-d) dp[cur][j]=pwd[i-1]*(1.0/d);
					else
					{
						dp[cur][j]=sum[pre][j+1];
						if (j+d+1<=n) dp[cur][j]-=sum[pre][j+d+1];
						dp[cur][j]/=d;
					}
				}
				sum[cur][n]=dp[cur][n];
				for (j=n-1;j>=1;j--) sum[cur][j]=sum[cur][j+1]+dp[cur][j];
				ans+=dp[cur][st1]*(double(1.0)-ss);
				ss+=dp[cur][st2];sss+=dp[cur][st1];
				swap(cur,pre);
			}
			ans+=(double(1.0)-sss)*(double(1.0)-ss)*double(d)*1.0/(2*d-1);
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	BouncingDiceGame A;
	int nn,dd,xx,yy;
	while (cin>>nn>>dd>>xx>>yy)
	{
		printf("%.10lf\n",A.winProbability(nn,dd,xx,yy));
	}
	return 0;
}
*/
