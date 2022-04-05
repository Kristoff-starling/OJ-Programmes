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
#define LOWBIT(x) x & (-x)

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

const int MAXN=1e6;

int n,m;
Pair a[MAXN+48];int tot;
int ans[MAXN+48];

priority_queue<int> q;

inline bool cmp(Pair x,Pair y)
{
	if (x.x!=y.x) return x.x<y.x;
	return x.y-x.x+1>y.y-y.x+1;
}

int main ()
{
	int i,ca;ca=getint();int x,y,j;
	while (ca--)
	{
		n=getint();m=getint();
		for (i=1;i<=m;i++) a[i].x=getint(),a[i].y=getint();
		for (i=m+1;i<=m+n;i++) a[i].x=a[i].y=i-m;
		tot=n+m;
		sort(a+1,a+tot+1,cmp);
		while (!q.empty()) q.pop();
		for (i=1;i<=n;i++) q.push(-i);
		int l=1,r=0;
		for (i=1;i<=tot;i++)
		{
			if (a[i].y<=r) continue;
			while (l<a[i].x) q.push(-ans[l++]);
			while (r<a[i].y) ans[++r]=-q.top(),q.pop();
		}
		for (i=1;i<=n;i++) {printf("%d",ans[i]);if (i!=n) printf(" ");}
		puts("");
	}
	return 0;
}
