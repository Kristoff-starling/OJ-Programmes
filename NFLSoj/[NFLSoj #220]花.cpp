#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=1e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
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
template<typename T> inline T myabs(T x) {return (x>=0)?x:-x;}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=8e5;
const int base=201968;

int n;
int X[MAXN+48],Y[MAXN+48];

inline int getind1(int id) {return X[id]+Y[id]+base;}
inline int getind2(int id) {return X[id]-Y[id]+base;}

struct DSU
{
	int pre[MAXN+48],sz[MAXN+48];
	inline void init() {for (register int i=1;i<=MAXN;i++) pre[i]=i;memset(sz,0,sizeof(sz));}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline int Size(int x) {x=find_anc(x);return sz[x];}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (x==y) return;
		if (sz[x]>sz[y]) swap(x,y);
		pre[x]=y;sz[y]+=sz[x];
	}
}dsu1,dsu2,dsu3;

vector<int> v1[MAXN+48],v2[MAXN+48];

int seq[MAXN+48],pre[MAXN+48],nxt[MAXN+48],stot;

int minn;LL mincnt;
map<Pair,bool> Mp;

inline void update(int nv,LL ncnt,int id1,int id2)
{
	if (id1>id2) swap(id1,id2);
	if (nv<minn) minn=nv,mincnt=ncnt,Mp.clear(),Mp[mp(id1,id2)]=true;
	else if (nv==minn && Mp.find(mp(id1,id2))==Mp.end()) mincnt+=ncnt,Mp[mp(id1,id2)]=true;
}

int main ()
{
	Get(n);for (register int i=1;i<=n;i++) Get(X[i],Y[i]);
	for (register int i=1;i<=n;i++) v1[getind1(i)].pb(i),v2[getind2(i)].pb(i);
	dsu1.init();dsu2.init();dsu3.init();
	for (register int i=0;i<=base*2;i++) dsu1.sz[i]=int(v1[i].size()),dsu2.sz[i]=int(v2[i].size());
	for (register int i=1;i<=n;i++) dsu3.sz[i]=1;
	for (register int i=0;i<=base*2;i++)
		if (int(v2[i].size())>1)
			for (register int j=1;j<int(v2[i].size());j++) dsu1.update(getind1(v2[i][0]),getind1(v2[i][j]));
	for (register int i=0;i<=base*2;i++)
		if (int(v1[i].size())>1)
			for (register int j=1;j<int(v1[i].size());j++) dsu2.update(getind2(v1[i][0]),getind2(v1[i][j]));
	for (register int i=0;i<=base*2;i++)
	{
		if (int(v1[i].size())>1)
			for (register int j=1;j<int(v1[i].size());j++) dsu3.update(v1[i][0],v1[i][j]);
		if (int(v2[i].size())>1)
			for (register int j=1;j<int(v2[i].size());j++) dsu3.update(v2[i][0],v2[i][j]);
	}
	minn=INF;
	stot=0;for (register int i=0;i<=base*2;i++) if (int(v1[i].size())) seq[++stot]=i;
	for (register int i=1;i<=stot-1;i++)
		if (!dsu1.issame(seq[i],seq[i+1]))
			update(seq[i+1]-seq[i],1ll*dsu1.Size(seq[i])*dsu1.Size(seq[i+1]),dsu3.find_anc(v1[seq[i]][0]),dsu3.find_anc(v1[seq[i+1]][0]));
	stot=0;for (register int i=0;i<=base*2;i++) if (int(v2[i].size())) seq[++stot]=i;
	for (register int i=1;i<=stot-1;i++)
		if (!dsu2.issame(seq[i],seq[i+1]))
			update(seq[i+1]-seq[i],1ll*dsu2.Size(seq[i])*dsu2.Size(seq[i+1]),dsu3.find_anc(v2[seq[i]][0]),dsu3.find_anc(v2[seq[i+1]][0]));
	if (minn>=INF) {puts("-1");return 0;}
	printf("%d\n%lld\n",minn,mincnt);
	return 0;
}
