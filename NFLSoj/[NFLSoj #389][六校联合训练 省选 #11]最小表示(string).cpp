#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2&...y) {Get(x);Get(y...);}

const int MAXN=5e4;

int n,m;
char s[MAXN+48];
int nxt[MAXN+48][11];

int sa[MAXN+48];

LL hsh[11][MAXN+48],pw[MAXN+48];
const int p=41;

inline void init_hash()
{
	for (register int i=1;i<=m;i++) hsh[i][0]=0;
	for (register int i=1;i<=n;i++)
	{
		int cur=s[i]-'a'+1;
		for (register int j=1;j<=m;j++) if (j!=cur) hsh[j][i]=(hsh[j][i-1]*p+17)%MOD;
		hsh[cur][i]=(hsh[cur][i-1]*p+23)%MOD;
	}
	pw[0]=1;for (register int i=1;i<=n;i++) pw[i]=pw[i-1]*p%MOD;
}

inline LL query_hash(int ch,int left,int right)
{
	return (hsh[ch][right]-hsh[ch][left-1]*pw[right-left+1]%MOD+MOD)%MOD;
}

inline bool check_same(int x,int y,int len)
{
	LL pro1=1,pro2=1;
	for (register int i=1;i<=m;i++) pro1=(pro1*query_hash(i,x,x+len-1))%MOD,pro2=(pro2*query_hash(i,y,y+len-1))%MOD;
	return pro1==pro2;
}

inline int getrnk(int st,int pos)
{
	int res=0,w=s[pos]-'a'+1,cmp=nxt[st][w];
	for (register int i=1;i<=m;i++) if (i!=w && nxt[st][i]<cmp) res++;
	return res+1;
}

inline bool compare_sa(int x,int y)
{
	if (x>y && check_same(x,y,n-x+1)) return true;
	if (x<y && check_same(x,y,n-y+1)) return false;
	int l=1,r=min(n-x+1,n-y+1),mid,Len=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (check_same(x,y,mid)) Len=mid,l=mid+1; else r=mid-1;
	}
	int r1=getrnk(x,x+Len),r2=getrnk(y,y+Len);
	return r1<r2;
}

inline int query_lcp(int x,int y)
{
	if (x>y) swap(x,y);
	if (check_same(x,y,n-y+1)) return n-y+1;
	int l=1,r=n-y+1,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (check_same(x,y,mid)) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n,m);scanf("%s",s+1);
	init_hash();
	for (register int j=1;j<=m;j++) nxt[n+1][j]=n+1;
	for (register int i=n;i>=1;i--)
	{
		for (register int j=1;j<=m;j++) nxt[i][j]=nxt[i+1][j];
		nxt[i][s[i]-'a'+1]=i;
	}
	for (register int i=1;i<=n;i++) sa[i]=i;
	sort(sa+1,sa+n+1,compare_sa);
	LL ans=1ll*(n+1)*n/2;
	for (register int i=1;i<=n-1;i++) ans-=query_lcp(sa[i],sa[i+1]);
	printf("%lld\n",ans);return 0;
}
