#include <bits/stdc++.h>
using namespace std;

int main ()
{
	int a,b,c,d,p,x;
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&p,&x);
	int m=1100000000/p+1;
	printf("%d %d\n",m*p+x,m*p+x-1);
	return 0;
}
