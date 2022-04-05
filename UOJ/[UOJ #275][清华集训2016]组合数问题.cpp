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
const int MOD=1e9+7;
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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int dp[148][48];
int limi[148],limj[148],tot1,tot2;
LL n,m;int k;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int ca;ca=getint();k=getint();
	while (ca--)
	{
		n=getLL();m=getLL();LL tmp;int i,p,q,il,ir,jl,jr,iLim,jLim,equal,smaller,Mask,toMask;
		m=min(n,m);tot1=tot2=0;
		tmp=n;while (tmp) limi[++tot1]=tmp%k,tmp/=k;
		tmp=m;while (tmp) limj[++tot2]=tmp%k,tmp/=k;
		for (i=tot2+1;i<=tot1;i++) limj[i]=0;
		reverse(limi+1,limi+tot1+1);reverse(limj+1,limj+tot1+1);
		memset(dp,0,sizeof(dp));
		dp[0][15]=1;
		for (i=0;i<=tot1-1;i++)
			for (Mask=0;Mask<=15;Mask++)
				if (dp[i][Mask])
					for (toMask=0;toMask<=15;toMask++)
					{
						if (!(toMask&8) && (toMask&4 || (!(toMask&4) && (Mask&4)))) continue;
						if ((toMask&Mask)==toMask)
						{
							int coef=0;
							if (toMask&1) il=ir=limi[i+1];
							else if (Mask&1) il=0,ir=limi[i+1]-1; else il=0,ir=k-1;
							if (toMask&2) jl=jr=limj[i+1];
							else if (Mask&2) jl=0,jr=limj[i+1]-1; else jl=0,jr=k-1;
							for (p=il;p<=ir;p++)
								for (q=jl;q<=jr;q++)
								{
									if ((toMask&4) && p!=q) continue;
									if (!(toMask&4) && (Mask&4) && p<=q) continue;
									if ((toMask&8) && p<q) continue;
									if (!(toMask&8) && (Mask&8) && p>=q) continue;
									coef++;
								}
							dp[i+1][toMask]=add(dp[i+1][toMask]+(1ll*coef*dp[i][Mask])%MOD);
						}
					}
		int ans=0;
		for (Mask=0;Mask<=15;Mask++)
			if (!(Mask&8)) ans=add(ans+dp[tot1][Mask]);
		printf("%d\n",ans);
	}
	return 0;
}
