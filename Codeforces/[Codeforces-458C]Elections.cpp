#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int 
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

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline void gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;

int n;
vector<int> v[MAXN+48];

int cc[MAXN+48];

inline int calc(int cmp)
{
	if (cmp==n) return INF;
	int cnt=int(v[0].size()),res=0;
	for (register int i=0;i<=10000;i++) cc[i]=0;
	for (register int i=1;i<=MAXN;i++)
	{
		if (int(v[i].size())>cmp)
		{
			for (register int j=0;j<int(v[i].size())-cmp;j++) res+=v[i][j];
			cnt+=int(v[i].size())-cmp;
		}
		int st=((int(v[i].size())>cmp)?int(v[i].size())-cmp:0);
		for (register int j=st;j<int(v[i].size());j++) cc[v[i][j]]++;
	}
	int pt=0;
	while (cnt<=cmp)
	{
		while (!cc[pt]) pt++;
		res+=pt;cnt++;cc[pt]--;
	}
	return res;
}

int main ()
{
	Get(n);int x,y;
	for (register int i=1;i<=n;i++) Get(x),Get(y),v[x].pb(y);
	for (register int i=0;i<=MAXN;i++) sort(v[i].begin(),v[i].end());
	int l=0,r=n,mid1,mid2;
	while (r-l+1>10)
	{
		mid1=(l+l+r)/3;mid2=(l+r+r)/3;
		if (calc(mid1)>calc(mid2)) l=mid1; else r=mid2;
	}
	int ans=INF;
	for (register int i=l;i<=r;i++) check_min(ans,calc(i));
	printf("%d\n",ans);
	return 0;
}
