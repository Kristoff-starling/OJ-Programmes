#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL k,p;
LL ans;

inline int getlen(int x)
{
	int res=0;
	while (x)
	{
		res++;
		x/=10;
	}
	return res;
}

inline LL mypow(int x)
{
	LL res=1;
	for (int i=1;i<=x;i++) res*=10;
	return res;
}

inline LL Re(LL x)
{
	LL res=0;
	while (x)
	{
		res=res*10+x%10;
		x/=10;
	}
	return res;
}

int main ()
{
	cin>>k>>p;
	for (LL i=1;i<=k;i++)
	{
		int len=getlen(i);
		LL j=Re(i);
		ans=(ans+j)%p;
		ans=(ans+(i*mypow(len))%p)%p;
	}
	cout<<ans<<endl;
}
