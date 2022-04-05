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
 
const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
LL a,b,c;
LL aa[1000048],sum[1000048];
LL dp[1000048];

struct node
{
	LL x,y;
	int ind;
};
inline double calc(int x,int y)
{
	return double(dp[x]+a*sum[x]*sum[x]+b*sum[y]-(dp[y]+a*sum[y]*sum[y]+b*sum[x]))/(sum[x]-sum[y]);
}

int head,tail;int q[1000048];

int main ()
{
	int i;
	n=getint();
	a=getint();b=getint();c=getint();
	for (i=1;i<=n;i++) aa[i]=getint(),sum[i]=sum[i-1]+aa[i];
	head=tail=1;q[head]=0;
	for (i=1;i<=n;i++)
	{
		while (head<tail && calc(q[head],q[head+1])>(long long)2*a*sum[i]) head++;
		int pos=q[head];
		dp[i]=dp[pos]+a*(sum[i]-sum[pos])*(sum[i]-sum[pos])+b*(sum[i]-sum[pos])+c;
		q[++tail]=i;
		while (head+1<tail && calc(q[tail-2],q[tail-1])<calc(q[tail-1],q[tail])) q[tail-1]=q[tail],tail--;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
