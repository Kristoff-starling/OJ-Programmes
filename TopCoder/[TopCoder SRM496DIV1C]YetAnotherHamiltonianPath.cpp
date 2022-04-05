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
const int INF=1e9;
const int magic=348;
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int dp[58][58][58][2];

class YetAnotherHamiltonianPath
{
	struct node
	{
		string label;
		int ind;
		inline bool operator < (const node &x) const{return label<x.label;}
	}s[58];
	int LCP[58],cost[58][58],sum[58][58];
	inline int pp(int x) {return x*x;}
	inline int query_lcp(string s1,string s2)
	{
		int res=0;
		while (res<=min(int(s1.size())-1,int(s2.size())-1) && s1[res]==s2[res]) res++;
		return res;
	}
	inline void init()
	{
		int i,j,k,l;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				for (k=1;k<=n;k++)
					for (l=0;l<=1;l++)
						dp[i][j][k][l]=-1;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				cost[i][j]=pp(query_lcp(s[i].label,s[j].label));
	}
	inline int solve(int st,int left,int right,int type)
	{
		if (dp[st][left][right][type]!=-1) return dp[st][left][right][type];
		if (!(left<=st && st<=right)) return -INF;
		if (left>=right) return 0;
		if (type==0)
			dp[st][left][right][type]=max(solve(st,left+1,right,type)+cost[left][left+1],solve(st,left+1,right,type^1)+cost[left][right]);
		else
			dp[st][left][right][type]=max(solve(st,left,right-1,type)+cost[right-1][right],solve(st,left,right-1,type^1)+cost[left][right]);
		return dp[st][left][right][type];
	}
	public:
		inline int leastCost(vector<string> label)
		{
			n=int(label.size())-2;int i,j,k,ll,lr,rl,rr,ans=0;
			if (!n) return pp(int(label[0].size()))+pp(int(label[1].size()))-pp(query_lcp(label[0],label[1]));
			for (i=1;i<=n;i++) s[i].label=label[i+1],s[i].ind=i;
			sort(s+1,s+n+1);init();
			for (i=1;i<=n-1;i++)
				for (j=i+1;j<=n;j++)
				{
					int curans=0;
					for (k=i;k<=j-1;k++)
					{
						ll=solve(i,1,k,0);lr=solve(i,1,k,1);rl=solve(j,k+1,n,0);rr=solve(j,k+1,n,1);
						curans=max(curans,ll+rl+cost[1][k+1]);
						curans=max(curans,ll+rr+cost[1][n]);
						curans=max(curans,lr+rl+cost[k][k+1]);
						curans=max(curans,lr+rr+cost[k][n]);
					}
					curans+=max(pp(query_lcp(label[0],s[i].label))+pp(query_lcp(label[1],s[j].label)),pp(query_lcp(label[0],s[j].label))+pp(query_lcp(label[1],s[i].label)));
					ans=max(ans,curans);
				}
			ans=-ans;
			for (i=0;i<int(label.size());i++)
				if (i==0 || i==1) ans+=pp(int(label[i].size())); else ans+=2*pp(int(label[i].size()));
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	vector<string> vv;int nn;
	YetAnotherHamiltonianPath A;
	while (cin>>nn)
	{
		vv.clear();string ss;
		while (nn--) cin>>ss,vv.pb(ss);
		cout<<A.leastCost(vv)<<endl;
	}
	return 0;
}
*/
