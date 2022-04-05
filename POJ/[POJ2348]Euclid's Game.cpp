#include <cstdio>
#include <iostream>

const int MAXN=1e5;
long long a[MAXN+48];int tot=0;

long long n,m;

inline bool check(long long N,long long M)
{
	if (N/M>=2) return 1;
	if (N%M==0) return 1;
	return check(M,N%M)^1;
}

int main ()
{
	while (scanf("%lld%lld",&n,&m) && !(!n && !m))
	{
		if (!n || !m) {puts("Stan wins");continue;}
		if (n<m) std::swap(n,m);
		if (check(n,m)) puts("Stan wins"); else puts("Ollie wins");
	}
}
