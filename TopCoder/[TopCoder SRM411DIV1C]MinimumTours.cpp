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

int n,m;
bool island[10048];
vector<int> v[10048];
vector<Pair> node[10048];
int num[88][88];
int mve[10][3];
int tot=0;
int ans;
int a[88][88];

struct MinimumTours
{
	void Clear()
	{
		int i,j;
		for (i=1;i<=tot;i++) v[i].clear(),node[i].clear();
		tot=0;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				num[i][j]=0;
		ans=0;
	}
	void init_move()
	{
		mve[1][1]=-1;mve[1][2]=0;
		mve[2][1]=-1;mve[2][2]=1;
		mve[3][1]=0;mve[3][2]=1;
		mve[4][1]=1;mve[4][2]=1;
		mve[5][1]=1;mve[5][2]=0;
		mve[6][1]=1;mve[6][2]=-1;
		mve[7][1]=0;mve[7][2]=-1;
		mve[8][1]=-1;mve[8][2]=-1;
	}
	void dfs(int x,int y,int ind)
	{
		num[x][y]=ind;
		node[ind].pb(mp(x,y));
		int i;
		int xx,yy;
		for (i=1;i<=8;i++)
		{
			xx=x+mve[i][1];yy=y+mve[i][2];
			if (1<=xx && xx<=n && 1<=yy && yy<=m && !num[xx][yy] && a[xx][yy]==a[x][y])
				dfs(xx,yy,ind);
		}
	}
	int Dfs(int cur,int father)
	{
		//cout<<cur<<endl;
		int cnt1=0,cnt2=0,i;
		for (i=0;i<int(v[cur].size());i++)
			if (v[cur][i]!=father)
			{
				int res=Dfs(v[cur][i],cur);
				if (res==1) cnt1++;
				if (res==2) cnt2++;
			}
		if (island[cur])
		{
			if (cnt1)
			{
				ans+=cnt1-1;
				return cnt1==1;
			}
			else
			{
				if (cnt2) return 0; else return 2;
			}
		}
		else
		{
			if (!cnt1) return cnt2>0;
			ans+=(cnt1>>1);
			return (cnt1&1)?1:2;
		}
	}
	int getMinimumTours(vector<string> s)
	{
		int i,j,dir,xx,yy;
		n=int(s.size());m=int(s[0].size());
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				a[i][j]=(s[i-1][j-1]=='.'?0:1);
		Clear();init_move();
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (!num[i][j])
				{
					island[++tot]=(s[i-1][j-1]=='x'?1:0);
					dfs(i,j,tot);
				}
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				for (dir=1;dir<=8;dir++)
				{
					xx=i+mve[dir][1];yy=j+mve[dir][2];
					if (1<=xx && xx<=n && 1<=yy && yy<=m && num[xx][yy]!=num[i][j])
						v[num[i][j]].pb(num[xx][yy]);
				}
		for (i=1;i<=tot;i++)
		{
			sort(v[i].begin(),v[i].end());
			v[i].resize(unique(v[i].begin(),v[i].end())-v[i].begin());
		}
		int ss=1;
		while (ss<=tot && !island[ss]) ss++;
		int res=Dfs(ss,-1);
		if (res) ans++;
		return ans;
	}
};

/*---Debug Part---*/
/*int main ()
{
	freopen ("data.in","r",stdin);
	vector<string> s;
	string ins;
	while (cin>>ins) s.pb(ins);
	cout<<A.getMinimumTours(s)<<endl;
	return 0;
}*/