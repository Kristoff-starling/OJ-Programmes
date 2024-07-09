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

const int MAXN=1e5;

char s[1048],t[1048];int n,m,q;

int a[1048],tot=0;

inline bool check_same(int pos)
{
	int i;
	for (i=1;i<=m;i++) if (t[i]!=s[pos+i-1]) return false;
	return true;
}

inline int bsearch1(int pos)
{
	int l=1,r=tot,mid,res=tot+1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (a[mid]>=pos) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

inline int bsearch2(int pos)
{
	int l=1,r=tot,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (a[mid]<=pos) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

int main ()
{
	n=getint();m=getint();q=getint();
	scanf("%s",s+1);scanf("%s",t+1);int i;
	for (i=1;i<=n-m+1;i++)
		if (check_same(i)) a[++tot]=i;
	while (q--)
	{
		int l=getint(),r=getint();
		if (r-l+1<m || !tot) {puts("0");continue;}
		r=r-m+1;
		int pos1=bsearch1(l),pos2=bsearch2(r);
		printf("%d\n",pos2-pos1+1);
	}
	return 0;
}
