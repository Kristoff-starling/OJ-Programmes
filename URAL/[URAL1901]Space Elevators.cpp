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

const LL MOD=1e9+7;
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

int n,s;
int a[100048];
int ans[100048],tot;
int small[100048],large[100048],stot,ltot;
bool vs[100048],vl[100048];
int tmp[100048],ttot;

int main ()
{
	int i;n=getint();s=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	sort(a+1,a+n+1);
	for (i=1;i<=n;i++)
		if (a[i]<=s/2) small[++stot]=a[i]; else large[++ltot]=a[i];
	int pt1=1;bool type=true;
	for (i=ltot;i>=1;i--)
	{
		while (pt1<=stot && large[i]+small[pt1]<=s) pt1++;
		if (pt1>stot) break;
		ans[++tot]=small[pt1];ans[++tot]=large[i];
		vs[pt1]=true;vl[i]=true;
		pt1++;
	}
	for (i=ltot;i>=1;i--)
		if (!vl[i]) ans[++tot]=large[i];
	for (i=stot;i>=1;i--)
		if (!vs[i]) ans[++tot]=small[i];
	int Ans=0;
	for (i=1;i<=n;)
	{
		if (i==n) {Ans++;i++;continue;}
		if (ans[i]+ans[i+1]>s) {Ans++;i++;continue;}
		Ans++;i+=2;
	}
	printf("%d\n",Ans);
	for (i=1;i<=n;i++) printf("%d ",ans[i]);
	puts("");return 0;
}
