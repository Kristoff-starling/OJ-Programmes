#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
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

class FlippingBitsDiv1
{
	char s[1048];int n,m;
	inline int solve_simple()
	{
		int len=n-m,res=INF,cnt=0;
		for (register int i=1;i<=len;i++)
			if (s[i]!=s[n-len+i]) cnt++;
		res=min(res,cnt);
		cnt=0;
		for (register int i=1;i<=len;i++)
			if (s[i]==s[n-len+i]) cnt++;
		res=min(res,cnt+1);
		return res;
	}
	int cc[348][2];int N;
	int dp[348][2][2];
	int Mask0[348],cnt[348];
	inline int calc(int st,int sta,int Mask)
	{
		if (sta) Mask^=((1<<m)-1);int cnt=0;
		int ll=(st==N?n-(st-1)*m:m);
		for (register int i=1;i<=ll;i++) if (s[(st-1)*m+i]-'0'!=(Mask&(1<<(i-1))?1:0)) cnt++;
		return cnt;
	}
	inline int Calc(int Mask)
	{
		int cnt=0;
		for (register int i=1;i<=N-1;i++)
			if ((Mask&(1<<(i-1))?1:0)^(Mask&(1<<i)?1:0)) cnt++;
		if (Mask&(1<<(N-1))) cnt++;
		return cnt;
	}
	//0: not reverse; 1:reverse
	public:
		inline int getmin(vector<string> S,int M)
		{
			string ss="";int i,j,k,p,q,chosen;
			for (i=0;i<int(S.size());i++) ss+=S[i];
			n=int(ss.size());for (i=1;i<=n;i++) s[i]=ss[i-1];
			m=M;
			if (m>n/2) return solve_simple();
			N=n/m;if (n%m) N++;
			int ans=INF;
			if (m<=17)
			{
				for (int Mask=0;Mask<=(1<<m)-1;Mask++)
				{
					for (i=1;i<=N;i++)
						for (j=0;j<=1;j++)
							cc[i][j]=calc(i,j,Mask);
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
										if (i==N && n%m && j==1) continue;
										int add=0;
										if (!p && j && i!=1) add++;
										if (!j && p) add++;
										add+=cc[i][j];
										dp[i][j][k]=min(dp[i][j][k],dp[i-1][p][q]+add);
									}
					ans=min(ans,min(dp[N][0][0],dp[N][1][0]));
					ans=min(ans,dp[N][1][1]+1);
				}
				return ans;
			}
			else
			{
				for (i=1;i<=m;i++) Mask0[i]=0,cnt[i]=0;
				for (i=1;i<=n;i++)
				{
					if (s[i]=='1') Mask0[(i-1)%m+1]|=(1<<((i-1)/m));
					cnt[(i-1)%m+1]++;
				}
				for (int Mask=0;Mask<=(1<<N)-1;Mask++)
				{
					if (Mask&(1<<(N-1)) && n%m) continue;
					int curans=Calc(Mask);
					for (i=1;i<=m;i++)
					{
						int nMask=(Mask0[i]^Mask);
						int c1=__builtin_popcount(nMask),c0=cnt[i]-c1;
						curans+=min(c0,c1);
					}
					ans=min(ans,curans);
				}
				return ans;
			}
		}
};

/*---Debug Part---*/
/*
int main ()
{
	FlippingBitsDiv1 A;
	string s;int n,m;vector<string> vv;
	while (cin>>n)
	{
		vv.clear();
		while (n--) cin>>s,vv.pb(s);
		cin>>m;
		cout<<A.getmin(vv,m)<<endl;
	}
	return 0;
}*/
/*
0110110011000011
1101000100011001
0000000101001001
0010011111000110
0100011001110001
0111100101110011
1010001111110001
0000110110101001
1001001001001111
1001110111111001
1010000111001101
0111111111010110
1100101010010001
010001110000101101100100101101000111011111", "10111101101111101011011011010100111011100001101001"}, 17}
*/

