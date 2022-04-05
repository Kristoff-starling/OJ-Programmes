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
 
const int MOD=20110520;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const int hashmod=4841;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
char a[148][148],tmp[148][148];

struct Hash
{
	vector<Pair> hsh[5048];
	inline void init()
	{
		for (register int i=0;i<=hashmod-1;i++)
			hsh[i].clear();
	}
	inline void Insert(int Mask,int newval)
	{
		int h=Mask%hashmod;newval%=MOD;
		for (register int i=0;i<int(hsh[h].size());i++)
			if (hsh[h][i].x==Mask) {hsh[h][i].y+=newval%=MOD;return;}
		hsh[h].pb(mp(Mask,newval));
	}
}dp[2];

//plug=0: no plug
//plug=1: a plug before turning
//plug=2: a plug after turning
inline int getplug(int Mask,int pos) {return (Mask>>((pos-1)<<1))&3;}
inline int Set(int Mask,int pos,int newplug) {Mask|=(3<<((pos-1)<<1));Mask^=((3-newplug)<<((pos-1)<<1));return Mask;}

int main ()
{
	int i,j,x,y,Mask,curval,toMask,toval,plug1,plug2;n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",a[i]+1);
	if (n<m)
	{
		swap(n,m);
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				tmp[i][j]=a[m-j+1][i];
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				a[i][j]=tmp[i][j];
	}
	dp[0].init();dp[1].init();
	dp[0].Insert(0,1);int cur=1,pre=0;
	for (x=1;x<=n;x++)
	{
		for (y=1;y<=m;y++)
		{
			dp[cur].init();
			for (i=0;i<=hashmod-1;i++)
				for (j=0;j<int(dp[pre].hsh[i].size());j++)
				{
					Mask=dp[pre].hsh[i][j].x;curval=dp[pre].hsh[i][j].y;
					plug1=getplug(Mask,y);plug2=getplug(Mask,y+1);
					if (a[x][y]=='*')
					{
						if (!plug1 && !plug2) dp[cur].Insert(Mask,curval);
					}
					else
					{
						if (!plug1 && !plug2)
						{
							if (x!=n && a[x+1][y]=='_' && y!=m && a[x][y+1]=='_') toMask=Set(Set(Mask,y,2),y+1,2),dp[cur].Insert(toMask,curval);
							if (x!=n && a[x+1][y]=='_') toMask=Set(Mask,y,1),dp[cur].Insert(toMask,curval);
							if (y!=m && a[x][y+1]=='_') toMask=Set(Mask,y+1,1),dp[cur].Insert(toMask,curval);
						}
						if (plug1==1 && !plug2)
						{
							if (y!=m && a[x][y+1]=='_') toMask=Set(Set(Mask,y,0),y+1,1),dp[cur].Insert(toMask,curval);
							if (x!=n && a[x+1][y]=='_') toMask=Set(Mask,y,2),dp[cur].Insert(toMask,curval);
						}
						if (plug1==2 && !plug2)
						{
							if (y!=m && a[x][y+1]=='_') toMask=Set(Set(Mask,y,0),y+1,2),dp[cur].Insert(toMask,curval);
							toMask=Set(Mask,y,0);dp[cur].Insert(toMask,curval);
						}
						if (!plug1 && plug2==1)
						{
							if (x!=n && a[x+1][y]=='_') toMask=Set(Set(Mask,y,1),y+1,0),dp[cur].Insert(toMask,curval);
							if (y!=m && a[x][y+1]=='_') toMask=Set(Mask,y+1,2),dp[cur].Insert(toMask,curval);
						}
						if (plug1==1 && plug2==1)
						{
							toMask=Set(Set(Mask,y,0),y+1,0);dp[cur].Insert(toMask,curval);
						}
						if (!plug1 && plug2==2)
						{
							if (x!=n && a[x+1][y]=='_') toMask=Set(Set(Mask,y,2),y+1,0),dp[cur].Insert(toMask,curval);
							toMask=Set(Mask,y+1,0);dp[cur].Insert(toMask,curval);
						}
					}
				}
			swap(cur,pre);
		}
		if (i==n) continue;
		dp[cur].init();
		for (i=0;i<hashmod;i++)
			for (j=0;j<int(dp[pre].hsh[i].size());j++)
			{
				Mask=dp[pre].hsh[i][j].x;curval=dp[pre].hsh[i][j].y;
				dp[cur].Insert(Mask<<2,curval);
			}
		swap(cur,pre);
	}
	for (i=0;i<int(dp[pre].hsh[0].size());i++)
		if (dp[pre].hsh[0][i].x==0) {printf("%d\n",dp[pre].hsh[0][i].y);return 0;}
	printf("0\n");return 0;
}
