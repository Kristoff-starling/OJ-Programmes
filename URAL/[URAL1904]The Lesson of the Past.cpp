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

int a[100048],tot=0;
int n,k[48];
vector<Pair> ans;

inline int myabs(int x) {return x>=0?x:-x;}

int main ()
{
	int i,j;n=getint();
	for (i=1;i<=n;i++) k[i]=getint();
	for (i=-30000;i<=30000;i++)
	{
		int cur=i;
		for (j=1;j<=n;j++) cur=myabs(cur-k[j]);
		if (cur<=1) a[++tot]=i;
	}
	int pt=1,pt1;
	while (pt<=tot)
	{
		pt1=pt;
		while (pt1<tot && a[pt1+1]==a[pt1]+1) pt1++;
		ans.pb(mp(a[pt],a[pt1]));
		pt=pt1+1;
	}
	printf("%d\n",int(ans.size()));
	for (i=0;i<int(ans.size());i++) printf("%d %d\n",ans[i].x,ans[i].y);
	return 0;
}
