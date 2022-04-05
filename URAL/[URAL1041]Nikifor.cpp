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

const int MOD=123456789;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-8;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

const int p=998244353;
struct Vector
{
	LL A[68];
	int cost,ind;
	inline bool operator < (const Vector &other) const
	{
		if (cost!=other.cost) return cost<other.cost;
		return ind<other.ind;
	}
}a[2048];

int n,m;
Vector base[148];
int ansind[148];

/*inline LB myabs(LB x)
{
	if (x>eps) return x;
	if (x<-eps) return -x;
	return 0;
}
inline bool Alive(long double x) {return myabs(x)>eps;}*/

inline int query_gcd(int x,int y) {return y==0?x:query_gcd(y,x%y);}

inline bool Insert(int cur)
{
	int i,j;
	for (i=1;i<=n;i++)
		if (a[cur].A[i])
			if (!base[i].ind)
			{
				base[i]=a[cur];
				return true;
			}
			else
			{
				//LB t=a[cur].A[i]/base[i].A[i];	
				int g=query_gcd(a[cur].A[i],base[i].A[i]);
				int c1=a[cur].A[i]/g,c2=base[i].A[i]/g;
				for (j=i;j<=n;j++) a[cur].A[j]=(a[cur].A[j]*c2-base[i].A[j]*c1)%p;
			}
	return false;
}

int main ()
{
	int i,j;m=getint();n=getint();
	for (i=1;i<=m;i++)	
		for (j=1;j<=n;j++)
			a[i].A[j]=getint();
	for (i=1;i<=m;i++) a[i].cost=getint(),a[i].ind=i;
	sort(a+1,a+m+1);int ans=0;
	for (i=1;i<=m;i++)
		if (Insert(i)) ans+=a[i].cost;
	for (i=1;i<=n;i++) if (!base[i].ind) {puts("0");return 0;}
	for (i=1;i<=n;i++) ansind[i]=base[i].ind;
	sort(ansind+1,ansind+n+1);
	printf("%d\n",ans);
	for (i=1;i<=n;i++) printf("%d\n",ansind[i]);
	return 0;
}
