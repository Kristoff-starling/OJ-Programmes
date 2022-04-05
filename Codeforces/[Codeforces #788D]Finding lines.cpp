#include <cassert>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <functional>
#define ll long long
#define lb long double
#define x first
#define y second
#define pair pair<int,int>
#define pll pair<ll,ll>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define lowbit(x) x & (-x)
using namespace std;

const int mod=998244353;
const int inf=2e9;
const ll linf=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline ll getll()
{
	bool f;char ch;ll res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

vector<int> x,y;
int t,d,cpos,tpos;
int st;

inline void check(int cpos)
{
	printf("0 %d %d\n",cpos,t);
	fflush(stdout);
	scanf("%d",&d);
	if (!d) x.pb(cpos);
	printf("0 %d %d\n",t,cpos);
	fflush(stdout);
	scanf("%d",&d);
	if (!d) y.pb(cpos);
}

int main ()
{
	t=-1e8;int i;
	printf("0 -100000000 -100000000\n");
	fflush(stdout);
	scanf("%d",&d);
	cpos=-1e8+d;t=-1e8;
	while (!d)
	{
		++t;
		printf("0 %d %d\n",t,t);
		fflush(stdout);
		scanf("%d",&d);
	}
	check(cpos);tpos=cpos;
	int cnt=0,dd,cc=0;
	do
	{
		dd=-1;
		if (tpos+(1<<11)<=1e8)
		{
			printf("0 %d %d\n",tpos+(1<<11),tpos+(1<<11));
			fflush(stdout);
			scanf("%d",&d);
			if (d==tpos+(1<<11)-cpos) {tpos+=(1<<11);cc++;continue;} else dd=d;
		}
		if (cc && dd!=-1)
		{
			cc=0;d=dd;
			cpos=tpos+d;
			check(cpos);tpos=cpos;
			continue;
		}
		for (i=0;i<=10;i++)
			if (tpos+(1<<i)<=1e8)
			{
				printf("0 %d %d\n",tpos+(1<<i),tpos+(1<<i));
				fflush(stdout);
				scanf("%d",&d);
				if (d!=tpos+(1<<i)-cpos) break;
			}
		if (i==11 && tpos+(1<<11)>1e8) break;
		if (i==11) d=dd;
		cpos=tpos+(1<<i)+d;
		check(cpos);tpos=cpos;
		++cnt;
	}
	while (true);
	int n=int(x.size()),m=int(y.size());
	printf("1 %d %d\n",n,m);
	for (i=0;i<int(x.size());i++) printf("%d ",x[i]);
	printf("\n");
	for (i=0;i<int(y.size());i++) printf("%d ",y[i]);
	printf("\n");
	return 0;
}
