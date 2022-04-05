#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))

const int INF=2e0;
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

const int MAXN=5e5;

char s[MAXN+48],S[MAXN+48];int len,len2;
int d[MAXN+48];

int Root[MAXN*2];
namespace SegmentTree
{
	int sum[MAXN*2*20+48],lson[MAXN*2*20+48],rson[MAXN*2*20+48],tot=0;
	inline int Create() {++tot;sum[tot]=lson[tot]=rson[tot]=0;return tot;}
	inline void pushup(int cur) {sum[cur]=sum[lson[cur]]+sum[rson[cur]];}
	inline void insert(int &cur,int pos,int l,int r)
	{
		if (!cur) cur=Create();
		if (l==r) {sum[cur]++;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) insert(lson[cur],pos,l,mid); else insert(rson[cur],pos,mid+1,r);
		pushup(cur);
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
		int res=Create();
		lson[res]=merge(lson[root1],lson[root2]);rson[res]=merge(rson[root1],rson[root2]);
		pushup(res);return res;
	}
	inline int query(int cur,int left,int right,int l,int r)
	{
		if (left>right) return 0;
		if (!cur) return 0;
		if (left<=l && r<=right) return sum[cur];
		int res=0,mid=(l+r)>>1;
		if (left<=mid) res+=query(lson[cur],left,right,l,mid);
		if (mid+1<=right) res+=query(rson[cur],left,right,mid+1,r);
		return res;
	}
}

struct SAM
{
	int nxt[MAXN*2][27],occ[MAXN*2],par[MAXN*2],maxn[MAXN*2],tot,last,root;
	vector<int> v[MAXN*2];
	inline int Create() {++tot;occ[tot]=par[tot]=maxn[tot]=0;memset(nxt[tot],0,sizeof(nxt[tot]));return tot;}
	inline void init() {tot=0;root=last=Create();}
	inline void extend(char ch,int ind)
	{
		int p=last,np=Create(),w=ch-'a'+1;maxn[np]=maxn[p]+1;occ[np]=ind;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=root;last=np;return;}
		int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
		int nq=Create();maxn[nq]=maxn[p]+1;
		memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[q]=par[np]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
		last=np;
	}
	inline void construct(char s[])
	{
		int len=strlen(s+1);init();
		for (register int i=1;i<=len;i++) extend(s[i],i);
	}
	Pair ord[MAXN*2];
	inline void dfs(int cur)
	{
		for (auto y : v[cur])
			dfs(y),Root[cur]=SegmentTree::merge(Root[cur],Root[y]);
	}
	inline void update()
	{
		for (register int i=1;i<=tot;i++) ord[i]=mp(maxn[i],i);
		sort(ord+1,ord+tot+1);
		for (register int i=tot;i>=2;i--)
		{
			int cur=ord[i].y;
			if (occ[cur]) occ[par[cur]]=occ[cur];
		}
	}
	inline void build()
	{
		for (register int i=2;i<=tot;i++)
		{
			v[par[i]].pb(i);
			if (occ[i]) SegmentTree::insert(Root[i],occ[i],1,len);
		}
		dfs(root);
	}
}s1,s2;

int main ()
{
#ifdef ONLINE_JUDGE
	freopen ("name.in","r",stdin);
	freopen ("name.out","w",stdout);
#else
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	scanf("%s",s+1);len=strlen(s+1);
	s1.construct(s);s1.build();
	int q,l,r;scanf("%d",&q);
	while (q--)
	{
		scanf("%s%d%d",S+1,&l,&r);len2=strlen(S+1);
		s2.construct(S);s2.update();
		int cur=s1.root,cnt=0;
		for (register int i=1;i<=len2;i++)
		{
			int w=S[i]-'a'+1;
			for (;;)
			{
				if (s1.nxt[cur][w] && SegmentTree::query(Root[s1.nxt[cur][w]],l+cnt,r,1,len))
				{
					cur=s1.nxt[cur][w];cnt++;
					break;
				}
				if (!cnt) break;
				cnt--;
				if (cnt==s1.maxn[s1.par[cur]]) cur=s1.par[cur];
			}
			d[i]=cnt;
		}
		LL ans=0;
		for (register int i=2;i<=s2.tot;i++) ans+=max(0,s2.maxn[i]-max(s2.maxn[s2.par[i]],d[s2.occ[i]]));
		printf("%lld\n",ans);
	}
	return 0;
}
