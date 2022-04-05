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
#define Pair pair<LL,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
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

int n;LL L;
int c[100048];
LL sum[100048],s[100048],dp[100048];

struct node
{
	LL x,y;
	int ind;
}q[100048];int head,tail;

inline double calc_k(node x,node y)
{
	return double(y.y-x.y)/(y.x-x.x);
}

int main ()
{
	int i,curk;
	n=getint();L=getint()+1;sum[0]=0ll;
	for (i=1;i<=n;i++) c[i]=getint(),sum[i]=sum[i-1]+c[i],s[i]=sum[i]+i;
	q[1]=node{L,L*L,0};head=tail=1;memset(dp,0,sizeof(dp));
	for (i=1;i<=n;i++)
	{
		curk=2*s[i];
		while (head<tail && calc_k(q[head],q[head+1])<curk) head++;
		dp[i]=dp[q[head].ind]+(s[i]-s[q[head].ind]-L)*(s[i]-s[q[head].ind]-L);
		node ins=node{s[i]+L,dp[i]+(s[i]+L)*(s[i]+L),i};
		while (head<tail && calc_k(q[tail-1],q[tail])>calc_k(q[tail],ins)) tail--;
		q[++tail]=ins;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
