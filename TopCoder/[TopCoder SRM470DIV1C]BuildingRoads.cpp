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

int score[300];
int dp[51][51][1024],Dp[1024],DP[1024];
char table[48];
int n,m,k;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

struct BuildingRoads
{
	inline void Clear()
	{
		int i,j,Mask;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				for (Mask=0;Mask<=(1<<k)-1;Mask++)
					dp[i][j][Mask]=INF;
		for (Mask=0;Mask<=(1<<k)-1;Mask++) Dp[Mask]=DP[Mask]=INF;
	}
	inline void init_score()
	{
		memset(score,0,sizeof(score));
		score['.']=0;
		for (int i=1;i<=26;i++) score['a'+i-1]=i;
		for (int i=1;i<=26;i++) score['A'+i-1]=i*100;
		for (int i=1;i<=9;i++) score['0'+i]=i*10000;
		score['0']=100000;
	}
	inline bool check_home(char ch)
	{
		if (ch=='!' || ch=='@' || ch=='#' || ch=='$') return true;
		return false;
	}
	bool inq[51][51];queue<int> q;
	char Mp[148][148];
	inline void spfa(int Mask)
	{
		int i,x,y,xx,yy;
		while (!q.empty())
		{
			x=q.front();q.pop();y=q.front();q.pop();inq[x][y]=false;
			for (i=0;i<=3;i++)
			{
				xx=x+dx[i];yy=y+dy[i];
				if (xx<1 || xx>n || yy<1 || yy>m) continue;
				int add=(Mp[x][y]==Mp[xx][yy]?0:score[Mp[xx][yy]]);
				if (dp[xx][yy][Mask]>dp[x][y][Mask]+add)
				{
					dp[xx][yy][Mask]=dp[x][y][Mask]+add;
					if (!inq[xx][yy]) inq[xx][yy]=true,q.push(xx),q.push(yy);
				}
			}
		}
	}
	inline bool check_Mask(int Mask)
	{
		int visited[248];memset(visited,0,sizeof(visited));
		int i;
		for (i=1;i<=k;i++) if (Mask&(1<<(i-1))) visited[table[i]]^=1;
		for (i=0;i<=200;i++) if (visited[i]) return false;
		return true;
	}
	int destroyRocks(vector<string> a)
	{
		int i,j,Mask,sub,cc=0;
		n=int(a.size());m=int(a[0].size());
		k=0;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (check_home(a[i-1][j-1])) k++;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				Mp[i][j]=a[i-1][j-1];
		init_score();Clear();
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (check_home(a[i-1][j-1])) dp[i][j][1<<(cc++)]=0,table[cc]=a[i-1][j-1];
		for (Mask=1;Mask<=(1<<k)-1;Mask++)
		{
			for (i=1;i<=n;i++)
				for (j=1;j<=m;j++)
				{
					for (sub=(Mask-1)&Mask;sub;sub=Mask&(sub-1))
						if (dp[i][j][sub]+dp[i][j][Mask-sub]-score[Mp[i][j]]<dp[i][j][Mask])
							dp[i][j][Mask]=dp[i][j][sub]+dp[i][j][Mask-sub]-score[Mp[i][j]];
					if (dp[i][j][Mask]<INF) inq[i][j]=true,q.push(i),q.push(j);
				}
			spfa(Mask);
		}
		for (Mask=1;Mask<=(1<<k)-1;Mask++)
			for (i=1;i<=n;i++)
				for (j=1;j<=m;j++)
					Dp[Mask]=min(Dp[Mask],dp[i][j][Mask]);
		for (Mask=1;Mask<=(1<<k)-1;Mask++)
		{
			DP[Mask]=Dp[Mask];
			for (sub=Mask&(Mask-1);sub;sub=Mask&(sub-1))
				if (check_Mask(sub) && check_Mask(Mask-sub)) DP[Mask]=min(DP[Mask],DP[sub]+DP[Mask-sub]);
		}
		return DP[(1<<k)-1];
	}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,mm;BuildingRoads A;
	vector<string> v;string ins;
	while (scanf("%d%d",&nn,&mm)!=EOF)
	{
		int i;v.clear();
		for (i=1;i<=nn;i++)
		{
			cin>>ins;
			v.pb(ins);
		}
		cout<<A.DestroyRocks(v)<<endl;
	}
	return 0;
}
*/
