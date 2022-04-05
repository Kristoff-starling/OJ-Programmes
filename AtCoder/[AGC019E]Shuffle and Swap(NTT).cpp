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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;
const int G=3;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int inv[200048];
LL finv[200048],fac[200048];
int n;
char s1[100048],s2[100048];
int e,m;

inline void init_inv()
{
	int i;
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (i=2;i<=100000;i++)
	{
		fac[i]=(fac[i-1]*i)%MOD;
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
} 

inline LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

int len;
LL wn_pos[100048],wn_neg[100048];
inline void init_wn()
{
	for (register int clen=2;clen<=len;clen<<=1)
	{
		wn_pos[clen]=quick_pow(G,(MOD-1)/clen);
		wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
}

LL a[100048],b[100048];

inline void NTT(LL c[],int fl)
{
	int i,j,k,clen;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;
		i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		LL wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
		for (j=0;j<len;j+=clen)
		{
			LL w=1;
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k],tmp2=(c[k+(clen>>1)]*w)%MOD;
				c[k]=(tmp1+tmp2)%MOD;c[k+(clen>>1)]=((tmp1-tmp2)%MOD+MOD)%MOD;
				w=(w*wn)%MOD;
			}
		}
	}
	if (fl==-1)
		for (i=0;i<len;i++) c[i]=(c[i]*inv[len])%MOD;
}

inline void calc_NTT()
{
	NTT(a,1);NTT(b,1);
	for (register int i=0;i<len;i++) a[i]=(a[i]*b[i])%MOD;
	NTT(a,-1);
}

struct poly
{
	LL A[100048];
	inline poly operator * (const poly B) const
	{
		int i;poly res;
		memset(a,0,sizeof(a));memset(b,0,sizeof(b));
		for (i=0;i<=m;i++) a[i]=A[i],b[i]=B.A[i];
		calc_NTT();
		for (i=0;i<=m;i++) res.A[i]=a[i];
		return res;
	}
};

inline poly Quick_pow(poly x,LL y)
{
	int i;poly res;
	for (i=0;i<=m;i++) x.A[i]%=MOD;
	res.A[0]=1;
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

int main ()
{
	int i,j,k;
	scanf("%s%s",s1+1,s2+1);n=strlen(s1+1);
	init_inv();
	e=m=0;
	for (i=1;i<=n;i++)
	{
		if (s1[i]=='1' && s2[i]=='0') e++;
		if (s1[i]=='1' && s2[i]=='1') m++;
	}
	len=1;while (len<=m*2) len<<=1;
	init_wn();
	poly ans;for (i=0;i<=m;i++) ans.A[i]=finv[i+1];
	ans=Quick_pow(ans,e);
	LL fans=0;
	for (i=0;i<=m;i++) fans=(fans+ans.A[i])%MOD;
	fans=fans*fac[e]%MOD*fac[m]%MOD*fac[e+m]%MOD;
	printf("%lld\n",fans);
	return 0;
}
