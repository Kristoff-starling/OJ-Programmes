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

const int MOD=1e9+9;
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

class KingdomTour
{
	public:
		vector<Pair> v[1048];
		int dp[248][248],tmp[248][248];
		int N,M;
		inline void Clear(int n) {for (int i=1;i<=n;i++) v[i].clear();}
		inline int STRING_TO_INT(string s)
		{
			int res=0,i;
			for (i=0;i<int(s.size());i++) res=res*10+s[i]-'0';
			return res;
		}
		inline void addedge(string s)
		{
			int pos,pos1,i,a[5];s+=" ";int len=int(s.size());
			for (i=1,pos=0;pos<=len-1;pos=pos1+1,i++)
			{
				pos1=s.find(' ',pos);
				a[i]=STRING_TO_INT(s.substr(pos,pos1-pos))+(i<3?1:0);
			}
			v[a[1]].pb(mp(a[2],a[3]));v[a[2]].pb(mp(a[1],a[3]));
		}
		inline void doit_roads(vector<string> roads)
		{
			int i,pos,pos1;string s="";
			for (i=0;i<int(roads.size());i++) s+=roads[i];
			s+=",";pos=0;int len=int(s.size());
			while (pos<=len-1)
			{
				pos1=s.find(',',pos);
				addedge(s.substr(pos,pos1-pos));
				pos=pos1+1;
			}
		}
		inline void dfs(int cur,int father)
		{
			int i,j,k,y,cc=0;
			for (i=0;i<int(v[cur].size());i++)
			{
				y=v[cur][i].x;
				if (y!=father) dfs(y,cur);
			}
			for (i=0;i<=M;i++) tmp[0][i]=0;
			for (i=0;i<int(v[cur].size());i++)
			{
				y=v[cur][i].x;
				if (y!=father)
				{
					cc++;
					for (j=0;j<=M;j++)
					{
						tmp[cc][j]=INF;
						for (k=0;k<=j;k++)
							tmp[cc][j]=min(tmp[cc][j],tmp[cc-1][j-k]+dp[y][k]+((k&1)?v[cur][i].y:v[cur][i].y*2));
					}
				}
			}
			for (i=0;i<=M;i++) dp[cur][i]=tmp[cc][i];
		}
		inline int minTime(int n,vector<string> roads,int K,int L)
		{
			int i,j;
			Clear(n);
			doit_roads(roads);
			N=n;M=K*2;
			for (i=1;i<=N;i++)
				for (j=0;j<=M;j++)
					dp[i][j]=INF;
			dfs(1,-1);
			int res=INF;
			for (i=0;i<=M;i+=2) res=min(res,dp[1][i]+L*(i>>1));
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	vector<string> v;
	int nn,kk,ll;string s;
	KingdomTour A;
	while (scanf("%d%d%d",&nn,&kk,&ll)!=EOF)
	{
		int num;num=getint();v.clear();
		while (num--) getline(cin,s),v.pb(s);
		cout<<A.minTime(nn,v,kk,ll);
	}
	return 0;
}
10 2 4 3
1 2 2,4 1 9,2 5 5,6 5 4,
1 7 7,7 3 1,2 0 2 
,5 8 5,9 5 6
*/
