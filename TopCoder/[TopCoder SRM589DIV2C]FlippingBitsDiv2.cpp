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

const int INF=1e9;
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

const int MAXN=2500;

class FlippingBitsDiv2
{
	int a[MAXN+48];string s;int m,n;
	int cnt0[MAXN+48],cnt1[MAXN+48],N;
	int dp[MAXN+48][2][2];
	public:
		inline int getmin(vector<string> S,int M)
		{
			m=M;s="";int i,j,k,p,q;
			for (i=0;i<int(S.size());i++) s+=S[i];
			for (i=0;i<=int(s.size())-1;i++) a[i+1]=s[i]-'0';
			n=int(s.size());N=n/m;
			for (i=1;i<=N;i++)
			{
				cnt0[i]=cnt1[i]=0;
				for (j=(i-1)*m+1;j<=i*m;j++)
					if (a[j]==0) cnt0[i]++; else cnt1[i]++;
			}
			for (i=0;i<=N;i++)
				for (j=0;j<=1;j++)
					for (k=0;k<=1;k++)
						dp[i][j][k]=INF;
			dp[0][0][1]=0;
			for (i=1;i<=N;i++)
				for (j=0;j<=1;j++)
					for (k=0;k<=1;k++)
						for (p=0;p<=1;p++)
							for (q=0;q<=1;q++)
							{
								if (k==1 && q==0) continue;
								if (k==1 && j==0) continue;
								if (k==0 && j==1 && q==1) continue;
								int add=0;
								if (!p && j && i!=1) add++;
								if (!j && p) add++;
								if (!j) add+=cnt0[i]; else add+=cnt1[i];
								dp[i][j][k]=min(dp[i][j][k],dp[i-1][p][q]+add);
							}
			int res=min(dp[N][0][0],dp[N][1][0]);
			int C0=0,C1=0;for (i=1;i<=N;i++) C0+=cnt0[i],C1+=cnt1[i];
			res=min(res,min(C0,C1+1));
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
 	FlippingBitsDiv2 A;
	int nn;vector<string> vv;int kk;
	while (cin>>nn)
	{
		vv.clear();string ss;
		while (nn--) cin>>ss,vv.pb(ss);
		cin>>kk;
		printf("%d\n",A.getmin(vv,kk));
	}
	return 0;
}
*/
/*
10
00010
11010110
1010111
110001010
0110001100
000110110
011010101
00
111
100
13
*/
