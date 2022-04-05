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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=5e5;

char s[MAXN+48];int len;
char t[MAXN+48];

int Root[MAXN*2];
namespace SegmentTree
{
	int lson[MAXN*2*20+48],rson[MAXN*2*20+48],sum[MAXN*2*20+48],tot;
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
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
		int res=Create();lson[res]=merge(lson[root1],lson[root2]);rson[res]=merge(rson[root1],rson[root2]);
		pushup(res);return res;
	}
}

struct SAM
{
	int nxt[MAXN*2][27],occ[MAXN*2],par[MAXN*2],maxn[MAXN*2],root,last,tot;
	vector<int> v[MAXN*2];
	inline int Create() {++tot;memset(nxt[tot],0,sizeof(nxt[tot]));occ[tot]=0;par[tot]=0;maxn[tot]=0;return tot;}
	inline void init() {tot=0;root=last=Create();}
	inline void extend(char ch,int ind)
	{
		int p=last,np=Create(),w=ch-'a'+1;maxn[np]=maxn[p]+1;occ[np]=ind;
		while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
		if (!p) {par[np]=root;last=np;return;}
		int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
		int nq=Create();maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
		par[nq]=par[q];par[q]=par[np]=nq;
		while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
		last=np;
	}
	inline void construct(char s[])
	{
		init();int len=strlen(s+1);
		for (register int i=1;i<=len;i++) extend(s[i],i);
	}
	Pair ord[MAXN*2];
	inline void update()
	{
		for (register int i=1;i<=tot;i++) ord[i]=mp(maxn[i],i);
		sort(ord+1,ord+tot+1);
		for (register int i=tot;i>=2;i--)
		{
			int x=ord[i].y;
			if (occ[x]) occ[par[x]]=occ[x];
		}
	}
	inline void dfs(int cur)
	{
		for (auto y : v[cur]) dfs(y),Root[cur]=SegmentTree::merge(Root[cur],Root[y]);
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

int d[MAXN+48];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	SegmentTree::init();scanf("%s",s+1);len=strlen(s+1);s1.construct(s);s1.build();
	int q;scanf("%d",&q);int l,r,len2;
	while (q--)
	{
		scanf("%s%d%d",t+1,&l,&r);len2=strlen(t+1);
		s2.construct(t);s2.update();int cur=s1.root,cnt=0;
		for (register int i=1;i<=len2;i++)
		{
			int w=t[i]-'a'+1;
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
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}

