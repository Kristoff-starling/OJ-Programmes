#include <bits/stdc++.h>
using namespace std;

const int MOD=1e9+7;

int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

int main ()
{
	int a,b,c;
	cin>>a>>b>>c;
	int p=quick_pow(c,MOD-2);
	int q=1ll*((1-p+MOD)%MOD)*quick_pow(p,MOD-2)%MOD;
	if (q==1)
	{
		int A=a,B=a+b;
		cout<<1ll*A*quick_pow(B,MOD-2)%MOD<<endl;
		return 0;
	}
	int A=(1-quick_pow(q,a)+MOD)%MOD;
	int B=(1-quick_pow(q,a+b)+MOD)%MOD;
	cout<<1ll*A*quick_pow(B,MOD-2)%MOD<<endl;
	return 0;
}