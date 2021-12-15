#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

void exgcd(LL a,LL b,LL &x,LL &y)
{
	if (!b) {x=1;y=0;return;}
	else
	{
		exgcd(b,a%b,x,y);
		LL t=x;x=y;y=t-a/b*y;
	}
}

LL a,b;

int main ()
{
    scanf("%lld%lld",&a,&b);
    LL x,y;exgcd(a,b,x,y);
    x=(x%b+b)%b;printf("%lld\n",x);
    return 0;
}