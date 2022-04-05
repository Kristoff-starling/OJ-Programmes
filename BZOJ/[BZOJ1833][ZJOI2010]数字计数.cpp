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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL A,B;
LL ans[20];

int num[20],ntot;

inline void Decompose(LL x) {ntot=0;while (x) num[++ntot]=x%10,x/=10;reverse(num+1,num+ntot+1);}

inline LL getbefore(int pos)
{
	LL res=0;
	for (register int i=1;i<=pos;i++) res=res*10+num[i];
	return res;
}

inline LL mypow(LL x,LL y)
{
	LL res=1;
	while (y) res*=x,y--;
	return res;
}

inline void solve(LL lim,int fl)
{
	if (!lim) return;
	Decompose(lim);
	int i,j;LL bef,aft;
	for (i=0;i<=9;i++)
		for (j=(i?1:2);j<=ntot;j++)
		{
			bef=getbefore(j-1);
			if (!i) bef--;
			aft=mypow(10,ntot-j);
			ans[i]+=bef*aft*fl;
			if (i<num[j]) ans[i]+=aft*fl;
			if (i==num[j])
			{
				aft=lim-getbefore(j)*mypow(10,ntot-j)+1;
				ans[i]+=aft*fl;
			}
		}
}

int main ()
{
	A=getLL();B=getLL();
	solve(B,1);solve(A-1,-1);
	for (register int i=0;i<=9;i++) printf("%lld ",ans[i]);
	puts("");return 0;
}
