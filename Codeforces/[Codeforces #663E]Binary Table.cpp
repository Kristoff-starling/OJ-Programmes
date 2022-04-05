#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,len;
char s[22][100048];

LL a[2000048],b[2000048];

inline void FWT(LL c[],int fl)
{
	int clen,j,k;
	for (clen=2;clen<=len;clen<<=1)
		for (j=0;j<len;j+=clen)
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k],tmp2=c[k+(clen>>1)];
				if (fl==1)
					c[k]=tmp1+tmp2,c[k+(clen>>1)]=tmp1-tmp2;
				else
					c[k]=((tmp1+tmp2)>>1),c[k+(clen>>1)]=((tmp1-tmp2)>>1);
			}
}

inline void calc_FWT()
{
	len=(1<<n);
	FWT(a,1);FWT(b,1);
	for (register int i=0;i<=(1<<n)-1;i++) a[i]*=b[i];
	FWT(a,-1);
}

int main ()
{
	int i,j,Mask;
	n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",s[i]+1);
	for (j=1;j<=m;j++)
	{
		Mask=0;
		for (i=1;i<=n;i++) Mask|=((s[i][j]-'0')<<(i-1));
		a[Mask]++;
	}
	for (Mask=0;Mask<=(1<<n)-1;Mask++)
		b[Mask]=min(__builtin_popcount(Mask),n-__builtin_popcount(Mask));
	calc_FWT();
	LL ans=LINF;
	for (i=0;i<=(1<<n)-1;i++) ans=min(ans,a[i]);
	printf("%lld\n",ans);
	return 0;
}
