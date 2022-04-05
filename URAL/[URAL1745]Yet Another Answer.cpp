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

const int MOD=123456789;
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
char s[10048];

struct node
{
	int len,maxd,lastd,ind;
}a[1048],A[1048],B[1048];int atot,btot;

inline bool cmpa(node x,node y) {return x.maxd>y.maxd;}
inline bool cmpb(node x,node y)
{
	int val1=max(-x.maxd,-x.lastd-y.maxd);
	int val2=max(-y.maxd,-y.lastd-x.maxd);
	return val1<val2;
}

int ans,anslen;
vector<int> anslist;

int dp[1048][5048];pair<int,bool> pre[1048][5048];

inline void getans(int i,int j)
{
	if (i==0) return;
	getans(i-1,pre[i][j].x);
	if (pre[i][j].y) anslist.pb(a[i].ind);
}

int main ()
{
	int i,j;n=getint();int sum=0;
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);a[i].len=strlen(s+1);a[i].ind=i;sum+=a[i].len;
		a[i].maxd=0;
		for (j=1;j<=a[i].len;j++)
		{
			if (s[j]=='(') a[i].lastd++;
			if (s[j]==')') a[i].lastd--;
			a[i].maxd=min(a[i].maxd,a[i].lastd);
		}
		if (a[i].lastd>=0) A[++atot]=a[i]; else B[++btot]=a[i];
	}
	sort(A+1,A+atot+1,cmpa);sort(B+1,B+btot+1,cmpb);
	for (i=1;i<=atot;i++) a[i]=A[i];for (i=1;i<=btot;i++) a[atot+i]=B[i];
	for (i=0;i<=n;i++)
		for (j=0;j<=min(sum,5000);j++)
			dp[i][j]=-1;
	dp[0][0]=0;
	for (i=0;i<=n-1;i++)
		for (j=0;j<=min(sum,5000);j++)
		{
			if (dp[i][j]<0) continue;
			if (dp[i][j]>dp[i+1][j])
			{
				dp[i+1][j]=dp[i][j];
				pre[i+1][j]=mp(j,false);
			}
			if (j+a[i+1].maxd>=0 && j+a[i+1].lastd<=5000 && dp[i+1][j+a[i+1].lastd]<dp[i][j]+a[i+1].len)
			{
				dp[i+1][j+a[i+1].lastd]=dp[i][j]+a[i+1].len;
				pre[i+1][j+a[i+1].lastd]=mp(j,true);
			}
		}
	getans(n,0);
	if (dp[n][0]==-1) {puts("0 0");return 0;}
	printf("%d %d\n",dp[n][0],int(anslist.size()));
	for (i=0;i<int(anslist.size());i++) printf("%d ",anslist[i]);
	puts("");return 0;
}
