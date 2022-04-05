#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cctype>
#define LL long long
#define LB long double
#define mp make_pair
#define pb push_back
#define pf push_front 
#define Pair pair<int,int>
#define x first
#define y second
#define LOWBIT(X) x & (-x)
using namespace std;

const int MOD=1e6;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;bool f;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
int len;
int max_len;
int p[20];

inline int getlen(int x)
{
	int res=0;
	while (x!=0)
	{
		res++;
		x/=10;
	}
	return res;
}

int a[15];
void split(int x)
{
	int tot=0;
	while (x!=0)
	{
		a[++tot]=x%10;
		x/=10;
	}
	reverse(a+1,a+tot+1);
}

int zero_Way[20],Way[20];
int ans=0;

int dfs(int cur,bool lim)
{
	if (cur>len) return 1;
	if (!lim)
	{
		return 10*dfs(cur+1,false);
	}
	else
		return a[cur]*dfs(cur+1,false)+dfs(cur+1,true);
}

inline int mypow(int x)
{
	int res=1;
	while (x--) res*=10;
	return res;
}

int main ()
{
	int i;
	n=getint();
	if (n<5)
	{
		cout<<n*(n-1)/2<<endl;
		return 0;
	}
	len=getlen(n);
	split(n);
	p[1]=5;
	for (i=2;i<=9;i++) p[i]=p[i-1]*10;
	if (len==10) max_len=9; else max_len=(n>=p[len])?len:len-1;
	Way[1]=8;zero_Way[1]=10;
	for (i=2;i<=9;i++)
	{
		Way[i]=zero_Way[i-1]*8;
		zero_Way[i]=zero_Way[i-1]*10;
	}
	if (len==max_len)
	{
		for (i=5;i<=a[1]-1;i++) ans+=dfs(2,false);
		ans+=dfs(2,true);
		if (n==mypow(len)-1) ans--;
	}
	else
	{
		/*for (i=5;i<=9;i++) ans+=dfs(3,false);
		for (i=1;i<=a[1]-1;i++)
			ans+=i*dfs(2,false);
		ans+=a[1]*dfs(2,true);
		for (i=1;i<=a[1]-1;i++)
			for (int j=5;j<=9;j++) ans+=dfs(3,false);
		for (i=5;i<=a[2]-1;i++) ans+=dfs(3,false);
		if (a[2]>=5) ans+=dfs(3,true);*/
		for (i=0;i<=a[1]-1;i++)
		{
			ans+=i*dfs(2,false);
			for (int j=5;j<=9;j++) ans+=dfs(3,false);
		}
		for (i=0;i<=a[1]-1;i++) ans+=dfs(2,true);
		for (i=5;i<=a[2]-1;i++) ans+=dfs(3,false);
		if (a[2]>=5) ans+=dfs(3,true);
		LL pp=mypow(max_len)-1;LL nn=n;
		while (nn>=pp)
		{
			ans--;
			pp+=mypow(max_len);
		}
	}
	cout<<ans<<endl;
	return 0;
}
