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
const int INF=1e9;
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
LL dp[3048],tmp[3048];
LL a[3048],sum[3048];
int q[3048],head,tail;

inline double calc(int ind1,int ind2)
{
	int pos1=q[ind1],pos2=q[ind2];
	return (dp[pos1]+sum[pos1]*sum[pos1]-dp[pos2]-sum[pos2]*sum[pos2])*1.0/(sum[pos1]-sum[pos2]);
}

int main ()
{
	int i,sta;
	n=getint();m=getint();
	for (i=1;i<=n;i++) a[i]=getint(),sum[i]=sum[i-1]+a[i];
	for (i=1;i<=n;i++) dp[i]=1e9;dp[0]=0;
	for (sta=1;sta<=m;sta++)
	{
		head=tail=1;q[head]=sta-1;
		for (i=0;i<=n;i++) tmp[i]=INF;
		for (i=sta;i<=n;i++)
		{
			while (head<tail && calc(head,head+1)<2*sum[i]) head++;
			tmp[i]=dp[q[head]]+(sum[i]-sum[q[head]])*(sum[i]-sum[q[head]]);
			q[++tail]=i;
			while (head+1<tail && calc(tail-2,tail-1)>calc(tail-1,tail)) q[tail-1]=q[tail],tail--;
		}
		for (i=0;i<=n;i++) dp[i]=tmp[i];
	}
	printf("%lld\n",dp[n]*m-sum[n]*sum[n]);
	return 0;
}
