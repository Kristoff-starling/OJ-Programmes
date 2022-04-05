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

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=1000;
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

int A,B,K;

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res*=x,y--;
		x*=x;y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=(res*x)%MO,y--;
		x=(x*x)%MO;y>>=1;
	}
	return res;
}

inline int gcd(int x,int y) {return y==0?x:gcd(y,x%y);}

int prime[200048],tot;bool isprime[200048];
inline void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=200000;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && (long long)i*prime[j]<=200000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
}

int plist[200048],nlist[200048];int ptot;
inline void Decompose(int cur)
{
	int i;
	for (i=1;i<=tot;i++)
		if (cur%prime[i]==0)
		{
			plist[++ptot]=prime[i];nlist[ptot]=0;
			while (cur%prime[i]==0) nlist[ptot]++,cur/=prime[i];
		}
	if (cur!=1) plist[++ptot]=cur,nlist[ptot]=1;
}

vector<int> pri;
inline int query(int p,int a)
{
	int P=quick_pow(p,a);
	int phi=P-quick_pow(p,a-1),tmp=phi;
	int i;pri.clear();
	for (i=1;i<=tot;i++)
		if (tmp%prime[i]==0)
		{
			pri.pb(prime[i]);
			while (tmp%prime[i]==0) tmp/=prime[i];
		}
	if (tmp>1) pri.pb(tmp);
	int res=2;
	do
	{
		bool f=true;
		for (i=0;i<int(pri.size());i++)
			if (quick_pow(res,phi/pri[i],P)==1) {f=false;break;}
		if (f) return res;
		res++;
	}
	while (true);
}

map<int,int> table;
inline int BSGS(int g,int b,int p)
{
	table.clear();
	if (b==1) return 0;
	int i,j;
	for (j=0;j<=magic-1;j++) table[((long long)quick_pow(g,j,p)*b)%p]=j;
	int lim=p/magic;
	for (i=1;i<=lim;i++)
	{
		int res=table[quick_pow(g,i*magic,p)];
		if (res) return i*magic-res;
	}
	for (j=0;j<=magic-1;j++)
	{
		int cur=(long long)(lim+1)*magic-j;
		if (cur<=p-1 && quick_pow(g,cur,p)==b) return cur;
	}
}

inline int solve0(int b,int p,int a)
{
	int g=query(p,a),P=quick_pow(p,a);
	int r=BSGS(g,b,P);
	int newp=P-quick_pow(p,a-1);
	if (r%gcd(A,newp)) return 0;
	return gcd(A,newp);
}

inline int solve(int ind)
{
	int MO=quick_pow(plist[ind],nlist[ind]);
	if (B%MO==0)
	{
		int lim=nlist[ind]/A+(nlist[ind]%A==0?0:1);
		return quick_pow(plist[ind],nlist[ind]-lim);
	}
	int cnt=0,b=B;
	while (b%plist[ind]==0) cnt++,b/=plist[ind];
	if (cnt)
	{
		if (cnt%A) return 0;
		int res=solve0(b,plist[ind],nlist[ind]-cnt);
		return res*quick_pow(plist[ind],cnt-cnt/A);
	}
	else
		return solve0(b,plist[ind],nlist[ind]);
}

int main ()
{
	int ca;ca=getint();
	sieve();
	while (ca--)
	{
		A=getint();B=getint();K=getint();K=2*K+1;B%=K;
		ptot=0;Decompose(K);
		int ans=1;for (register int i=1;i<=ptot;i++) ans*=solve(i);
		printf("%d\n",ans);
	}
	return 0;
}
