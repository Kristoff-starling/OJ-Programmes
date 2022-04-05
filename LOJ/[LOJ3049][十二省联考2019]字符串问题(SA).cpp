#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=2e5;

char s[MAXN+48];int len;
int na,la[MAXN+48],ra[MAXN+48];
int nb,lb[MAXN+48],rb[MAXN+48];
int m;vector<int> v[MAXN+48];

struct node
{
	int type,pos,len,id;
	node () {}
	inline node (int _t,int _p,int _l,int _i) {type=_t;pos=_p;len=_l;id=_i;}
	inline bool operator < (const node &other) const
	{
		if (len!=other.len) return len>other.len;
		return type<other.type;
	}
}str[MAXN*2+48];int stot;

int lcp[MAXN+48],rnk[MAXN+48],sa[MAXN+48];

namespace SA
{
	int fir[MAXN+48],sec[MAXN+48],tmp[MAXN+48],cnt[MAXN+48],maxind,tot;
	inline bool compare_sa(int x,int y,int k)
	{
		if (fir[x]!=fir[y]) return fir[x]<fir[y];
		int tmp1=(x+k<=len?fir[x+k]:-1),tmp2=(y+k<=len?fir[y+k]:-1);
		return tmp1<tmp2;
	}
	inline void construct_sa()
	{
		maxind='z';
		memset(cnt+1,0,maxind<<2);
		for (register int i=1;i<=len;i++) cnt[s[i]]++;
		for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
		for (register int i=len;i>=1;i--) sa[cnt[s[i]]--]=i;
		fir[sa[1]]=1;for (register int i=2;i<=len;i++) fir[sa[i]]=fir[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
		for (register int k=1;k<=len;k<<=1)
		{
			tot=0;memset(cnt+1,0,maxind<<2);
			for (register int i=len-k+1;i<=len;i++) sec[++tot]=i;
			for (register int i=1;i<=len;i++) if (sa[i]>k) sec[++tot]=sa[i]-k;
			for (register int i=1;i<=len;i++) cnt[fir[sec[i]]]++;
			for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (register int i=len;i>=1;i--) sa[cnt[fir[sec[i]]]--]=sec[i];
			tmp[sa[1]]=1;for (register int i=2;i<=len;i++) tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i],k);
			memcpy(fir+1,tmp+1,len<<2);maxind=fir[sa[len]];if (maxind>=len) break;
		}
	}
	inline void construct_lcp()
	{
		for (register int i=1;i<=len;i++) rnk[sa[i]]=i;
		int h=0;
		for (register int i=1;i<=len;i++)
		{
			int j=sa[rnk[i]-1];
			if (h) h--;
			while (i+h<=len && j+h<=len && s[i+h]==s[j+h]) h++;
			lcp[rnk[i]-1]=h;
		}
	}
}

int ST[MAXN+48][21],Log[MAXN+48];

inline void init_ST()
{
	Log[0]=Log[1]=0;for (register int i=2;i<=len;i++) Log[i]=Log[i>>1]+1;
	for (register int i=1;i<=len-1;i++) ST[i][0]=lcp[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=len-1;i++)
		{
			ST[i][j]=ST[i][j-1];
			if (i+(1<<(j-1))<=len) check_min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
		}
}

inline int query_ST(int l,int r)
{
	int k=r-l+1;
	return min(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
}

inline int query_lcp(int pos1,int pos2)
{
	if (pos1>pos2) swap(pos1,pos2);
	if (pos1==pos2) return len-sa[pos1]+1;
	return query_ST(pos1,pos2-1);
}

vector<int> vv[MAXN*20+48];
int d[MAXN*20+48],val[MAXN*20+48],sgt[MAXN+48],ps[MAXN+48];

int seq[MAXN+48];
inline bool cmpa(int x,int y) {return rnk[la[x]]<rnk[la[y]];}

inline void addedge(int x,int y) {vv[x].pb(y);d[y]++;}

LL dp[MAXN*21+48];
int head,tail,q[MAXN*21+48];

inline LL solve(int cur)
{
	if (dp[cur]!=-1) return dp[cur];
	dp[cur]=0;
	for (auto y : vv[cur]) check_max(dp[cur],solve(y));
	return dp[cur]+=val[cur];
}

inline Pair getrange(int id)
{
	int l,r,pos=na+1,mid,cmp=rb[id]-lb[id]+1;
	l=1;r=na;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (rnk[lb[id]]<rnk[la[seq[mid]]]) pos=mid,r=mid-1; else l=mid+1;
	}
	Pair res=mp(pos,pos-1);
	l=1;r=pos-1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (query_lcp(rnk[la[seq[mid]]],rnk[lb[id]])>=cmp) res.x=mid,r=mid-1; else l=mid+1;
	}
	l=pos;r=na;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (query_lcp(rnk[la[seq[mid]]],rnk[lb[id]])>=cmp) res.y=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

