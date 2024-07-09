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
const int INF=1e9;
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

typedef bitset<100048> bs;

struct equation
{
	bs b;int res;
	inline void init() {b=0;res=0;}
}cur;
map<int,equation> b;
bool exist[100048];

int n;
LL a[100048];
int maxbit;
int ans[148];
int sol[100048];

inline bool check()
{
	int bit,i;
	for (i=1;i<=n;i++)
		if (cur.b[i])
			if (exist[i]) cur.b^=b[i].b,cur.res^=b[i].res; else {b[i]=cur;exist[i]=true;return true;}
	if (cur.res) return false; else return true;
}

inline void find_solution()
{
	int i,j;
	for (i=n;i>=1;i--)
	{
		if (!exist[i]) {sol[i]=0;continue;}
		for (j=i+1;j<=n;j++)
			if (b[i].b[j]) b[i].res^=sol[j];
		sol[i]=b[i].res;
	}
}		

int main ()
{
	int i,bit;n=getint();
	for (i=1;i<=n;i++) a[i]=getLL();
	for (maxbit=63;maxbit;maxbit--)
	{
		bool f=false;
		for (i=1;i<=n;i++)
			if (a[i]&(1ll<<(maxbit-1))) {f=true;break;}
		if (f) break;
	}
	for (bit=maxbit;bit;bit--)
	{
		cur.init();
		for (i=1;i<=n;i++)
			if (a[i]&(1ll<<(bit-1))) cur.b[i]=1,cur.res++;
		if (cur.res%2==1) {ans[bit]=1;continue;}
		cur.res=1;
		if (check()) ans[bit]=2; else ans[bit]=0;
	}
	for (bit=maxbit;bit;bit--)
		if (ans[bit]==1)
		{
			cur.init();
			for (i=1;i<=n;i++)
				if (a[i]&(1ll<<(bit-1))) cur.b[i]=1;
			cur.res=0;
			check();
		}
	find_solution();
	for (i=1;i<=n;i++) printf("%d ",2-sol[i]);
	return 0;
}
