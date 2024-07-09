//I'll always miss you like a darling.
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
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

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

const int MAXN=1e5;

char s[MAXN+48],ss[MAXN*2+48],ans[MAXN*2+48];
int n,q;

int root[MAXN*2];

namespace SegmentTree
{
	int lson[MAXN*2*150+48],rson[MAXN*2*150+48],sum[MAXN*2*150+48],tot;
	inline void init() {tot=0;}
	inline int Create() {++tot;lson[tot]=rson[tot]=sum[tot]=0;return tot;}
	inline void pushup(int cur) {sum[cur]=sum[lson[cur]]+sum[rson[cur]];}
	inline void insert(int &cur,int pos,int l,int r)
	{
		if (!cur) cur=Create();
		if (l==r) {sum[cur]++;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) insert(lson[cur],pos,l,mid); else insert(rson[cur],pos,mid+1,r);
		pushup(cur);
	}
	inline int merge(int root1,int root2) //merge root2 to root1;
	{
		if (!root1 || !root2) return root1^root2;
		int rt=Create();
		lson[rt]=merge(lson[root1],lson[root2]);rson[rt]=merge(rson[root1],rson[root2]);
		pushup(rt);return rt;
	}
	inline int query(int cur,int left,int right,int l,int r)
	{
		if (left>right) return 0;
		if (!cur) return 0;
		if (left<=l && r<=right) return sum[cur];
		int mid=(l+r)>>1,res=0;
		if (left<=mid) res+=query(lson[cur],left,right,l,mid);
		if (mid+1<=right) res+=query(rson[cur],left,right,mid+1,r);
		return res;
	}
}

namespace SAM
{
	int nxt[MAXN*2][27],par[MAXN*2],maxn[MAXN*2],occ[MAXN*2],tot,last,Root;
	vector<int> v[MAXN*2];
	inline int Create() {++tot;memset(nxt[tot],0,sizeof(nxt[tot]));par[tot]=maxn[tot]=occ[tot]=0;return tot;}
	inline void init() {tot=0;last=Root=Create();}
	inline void extend(char ch,int ind)
	{
		int w=ch-'a'+1,p=last,np=Create();maxn[np]=maxn[p]+1;occ[np]=ind;last=np;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=Root;return;}
		int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;return;}
		int nq=Create();maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[np]=par[q]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
	}
	inline void dfs(int cur)
	{
		root[cur]=SegmentTree::Create();
		if (occ[cur]) SegmentTree::insert(root[cur],occ[cur],1,n);
		Rep(i,0,v[cur].size())
		{
			int y=v[cur][i];dfs(y);
			root[cur]=SegmentTree::merge(root[cur],root[y]);
		}	
	}
	inline void construct(char s[])
	{
		int len=strlen(s+1);init();
		rep(i,1,len) extend(s[i],i);
		rep(i,1,tot) v[i].clear();
		rep(i,2,tot) v[par[i]].pb(i);
		SegmentTree::init();dfs(Root);
	}
	inline Pair go(char s[],int l,int r)
	{
		int cur=Root,len=strlen(s+1);Pair res=mp(-1,-1);
		rep(i,0,len)
		{
			char ch=(i<len?s[i+1]:('a'-1));
			REP(j,26,ch-'a'+1+1)
				if (nxt[cur][j])
				{
					int to=nxt[cur][j];
					if (SegmentTree::query(root[to],l+i,r,1,n)) res=mp(i,j);
				}
			if (!nxt[cur][ch-'a'+1]) break;
			cur=nxt[cur][ch-'a'+1];
		}
		return res;
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%s",s+1);n=strlen(s+1);SAM::construct(s);
	Get(q);int l,r;
	while (q--)
	{
		Get(l,r);scanf("%s",ss+1);
		Pair res=SAM::go(ss,l,r);
		if (res.x==-1) puts("-1"); else
		{
			rep(i,1,res.x) ans[i]=ss[i];
			ans[res.x+1]='a'+res.y-1;ans[res.x+2]='\0';
			printf("%s\n",ans+1);
		}
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
