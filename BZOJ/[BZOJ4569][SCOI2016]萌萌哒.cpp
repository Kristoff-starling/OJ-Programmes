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

int n,q;

const int MAXN=1e5,LMAX=18;
int pre[MAXN*20+48];
int Log[MAXN+48];

inline int getind(int layer,int pos)
{
	return layer*n+pos;
}

inline void init() {for (register int i=1;i<=LMAX*n+n;i++) pre[i]=i;}
inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
inline bool update(int x,int y) {x=find_anc(x);y=find_anc(y);if (x!=y) {pre[x]=y;return true;} else return false;}
inline void merge(int l,int r,int layer)
{
	bool res=update(getind(layer,l),getind(layer,r));
	if (!layer) return;
	if (res) merge(l,r,layer-1),merge(l+(1<<(layer-1)),r+(1<<(layer-1)),layer-1);
}

set<int> s;

int main ()
{
	int i,l1,r1,l2,r2;
	n=getint();q=getint();init();
	Log[0]=Log[1]=0;for (i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	while (q--)
	{
		l1=getint();r1=getint();l2=getint();r2=getint();
		if (l1>l2) swap(l1,l2),swap(r1,r2);
		int st=Log[r1-l1+1];
		merge(l1,l2,st);merge(r1-(1<<st)+1,r2-(1<<st)+1,st);
	}
	s.clear();int cnt=0;
	for (i=1;i<=n;i++)
	{
		int tmp=find_anc(getind(0,i));
		if (!s.count(tmp)) cnt++,s.insert(tmp);
	}
	if (cnt==1) {puts("10");return 0;}
	cnt--;LL ans=9;
	while (cnt--) ans=(ans*10)%MOD;
	printf("%lld\n",ans);
	return 0;
}
