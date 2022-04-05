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
int a[48];

bool check(int sy,int sm)
{
	int yy=sy,mm=sm;
	int i,need;
	for (i=1;i<=n;i++)
	{
		if (mm==1 || mm==3 ||  mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
		{
			need=31;
		}
		else
		{
			if (mm==4 || mm==6 || mm==9 || mm==11)
			{
				need=30;
			}
			else
			{
				if (yy==0) need=29; else need=28;
			}
		}
		if (a[i]!=need) return false;
		mm++;
		if (mm>12)
		{
			mm-=12;
			yy++;
		}
		yy%=4;
	}
	return true;
}

int main ()
{
	n=getint();
	int i,j;
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=0;i<=3;i++)
		for (j=1;j<=12;j++)
			if (check(i,j))
			{
				printf("YES\n");
				return 0;
			}
	printf("NO\n");
	return 0;
}
