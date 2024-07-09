#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

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
	x=(f?res:(-res));
}

template<typename T1,typename...T2> inline void Get(T1 &x,T2&...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=5e5;

int n;char s[MAXN+48];
int dp[MAXN+48];

int rnk[MAXN+48],lcp[MAXN+48];

namespace SA
{
	int fir[MAXN+48],sec[MAXN+48],cnt[MAXN+48],sa[MAXN+48],tmp[MAXN+48],maxind;
	inline bool compare_sa(int x,int y,int k)
	{
		if (fir[x]!=fir[y]) return fir[x]<fir[y];
		int tmp1=(x+k<=n?fir[x+k]:-1),tmp2=(y+k<=n?fir[y+k]:-1);
		return tmp1<tmp2;
	}
	inline void construct_sa()
	{
		maxind='z';memset(cnt+1,0,maxind<<2);
		for (register int i=1;i<=n;i++) cnt[s[i]]++;
		for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
		for (register int i=n;i>=1;i--) sa[cnt[s[i]]--]=i;
		fir[sa[1]]=1;for (register int i=2;i<=n;i++) fir[sa[i]]=fir[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
		for (register int len=1;len<=n;len<<=1)
		{
			memset(cnt+1,0,maxind<<2);int tot=0;
			for (register int i=n-len+1;i<=n;i++) sec[++tot]=i;
			for (register int i=1;i<=n;i++) if (sa[i]>len) sec[++tot]=sa[i]-len;
			for (register int i=1;i<=n;i++) cnt[fir[sec[i]]]++;
			for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (register int i=n;i>=1;i--) sa[cnt[fir[sec[i]]]--]=sec[i];
			tmp[sa[1]]=1;for (register int i=2;i<=n;i++) tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i],len);
			memcpy(fir+1,tmp+1,n<<2);maxind=fir[sa[n]];if (maxind>=n) break;
		}
	}
	inline void construct_lcp()
	{
		int h=0;
		for (register int i=1;i<=n;i++) rnk[sa[i]]=i;
		for (register int i=1;i<=n;i++)
		{
			int j=sa[rnk[i]-1];
			if (h) h--;
			while (i+h<=n && j+h<=n && s[i+h]==s[j+h]) h++;
			lcp[rnk[i]-1]=h;
		}
	}
}

int Log[MAXN+48],ST[MAXN+48][21];

inline void init_ST()
{
	Log[0]=Log[1]=0;for (register int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for (register int i=1;i<=n;i++) ST[i][0]=lcp[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=n;i++)
		{
			ST[i][j]=ST[i][j-1];
			if (i+(1<<(j-1))<=n) check_min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
		}
}

inline int query_ST(int left,int right)
{
	int k=right-left+1;
	return min(ST[left][Log[k]],ST[right-(1<<Log[k])+1][Log[k]]);
}

inline int query_lcp(int pos1,int pos2)
{
	if (pos1>pos2) swap(pos1,pos2);
	return query_ST(pos1,pos2-1);
}

namespace SegmentTree
{
	int maxn[MAXN*4];
	inline void pushup(int cur) {maxn[cur]=max(maxn[cur<<1],maxn[cur<<1|1]);}
	inline void build(int cur,int l,int r)
	{
		if (l==r) {maxn[cur]=-1;return;}
		int mid=(l+r)>>1;
		build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
		pushup(cur);
	}
	inline void modify(int cur,int pos,int nv,int l,int r)
	{
		if (l==r) {maxn[cur]=nv;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) modify(cur<<1,pos,nv,l,mid); else modify(cur<<1|1,pos,nv,mid+1,r);
		pushup(cur);
	}
	inline int query(int cur,int left,int right,int l,int r)
	{
		if (left<=l && r<=right) return maxn[cur];
		int mid=(l+r)>>1,res=-1;
		if (left<=mid) check_max(res,query(cur<<1,left,right,l,mid));
		if (mid+1<=right) check_max(res,query(cur<<1|1,left,right,mid+1,r));
		return res;
	}
}

inline Pair find_range(int pos,int val)
{
	Pair res=mp(pos,pos);int l=1,r=pos-1,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (query_lcp(mid,pos)>=val) res.x=mid,r=mid-1; else l=mid+1;
	}
	l=pos+1;r=n;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (query_lcp(pos,mid)>=val) res.y=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

int lim;

inline bool check(int pos,int val)
{
	if (pos+val>n) return false;
	while (lim>pos+val) --lim,SegmentTree::modify(1,rnk[lim],dp[lim],1,n);
	Pair range=find_range(rnk[pos],val-1);
	if (SegmentTree::query(1,range.x,range.y,1,n)>=val-1) return true;
	range=find_range(rnk[pos+1],val-1);
	if (SegmentTree::query(1,range.x,range.y,1,n)>=val-1) return true;
	return false;
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n);scanf("%s",s+1);
	SA::construct_sa();SA::construct_lcp();SegmentTree::build(1,1,n);init_ST();
	int val=0,ans=0;lim=n+1;
	for (register int i=n;i>=1;i--)
	{
		val++;
		while (val>1 && !check(i,val)) val--;
		dp[i]=val;check_max(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}
