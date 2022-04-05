#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <list>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,k;
int to[2][MAXN+48];bool used[2][MAXN+48];
int path[MAXN*2+48],tot=0;

inline void dfs(int cur)
{
	if (!used[0][cur])
	{
		used[0][cur]=true;
		dfs(to[0][cur]);
		path[++tot]=0;
	}
	if (!used[1][cur])
	{
		used[1][cur]=true;
		dfs(to[1][cur]);
		path[++tot]=1;
	}
}

int main ()
{
	int i,Mask,toMask;
	while (scanf("%d%d",&n,&k) && !(!n && !k))
	{
		for (Mask=0;Mask<=(1<<(n-1))-1;Mask++)
			for (i=0;i<=1;i++)
			{
				toMask=(Mask<<1);toMask|=i;toMask&=((1<<(n-1))-1);
				to[i][Mask]=toMask;used[i][Mask]=false;
			}
		for (i=0;i<=n-2;i++) path[i]=0;tot=n-2;
		dfs(0);
		reverse(path+n-1,path+tot+1);
		memcpy(path+tot+1,path,(tot+1)*sizeof(int));
		int ans=0;
		for (i=k;i<=k+n-1;i++) ans<<=1,ans|=path[i];
		printf("%d\n",ans);
	}
	return 0;
}
