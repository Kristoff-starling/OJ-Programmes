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

int n;
int a[1048];
LL dp[1048];Pair del[1048];
int cnt;
vector<int> ans;

inline void getans(int cur)
{
	if (del[cur].x==1)
	{
		for (int i=1;i<=cur-1;i++) ans.pb(1);
		cnt=cur-1;
		return;
	}
	getans(del[cur].x-1);
	int len=del[cur].y-del[cur].x+1;
	for (int i=len/2+1;i>=1;i--)
		ans.pb(del[cur].x-cnt+i-1);
	cnt+=len+1;
}

int main ()
{
	int i,j;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++)
	{
		dp[i]=a[i];del[i]=mp(1,i-1);
		for (j=2;i-j>=1;j+=2)
			if (dp[i-j]+a[i]>dp[i])
			{
				dp[i]=dp[i-j]+a[i];
				del[i]=mp(i-j+1,i-1);
			}
	}
	LL maxn=-INF;int pos;
	for (i=1;i<=n;i++)
		if (dp[i]>maxn) maxn=dp[i],pos=i;
	printf("%lld\n",maxn);
	getans(pos);
	for (i=n;i>=pos+1;i--) ans.pb(n-cnt),cnt++;
	printf("%d\n",int(ans.size()));
	for (i=0;i<int(ans.size());i++) printf("%d\n",ans[i]);
	return 0;
}