int tot;

namespace SegmentTree
{
	int lson[MAXN*20+48],rson[MAXN*20+48],Root;
	inline int Create() {++tot;lson[tot]=rson[tot]=0;d[tot]=val[tot]=0;vv[tot].clear();return tot;}
	inline void init() {tot=nb;Root=Create();}
	inline void insert(int cur,int last,int pos,int id,int l,int r)
	{
		if (l==r) {sgt[id]=cur;val[cur]=ra[id]-la[id]+1;return;}
		lson[cur]=lson[last];rson[cur]=rson[last];
		int mid=(l+r)>>1;
		if (pos<=mid) lson[cur]=Create(),insert(lson[cur],lson[last],pos,id,l,mid);
		else rson[cur]=Create(),insert(rson[cur],rson[last],pos,id,mid+1,r);
	}
	inline void addinterval(int cur,int left,int right,int id,int l,int r)
	{
		if (left>right) return;
		if (!cur) return;
		if (left<=l && r<=right) {addedge(id,cur);return;}
		int mid=(l+r)>>1;
		if (left<=mid) addinterval(lson[cur],left,right,id,l,mid);
		if (mid+1<=right) addinterval(rson[cur],left,right,id,mid+1,r);
	}
	inline void buildedge()
	{
		for (register int cur=nb+1;cur<=tot;cur++)
		{
			if (lson[cur]) addedge(cur,lson[cur]);
			if (rson[cur]) addedge(cur,rson[cur]);
		}
	}
}

inline void input()
{
	scanf("%s",s+1);len=strlen(s+1);stot=0;
	Get(na);for (register int i=1;i<=na;i++) Get(la[i],ra[i]),str[++stot]=node(0,la[i],ra[i]-la[i]+1,i);
	Get(nb);for (register int i=1;i<=nb;i++) Get(lb[i],rb[i]),str[++stot]=node(1,lb[i],rb[i]-lb[i]+1,i);
	Get(m);int x,y;
	for (register int i=1;i<=na;i++) v[i].clear();
	for (register int i=1;i<=m;i++) Get(x,y),v[x].pb(y);
}

bool visited[MAXN+48];

inline void Clear()
{
	for (register int i=1;i<=nb;i++) vv[i].clear(),d[i]=0,val[i]=0;
	for (register int i=1;i<=na*20+nb;i++) dp[i]=-1;
	head=1;tail=0;
	SegmentTree::init();
}

inline void solve()
{
	SA::construct_sa();SA::construct_lcp();
	init_ST();
	sort(str+1,str+stot+1);
	for (register int i=1;i<=na;i++) seq[i]=i;
	sort(seq+1,seq+na+1,cmpa);
	for (register int i=1;i<=na;i++) ps[seq[i]]=i;
	for (register int i=1;i<=stot;i++)
		if (str[i].type==0)
		{
			int curRoot=SegmentTree::Create();
			SegmentTree::insert(curRoot,SegmentTree::Root,ps[str[i].id],str[i].id,1,na);
			SegmentTree::Root=curRoot;
		}
		else
		{
			Pair r=getrange(str[i].id);
			SegmentTree::addinterval(SegmentTree::Root,r.x,r.y,str[i].id,1,na);
		}
	for (register int i=1;i<=na;i++)
		for (register int j=0;j<int(v[i].size());j++)
			addedge(sgt[i],v[i][j]);
	SegmentTree::buildedge();
	for (register int i=1;i<=tot;i++) if (!d[i]) q[++tail]=i;
	int cnt=0;
	while (head<=tail)
	{
		int cur=q[head++];cnt++;
		for (auto y : vv[cur])
		{
			d[y]--;
			if (!d[y]) q[++tail]=y;
		}
	}
	if (cnt<tot) {puts("-1");return;}
	LL ans=0;
	for (register int i=1;i<=tot;i++) check_max(ans,solve(i));
	printf("%lld\n",ans);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;Get(ca);
	while (ca--)
	{
		input();
		Clear();
		solve();
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
