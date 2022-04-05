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

const int MOD=1e9;
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
char s[48][48];
int deg[148][148],ga[148][148];
int Ind[48][48],itot=0;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
LL a[148][148];

inline void doit(int i,int j)
{
	int ind=Ind[i][j];deg[ind][ind]=0;int xx,yy,dir;
	for (dir=0;dir<=3;dir++)
	{
		xx=i+dx[dir];yy=j+dy[dir];
		if (1<=xx && xx<=n && 1<=yy && yy<=m && Ind[xx][yy]) deg[ind][ind]++,ga[ind][Ind[xx][yy]]=1;
	}
}

inline LL mod(LL x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

inline LL calc_det()
{
	int i,j,k,x,y,fl=1;LL ans=1;
	for (i=1;i<=itot-1;i++)
	{
		for (j=i+1;j<=itot-1;j++)
		{
			x=i;y=j;
			while (a[y][i])
			{
				LL t=a[x][i]/a[y][i];
				for (k=i;k<=itot-1;k++)
					a[x][k]=mod(a[x][k]-(a[y][k]*t)%MOD);
				swap(x,y);
			}
			if (x!=i)
			{
				for (k=i;k<=itot-1;k++) swap(a[x][k],a[y][k]);
				fl=-fl;
			}
		}
		if (a[i][i]==0) return 0;
		ans=(ans*a[i][i])%MOD;
	}
	if (fl==-1) ans=-ans;
	ans=mod(ans);
	return ans;
}

int main ()
{
	int i,j;n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",s[i]+1);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (s[i][j]=='.') Ind[i][j]=++itot;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			doit(i,j);
	for (i=1;i<=itot;i++)
		for (j=1;j<=itot;j++)
			a[i][j]=deg[i][j]-ga[i][j];
	printf("%lld\n",calc_det());
	return 0;
}
