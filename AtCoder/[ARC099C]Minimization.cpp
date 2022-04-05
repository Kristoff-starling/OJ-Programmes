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

const int MOD=1e9+9;
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

int n,k;
int a[100048];

int main ()
{
	int i,minpos;n=getint();k=getint();
	for (i=1;i<=n;i++)
	{
		a[i]=getint();
		if (a[i]==1) minpos=i;
	}
	int left=minpos-1,right=n-left-1,ti,ll;
	if (left%(k-1)==0) ti=left/(k-1); else ti=left/(k-1)+1;
	ll=left%(k-1);if (ll) right-=(k-ll-1);
	if (right>0)
		if (right%(k-1)==0) ti+=right/(k-1); else ti+=right/(k-1)+1;
	printf("%d\n",ti);
	return 0;
}
