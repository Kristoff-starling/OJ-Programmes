#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e6;

int a[MAXN+48],b[MAXN+48],c[MAXN+48],tot;

int main ()
{
	int n;scanf("%d",&n);
	puts("Yes");
	for (register int i=1;i<=n;i++)
		for (register int j=i+1;j<=n;j++)
		{
			int k=(n*2-i-j-1)%n+1;
			if (k>j) ++tot,a[tot]=i,b[tot]=j,c[tot]=k;
		}
	printf("%d\n",tot);
	for (register int i=1;i<=tot;i++) printf("%d %d %d\n",a[i],b[i],c[i]);
	puts("");return 0;
}
