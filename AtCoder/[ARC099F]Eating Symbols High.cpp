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
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
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

int n;
char s[300048];

inline LL mod(LL x,int MO) {while (x>=MO) x-=MO;while (x<0) x+=MO;return x;}
inline LL quick_pow(LL x,LL y,int MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=(res*x)%MO,y--;
		x=(x*x)%MO;y>>=1;
	}
	return res;
}
const int p1=19260817,p2=998244353,m1=1e9+7,m2=1e9+9;
LL inv1,inv2;
LL f1[300048],f2[300048];LL K,B;
map<pLL,int> Mp;

int main ()
{
	int i;n=getint();scanf("%s",s+1);
	inv1=quick_pow(p1,m1-2,m1);inv2=quick_pow(p2,m2-2,m2);
	K=1;B=0;
	for (i=1;i<=n;i++)
	{
		if (s[i]=='+') B=mod(B+K,m1);
		if (s[i]=='-') B=mod(B-K,m1);
		if (s[i]=='<') K=(K*inv1)%m1;
		if (s[i]=='>') K=(K*p1)%m1;
		f1[i]=B;
	}
	K=1;B=0;
	for (i=1;i<=n;i++)
	{
		if (s[i]=='+') B=mod(B+K,m2);
		if (s[i]=='-') B=mod(B-K,m2);
		if (s[i]=='<') K=(K*inv2)%m2;
		if (s[i]=='>') K=(K*p2)%m2;
		f2[i]=B;
	}
	Mp.clear();for (i=1;i<=n;i++) Mp[mp(f1[i],f2[i])]++;
	LL c1=0,c2=0;
	for (i=n;i>=1;i--)
	{
		if (s[i]=='+') c1=mod(c1+1,m1),c2=mod(c2+1,m2);
		if (s[i]=='-') c1=mod(c1-1,m1),c2=mod(c2-1,m2);
		if (s[i]=='<') c1=(c1*inv1)%m1,c2=(c2*inv2)%m2;
		if (s[i]=='>') c1=(c1*p1)%m1,c2=(c2*p2)%m2;
	}
	LL k1=1,b1=0,k2=1,b2=0,need1,need2,ans=0;
	for (i=1;i<=n;i++)
	{
		need1=(mod(c1-b1,m1)*quick_pow(k1,m1-2,m1))%m1;
		need2=(mod(c2-b2,m2)*quick_pow(k2,m2-2,m2))%m2;
		ans+=Mp[mp(need1,need2)];
		Mp[mp(f1[i],f2[i])]--;
		if (s[i]=='+') b1=mod(b1-1,m1),b2=mod(b2-1,m2);
		if (s[i]=='-') b1=mod(b1+1,m1),b2=mod(b2+1,m2);
		if (s[i]=='<') k1=(k1*p1)%m1,b1=(b1*p1)%m1,k2=(k2*p2)%m2,b2=(b2*p2)%m2;
		if (s[i]=='>') k1=(k1*inv1)%m1,b1=(b1*inv1)%m1,k2=(k2*inv2)%m2,b2=(b2*inv2)%m2;
	}
	printf("%lld\n",ans);
	return 0;
}
