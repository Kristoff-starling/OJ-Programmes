#include <cstdio>

int main ()
{
	int n;
	while (scanf("%d",&n) && n) puts((n==1 || n==2)?"Alice":"Bob");
	return 0;
}
