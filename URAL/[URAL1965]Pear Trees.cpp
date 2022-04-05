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
int a[100048];
vector<int> anslist1,anslist2;
int dp1[100048],dp2[100048];int pre1[100048],pre2[100048];

inline bool checkup()
{
	anslist1.clear();anslist2.clear();int i;
	anslist1.pb(-INF);anslist2.pb(-INF);
	for (i=1;i<=n;i++)
	{
		int val1=anslist1.back(),val2=anslist2.back();
		if (a[i]>max(val1,val2))
		{
			if (val1>val2) anslist1.pb(a[i]); else anslist2.pb(a[i]);
			continue;
		}
		if (a[i]>val1) {anslist1.pb(a[i]);continue;}
		if (a[i]>val2) {anslist2.pb(a[i]);continue;}
		return false;
	}
	return true;
}

inline bool checkdown()
{
	anslist1.clear();anslist2.clear();int i;
	anslist1.pb(INF);anslist2.pb(INF);
	for (i=1;i<=n;i++)
	{
		int val1=anslist1.back(),val2=anslist2.back();
		if (a[i]<min(val1,val2))
		{
			if (val1>val2) anslist2.pb(a[i]); else anslist2.pb(a[i]);
			continue;
		}
		if (a[i]<val1) {anslist1.pb(a[i]);continue;}
		if (a[i]<val2) {anslist2.pb(a[i]);continue;}
		return false;
	}
	return true;
}

inline void getans(int i,int type)
{
	if (i==0) return;
	if (type==1)
	{
		getans(i-1,pre1[i]);
		anslist1.pb(a[i]);
	}
	else
	{
		getans(i-1,pre2[i]);
		anslist2.pb(a[i]);
	}
}

int main ()
{
	int i;n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	if (checkup() || checkdown())
	{
		if (int(anslist1.size())==1) anslist1.pb(anslist2.back()),anslist2.pop_back();
		if (int(anslist2.size())==1) anslist2.pb(anslist1.back()),anslist1.pop_back();
		printf("%d %d\n",int(anslist1.size())-1,int(anslist2.size())-1);
		for (i=1;i<int(anslist1.size());i++) printf("%d ",anslist1[i]);puts("");
		for (i=1;i<int(anslist2.size());i++) printf("%d ",anslist2[i]);puts("");
		return 0;
	}
	for (i=2;i<=n;i++) dp1[i]=-INF,dp2[i]=INF;
	dp1[1]=INF;dp2[1]=-INF;
	for (i=2;i<=n;i++)
	{
		if (a[i]>a[i-1] && dp1[i-1]>dp1[i])
		{
			dp1[i]=dp1[i-1];
			pre1[i]=1;
		}
		if (dp2[i-1]<a[i] && a[i-1]>dp1[i])
		{
			dp1[i]=a[i-1];
			pre1[i]=2;
		}
		if (a[i]<a[i-1] && dp2[i-1]<dp2[i])
		{
			dp2[i]=dp2[i-1];
			pre2[i]=2;
		}
		if (dp1[i-1]>a[i] && a[i-1]<dp2[i])
		{
			dp2[i]=a[i-1];
			pre2[i]=1;
		}
	}
	if (dp1[n]==-INF && dp2[n]==INF) {puts("Fail");return 0;}
	anslist1.clear();anslist2.clear();
	if (dp1[n]>-INF) getans(n,1); else getans(n,2);
	printf("%d %d\n",int(anslist1.size()),int(anslist2.size()));
	for (i=0;i<int(anslist1.size());i++) printf("%d ",anslist1[i]);puts("");
	for (i=0;i<int(anslist2.size());i++) printf("%d ",anslist2[i]);puts("");
	return 0;
}
