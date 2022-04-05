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

int n,r;
int a[1048];
double ans[1048];

inline double myabs(double x)
{
	return x>=eps?x:-x;
}

double calc(int ind1,int ind2)
{
	int x1=a[ind1],x2=a[ind2];
	if (myabs(x1-x2)-r*2>eps) return double(-1);
	double dd=r*2*r*2-(myabs(x1-x2)*myabs(x1-x2));
	dd=sqrt(dd);
	return ans[ind1]+dd;
}

int main ()
{
	n=getint();r=getint();
	int i,j;
	for (i=1;i<=n;i++) a[i]=getint();
	ans[1]=r;
	for (i=2;i<=n;i++)
	{
		ans[i]=r;
		for (j=1;j<=i-1;j++)
			ans[i]=max(ans[i],calc(j,i));
	}
	for (i=1;i<=n;i++) printf("%.8lf ",ans[i]);
	return 0;
}
