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

class RandomApple
{
	public:
		LL dp[500048],dp2[500048];int cnt[58][58];
		int n,k,sum=0;
		inline vector<double> theProbability(vector<string> hundred,vector<string> ten,vector<string> one)
		{
			int i,j;
			n=int(hundred.size());k=int(hundred[0].size());
			for (i=1;i<=n;i++)
			{
				cnt[i][0]=0;
				for (j=1;j<=k;j++)
				{
					cnt[i][j]=(hundred[i-1][j-1]-'0')*100+(ten[i-1][j-1]-'0')*10+one[i-1][j-1]-'0';
					sum+=cnt[i][j];cnt[i][0]+=cnt[i][j];
				}
			}
			memset(dp,0ll,sizeof(dp));
			dp[0]=1;
			for (i=1;i<=n;i++)
				for (j=sum;j>=0;j--)
					if (j-cnt[i][0]>=0) dp[j]+=dp[j-cnt[i][0]];
			vector<double> res(k,0);
			for (i=1;i<=n;i++)
			{
				memset(dp2,0ll,sizeof(dp2));double p=0;
				for (j=0;j<=sum;j++)
				{
					dp2[j]=dp[j];if (j>=cnt[i][0]) dp2[j]-=dp2[j-cnt[i][0]];
					p+=double(dp2[j])/((1ll<<n)-1)/(j+cnt[i][0]);
				}
				for (j=0;j<=k-1;j++)
					res[j]+=cnt[i][j+1]*p;
			}
			return res;
		}

};

/*---Debug Part---*/
/*
int main ()
{
	RandomApple A;
	vector<string> hh,tt,oo;
	int nn;
	while (scanf("%d",&nn)!=EOF)
	{
		string ins="";
		hh.clear();tt.clear();oo.clear();
		int i;
		for (i=1;i<=nn;i++) cin>>ins,hh.pb(ins);
		for (i=1;i<=nn;i++) cin>>ins,tt.pb(ins);
		for (i=1;i<=nn;i++) cin>>ins,oo.pb(ins);
		vector<double> res=A.theProbability(hh,tt,oo);
		for (i=0;i<int(res.size());i++) printf("%.10lf ",res[i]);
		cout<<endl;
	}
	return 0;
}
*/
