#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

bool inq[5000048];
pair<int,Pair> dp[5000048];
int n,e;
vector<int> v[48];
queue<int> q;

int Create(int x)
{
	int res=0;
	res|=(1<<(x-1));
	for (int i=0;i<v[x].size();i++)
		res|=(1<<(v[x][i]-1));
	return res;
}

void print(int ind)
{
	//printf("%d ",dp[ind].y.x);
	if (dp[ind].y.y!=-1) print(dp[ind].y.y);
	if (dp[ind].y.x!=-1) printf("%d ",dp[ind].y.x);
}

int main ()
{
	int i,x,y,Mask,toMask;
	n=getint();e=getint();
	if (e==n*(n-1)/2)
	{
		cout<<0<<endl;
		return 0;
	}
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	for (i=0;i<=(1<<n);i++) dp[i]=mp(INF,mp(-1,-1));
	dp[0]=mp(0,mp(-1,-1));
	q.push(0);inq[0]=true;
	while (!q.empty())
	{
		Mask=q.front();q.pop();
		inq[Mask]=false;
		if (Mask==0)
		{
			for (i=1;i<=n;i++)
			{
				toMask=Create(i);
				dp[toMask]=mp(1,mp(i,0));
				q.push(toMask);inq[toMask]=true;
			}
		}
		else
		{
			for (i=1;i<=n;i++)
				if (Mask&(1<<(i-1)))
				{
					toMask=Create(i);
					toMask|=Mask;
					if (dp[toMask].x>dp[Mask].x+1)
					{
						dp[toMask]=mp(dp[Mask].x+1,mp(i,Mask));
						if (!inq[toMask])
						{
							q.push(toMask);
							inq[toMask]=true;
						}
					}
				}
		}
	}
	printf("%d\n",dp[(1<<n)-1].x);
	print((1<<n)-1);printf("\n");
	return 0;
}
