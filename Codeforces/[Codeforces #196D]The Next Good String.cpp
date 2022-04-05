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

const int MAXN=4e5;

int d;
char s[MAXN+48];int len;
char ans[MAXN+48];

inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}

const int p1=19260817,p2=998244353,MOD1=1e9+7,MOD2=1e9+9;
int pw1[MAXN+48],pw2[MAXN+48];
int h1l[MAXN+48],h1r[MAXN+48],h2l[MAXN+48],h2r[MAXN+48];

inline int gethash1l(int l,int r)
{
	return sub(h1l[r]-(1ll*h1l[l-1]*pw1[r-l+1])%MOD1,MOD1);
}

inline int gethash2l(int l,int r)
{
	return sub(h2l[r]-(1ll*h2l[l-1]*pw2[r-l+1])%MOD2,MOD2);
}

inline int gethash1r(int l,int r)
{
	return sub(h1r[r]-h1r[l-1],MOD1);
}

inline int gethash2r(int l,int r)
{
	return sub(h2r[r]-h2r[l-1],MOD2);
}

inline bool ispal(int l,int r)
{
	if ((1ll*gethash1l(l,r)*pw1[l-1])%MOD1==gethash1r(l,r) && (1ll*gethash2l(l,r)*pw2[l-1])%MOD2==gethash2r(l,r))
		return true;
	else
		return false;
}

int main ()
{
	d=getint();scanf("%s",s+1);len=strlen(s+1);
	pw1[0]=pw2[0]=1;int i;
	for (i=1;i<=len;i++) pw1[i]=(1ll*pw1[i-1]*p1)%MOD1,pw2[i]=(1ll*pw2[i-1]*p2)%MOD2;
	int fi=len;
	for (i=1;i<=len;i++)
	{
		h1l[i]=(1ll*h1l[i-1]*p1+s[i])%MOD1;
		h2l[i]=(1ll*h2l[i-1]*p2+s[i])%MOD2;
		h1r[i]=add(h1r[i-1]+(1ll*pw1[i-1]*s[i])%MOD1,MOD1);
		h2r[i]=add(h2r[i-1]+(1ll*pw2[i-1]*s[i])%MOD2,MOD2);
		if (i>=d && ispal(i-d+1,i)) {fi=i;break;}
		if (i>=d+1 && ispal(i-d,i)) {fi=i;break;}	
	}
	bool f=false;
	for (i=fi;i>=1;i--)
	{
		for (auto ch=s[i]+1;ch<='z';ch++)
		{
			s[i]=ch;
			h1l[i]=(1ll*h1l[i-1]*p1+s[i])%MOD1;
			h2l[i]=(1ll*h2l[i-1]*p2+s[i])%MOD2;
			h1r[i]=add(h1r[i-1]+(1ll*pw1[i-1]*s[i])%MOD1,MOD1);
			h2r[i]=add(h2r[i-1]+(1ll*pw2[i-1]*s[i])%MOD2,MOD2);
			if (i>=d && ispal(i-d+1,i)) continue;
			if (i>=d+1 && ispal(i-d,i)) continue;
			f=true;break;
		}
		if (f) break;
	}
	if (!f)
	{
		puts("Impossible");
		return 0;
	}
	int st=i;
	for (i=st+1;i<=len;i++)
	{
		for (auto ch='a';ch<='z';ch++)
		{
			s[i]=ch;
			h1l[i]=(1ll*h1l[i-1]*p1+s[i])%MOD1;
			h2l[i]=(1ll*h2l[i-1]*p2+s[i])%MOD2;
			h1r[i]=add(h1r[i-1]+(1ll*pw1[i-1]*s[i])%MOD1,MOD1);
			h2r[i]=add(h2r[i-1]+(1ll*pw2[i-1]*s[i])%MOD2,MOD2);	
			if (i>=d && ispal(i-d+1,i)) continue;
			if (i>=d+1 && ispal(i-d,i)) continue;
			break;
		}
	}
	printf("%s",s+1);
	return 0;
}
