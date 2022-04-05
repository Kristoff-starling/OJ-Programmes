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

LL val[20048];
int ind[31][31][31][31],Ind;
vector<int> v[20048];
LL dp[20048];

int dfn[20048],low[20048],ii;
stack<int> s;
bool visited[20048];int tot;
int bel[20048];
LL c[48][48];

inline void init_c(int lim)
{
	c[0][0]=1;int i,j;
	for (i=1;i<=lim;i++)
	{
		c[i][0]=c[i][i]=1;
		for (j=1;j<=i-1;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
}

inline LL calc(int c1,int c2,int c3,int c4)
{
	int k=c1+c2+c3+c4;
	return c[k][c1]*c[k-c1][c2]*c[k-c1-c2][c3];
}

inline void tarjan(int cur)
{
	s.push(cur);
	dfn[cur]=low[cur]=++ii;
	visited[cur]=true;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (!dfn[y])
		{
			tarjan(y);
			low[cur]=min(low[cur],low[y]);
		}
		else if (visited[y]) low[cur]=min(low[cur],dfn[y]);
	}
	if (dfn[cur]==low[cur])
	{
		int v1;++tot;
		do
		{
			v1=s.top();s.pop();
			bel[v1]=tot;
			val[tot]+=val[v1];
			visited[v1]=false;
		}
		while (v1!=cur);
	}
}

inline void Clear()
{
	Ind=0;ii=0;
	memset(visited,false,sizeof(visited));
	memset(val,0,sizeof(val));
	memset(ind,0,sizeof(ind));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(dp,0,sizeof(dp));
	for (register int i=1;i<=20000;i++) v[i].clear();
}

inline LL solve(int cur)
{
	if (dp[cur]) return dp[cur];
	dp[cur]=val[cur];int i,y;LL maxn=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (solve(y)>maxn) maxn=solve(y);
	}
	dp[cur]+=maxn;
	return dp[cur];
}

class ImpossibleGame
{
	public:
		inline LL getMinimum(int k,vector<string> before,vector<string> after)
		{
			int i,j,m,p;
			int c[5],toc[5];
			init_c(k);Clear();
			for (i=0;i<=k;i++)
				for (j=0;j<=k;j++)
					for (m=0;m<=k;m++)
						if (i+j+m<=k)
						{
							ind[i][j][m][k-i-j-m]=++Ind;
							val[Ind]=calc(i,j,m,k-i-j-m);
						}
			for (int tmp=0;tmp<int(before.size());tmp++)
			{
				memset(c,0,sizeof(c));memset(toc,0,sizeof(toc));
				for (j=0;j<=int(before[tmp].size())-1;j++) c[before[tmp][j]-'A'+1]++;
				for (j=0;j<=int(after[tmp].size())-1;j++) toc[after[tmp][j]-'A'+1]++;
				if (c[1]==toc[1] && c[2]==toc[2] && c[3]==toc[3]) continue;
				for (i=c[1];i<=k;i++)
					for (j=c[2];j<=k;j++)
						for (m=c[3];m<=k;m++)
							if (k-i-j-m>=c[4])
								v[ind[i][j][m][k-i-j-m]].pb(ind[i-c[1]+toc[1]][j-c[2]+toc[2]][m-c[3]+toc[3]][k-i-j-m-c[4]+toc[4]]);
			}
			tot=Ind;
			for (i=1;i<=Ind;i++)
				if (!dfn[i]) tarjan(i);
			for (i=1;i<=Ind;i++)
				for (j=0;j<int(v[i].size());j++)
					if (bel[i]!=bel[v[i][j]]) v[bel[i]].pb(bel[v[i][j]]);
			LL res=0;
			for (i=Ind+1;i<=tot;i++) dp[i]=solve(i),res=max(res,dp[i]);
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int kk,nn;
	vector<string> v1,v2;
	ImpossibleGame A;
	while (cin>>kk>>nn)
	{
		int i;
		v1.clear();v2.clear();string s;
		for (i=1;i<=nn;i++) cin>>s,v1.pb(s);
		for (i=1;i<=nn;i++) cin>>s,v2.pb(s);
		cout<<A.getMinimum(kk,v1,v2)<<endl;
	}
	return 0;
}
*/
/*
6 6
AABBC
AAAADA
AAACA
CABAA
AAAAAA
BAAAA
AACCB
DAAABC
AAAAD
ABCBA
AABAAA
AACAA
*/
