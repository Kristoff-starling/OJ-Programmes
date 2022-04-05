#include <cstdio>
#include <algorithm>

const int MAXN=10000;

int n,a[MAXN+48],tot;

int main ()
{
	int i,x,ca,res;scanf("%d",&ca);
	while (ca--)
	{
		scanf("%d",&n);tot=0;
		if (n&1) a[++tot]=0;
		for (i=1;i<=n;i++) scanf("%d",&x),a[++tot]=x;
		std::sort(a+1,a+tot+1);res=0;
		for (i=1;i<=tot-1;i+=2) res^=(a[i+1]-a[i]-1);
		if (!res) puts("Bob will win"); else puts("Georgia will win");
	}
	return 0;
}
