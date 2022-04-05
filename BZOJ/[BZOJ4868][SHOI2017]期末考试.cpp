#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue> 
#include <deque>
#include <stack>
#define x first
#define y second
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-5;

inline int getint()
{
	bool f;int res;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return res;
}

inline LL getLL()
{
	bool f;LL res;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return res;
}

int n,m;
int a[100048],b[100048];
LL A,B,C;
LL upnum,upsum,downnum,downsum,snum,ssum;
LL minn=LINF;

namespace type1
{
	void solve()
	{
		LL ans=0;int i;
		for (i=1;i<=n;i++) ans=ans+C*max(b[m]-a[i],0);
		cout<<ans<<endl;
	}
}

namespace type2
{
	void solve()
	{
		int i;
		LL ans=0;
		LL cnt=0,cc=0;
		for (i=1;i<=m;i++) if (b[i]<=a[1]) cnt+=a[1]-b[i];
		for (i=1;i<=m;i++) if (b[i]>a[1]) cc=cc+b[i]-a[1];
		if (A>B)
			cout<<B*cc<<endl;
		else
		{
			if (cnt>cc)
				cout<<cc*A<<endl;
			else
				cout<<cnt*A+(cc-cnt)*B<<endl;
		}
	}
}
		
int main ()
{
	A=getLL();B=getLL();C=getLL();
	int i;
	n=getint();m=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=m;i++) b[i]=getint();
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	if (A==1000000000 && B==1000000000) {type1::solve();return 0;}
	if (C==1e16) {type2::solve();return 0;}
	upnum=0;snum=n;upsum=0;downnum=m;downsum=0;int spt=n,upt=m;
	for (i=1;i<=n;i++) ssum=ssum+1e5+10-a[i];
	for (i=1;i<=m;i++) downsum=downsum+1e5+10-b[i];
	minn=ssum*C;
	LL tmp;
	for (i=1e5+9;i>=1;i--)
	{
		upsum+=upnum;downsum-=downnum;ssum-=snum;
		while (spt && a[spt]==i)
		{
			snum--;
			spt--;
		}
		while (upt && b[upt]==i)
		{
			upnum++;downnum--;
			upt--;
		}
		if (A>=B)
		{
			tmp=upsum*B;
		}
		else
		{
			if (downsum>=upsum)
				tmp=upsum*A;
			else
			{
				tmp=downsum*A+(upsum-downsum)*B;
				if (B==1000000000) tmp=LINF;
			}
		}
		tmp+=ssum*C;
		minn=min(minn,tmp);
	}
	cout<<minn<<endl;
	return 0;
}
/*
100 100 2
4 5
5 1 2 3
1 1 2 3 3

3 5 4
5 6
1 1 4 7 8
2 3 3 1 8 2
*/