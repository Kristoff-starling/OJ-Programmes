#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=100;

int n,m;
LL a[MAXN+48],b[MAXN+48];
int aa[MAXN+48],atot;
int bb[MAXN+48],btot;

LL ans[MAXN+48][MAXN+48];

int main ()
{
	n=getint();m=getint();int i,j,k;
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=m;i++) b[i]=getint();
	for (i=0;i<=31;i++)
	{
		atot=0;btot=0;
		for (j=1;j<=n;j++)
			if (a[j]&(1ll<<i)) aa[++atot]=j;
		for (j=1;j<=m;j++)
			if (b[j]&(1ll<<i)) bb[++btot]=j;
		if ((atot&1)!=(btot&1)) {puts("NO");return 0;}
		if (atot&1)
		{
			for (j=1;j<=atot;j++)
				for (k=1;k<=btot;k++)
					ans[aa[j]][bb[k]]|=(1ll<<i);
		}
		else
		{
			if (atot<=btot)
			{
				if (atot)
				{
				for (j=1;j<=atot-1;j++)
					ans[aa[j]][bb[j]]|=(1ll<<i);
				for (j=atot;j<=btot;j++)
					ans[aa[atot]][bb[j]]|=(1ll<<i);
				}
				else
				{
					for (j=1;j<=btot;j++)
						ans[1][bb[j]]|=(1ll<<i);
				}
			}
			else
			{
				if (btot)
				{
				for (j=1;j<=btot-1;j++)
					ans[aa[j]][bb[j]]|=(1ll<<i);
				for (j=btot;j<=atot;j++)
					ans[aa[j]][bb[btot]]|=(1ll<<i);
				}
				else
				{
					for (j=1;j<=atot;j++)
						ans[aa[j]][1]|=(1ll<<i);
				}
			}
		}
	}
	puts("YES");
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
			printf("%I64d ",ans[i][j]);
		puts("");
	}
	return 0;
}
