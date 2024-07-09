#pragma GCc optimize ("Ofast")
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
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;char s[100048];
unsigned int dp[100048];

int main ()
{
	int i,j;n=getint();scanf("%s",s+1);
	int nq=0;
	for (i=1;i<=n;i++) nq+=(s[i]=='?');
	if ((n&1) || (nq*2<n)) {printf("0\n");return 0;}
	int dlim,ulim;dp[0]=1;
	for (i=1;i<=n;i++)
	{
		for (j=(i+1)/2;j>=1;j--) if (s[i]=='?') dp[j]+=dp[j-1];
		for (j=0;j<=n;j++) cout<<dp[j]<<' ';
		cout<<endl;
	}
	unsigned int ans=dp[n/2];
	for (i=1;i<=nq-n/2;i++) ans*=25;
	cout<<ans<<endl;
	return 0;
}
