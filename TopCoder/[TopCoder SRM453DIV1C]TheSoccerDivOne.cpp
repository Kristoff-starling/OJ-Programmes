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

struct TheSoccerDivOne
{
	const int BASE=208;
	int n,cmp,a[58],lim[58];int dp[58][448][10],inq[58][448][10];
	queue<int> q;
	inline int myabs(int x)
	{
		return x>=0?x:-x;
	}
	inline void go(int people,int three,int one)
	{
		int tnum,onum,znum,tothree,toone,match;
		for (tnum=0;tnum<=4;tnum++)
			for (onum=0;onum+tnum<=4;onum++)
			{
				znum=4-tnum-onum;
				int add=(a[people]+tnum*3+onum>cmp?1:0);
				for (match=0;match<=one && match<=onum;match++)
				{
					if (one+onum-match*2>4) continue;
					tothree=three+tnum-znum;toone=one+onum-match*2;
					if (dp[people][tothree][toone]>dp[people-1][three][one]+add)
					{
						dp[people][tothree][toone]=dp[people-1][three][one]+add;
						if (!inq[people][tothree][toone]) 
						{
							q.push(people);q.push(tothree);q.push(toone);
							inq[people][tothree][toone]=true;
						}
					}
				}
			}
	}
	inline int work()
	{
		int i,j,k,people,three,one;
		for (i=0;i<=n;i++)
			for (j=BASE-210;j<=BASE+210;j++)
				for (k=0;k<=4;k++)
					dp[i][j][k]=INF;
		dp[0][BASE+4][0]=0;
		memset(inq,false,sizeof(inq));
		q.push(0);q.push(BASE+4);q.push(0);inq[0][BASE+4][0]=true;
		while (!q.empty())
		{
			people=q.front();q.pop();three=q.front();q.pop();one=q.front();q.pop();
			inq[people][three][one]=false;
			if (people<n-1) go(people+1,three,one);
		}
		return dp[n-1][BASE][0]+1;
	}
	inline int find(vector<int> v)
	{
		n=int(v.size());
		cmp=v[0]+3*4;
		for (int i=1;i<=n-1;i++) a[i]=v[i];
		return work();
	}
};


/*---Debug Part---*/
/*
int main ()
{
//	freopen ("soccer.in","r",stdin);
//	freopen ("1.out","w",stdout);
	TheSoccerDivOne A;
	int n,x;
	while (scanf("%d",&n)!=EOF)
	{
		vector<int> v;
		while (n--)
		{
			x=getint();
			v.pb(x);
		}
		printf("%d\n",A.find(v));
	}
	return 0;
}
*/
