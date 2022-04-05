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

class MagicianTour
{
	public:
		Pair a[58];int n,cnt=0;
		int color[58];bool dp[58][6048];
		const int BASE=1968;
		vector<int> v[58];int popu[58];
		inline void Clear()
		{
			for (int i=1;i<=n;i++) v[i].clear();
			cnt=0;
			memset(color,0,sizeof(color));
			memset(dp,false,sizeof(dp));
		}
		inline void dfs(int cur)
		{
			int i;
			for (i=0;i<int(v[cur].size());i++)
				if (!color[v[cur][i]])
				{
					color[v[cur][i]]=3-color[cur];
					if (color[v[cur][i]]==1) a[cnt].x+=popu[v[cur][i]]; else a[cnt].y+=popu[v[cur][i]];
					dfs(v[cur][i]);
				}
		}
		inline int bestDifference(vector<string> roads,vector<int> populations)
		{
			int i,j;
			n=int(populations.size());Clear();
			for (i=1;i<=n;i++)
				for (j=1;j<=n;j++)
					if (i!=j && roads[i-1][j-1]=='1') v[i].pb(j);
			for (i=1;i<=n;i++) popu[i]=populations[i-1];
			for (i=1;i<=n;i++)
				if (!color[i])
				{
					cnt++;a[cnt]=mp(popu[i],0);color[i]=1;
					dfs(i);
				}
			dp[0][BASE]=true;
			for (i=0;i<=cnt-1;i++)
				for (j=BASE-n*20-48;j<=BASE+n*20+48;j++)
					if (dp[i][j])
					{
						dp[i+1][j+a[i+1].x-a[i+1].y]=true;
						dp[i+1][j-a[i+1].x+a[i+1].y]=true;
					}
			int ans=INF,pt;
			for (pt=BASE;!dp[cnt][pt];pt++) {}
			ans=min(ans,pt-BASE);
			for (pt=BASE;!dp[cnt][pt];pt--) {}
			ans=min(ans,BASE-pt);
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn;
	vector<string> rr;
	vector<int> pp;
	MagicianTour A;
	while (scanf("%d",&nn)!=EOF)
	{
		rr.clear();pp.clear();string s;int i,x;
		for (i=1;i<=nn;i++) cin>>s,rr.pb(s);
		for (i=1;i<=nn;i++) cin>>x,pp.pb(x);
		cout<<A.bestDifference(rr,pp)<<endl;
	}
	return 0;
}
*/
