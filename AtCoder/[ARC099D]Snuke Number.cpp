#include <bits/stdc++.h>
#define LL long long
using namespace std;
 
int k;
 
inline int Get(LL x)
{
	int res=0;
	while (x) res+=x%10,x/=10;
	return res;
}
 
int main ()
{
	scanf("%d",&k);LL cur=1,nxt;LL delta=1;
	while (k--)
	{
		printf("%lld\n",cur);
		nxt=cur+delta;
		while (double(nxt)*1.0/Get(nxt)>delta)
		{
			delta*=10;
			nxt=cur+delta;
		}
		cur=nxt;
	}
	return 0;
}
