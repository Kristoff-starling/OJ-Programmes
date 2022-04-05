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
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int MOD=998244353;
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=5e5;

int n,e,q;

bool ans[MAXN+48];
vector<int> Q[MAXN+48],toq[MAXN+48];
bool visited[MAXN+48];vector<int> cur;
int pt[MAXN+48];

struct Edge
{
	int x,y,c,ind;
	inline void input() {Get(x);Get(y);Get(c);}
	inline bool operator < (const Edge &other) const {return c<other.c;}
}edge[MAXN+48],Edge[MAXN+48];

inline bool cmp(int id1,int id2) {return Edge[id1].c<Edge[id2].c;}

namespace DSU
{
	int pre[MAXN+48],rnk[MAXN+48];
	int sx[MAXN+48],sy[MAXN+48],ss[MAXN+48],stot;
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i,rnk[i]=1;stot=0;}
	inline int find_anc(int x) {while (pre[x]!=x) x=pre[x];return x;}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);if (rnk[x]>rnk[y]) swap(x,y);
		++stot;sx[stot]=x;sy[stot]=y;ss[stot]=rnk[y];
		pre[x]=y;rnk[y]+=rnk[x];
	}
	inline void undo()
	{
		assert(stot);
		int x=sx[stot],y=sy[stot],sz=ss[stot];stot--;
		rnk[y]=sz;pre[x]=x;
	}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
#endif
	Get(n);Get(e);int num,x;
	for (register int i=1;i<=e;i++) edge[i].input(),edge[i].ind=i,Edge[i]=edge[i];
	sort(edge+1,edge+e+1);Get(q);
	for (register int i=1;i<=q;i++)
	{
		Get(num);Q[i].clear();
		while (num--) Get(x),Q[i].pb(x),toq[x].pb(i);
		sort(Q[i].begin(),Q[i].end(),cmp);
	}
	DSU::init();memset(ans,true,sizeof(ans));
	memset(visited,false,sizeof(visited));
	memset(pt,0,sizeof(pt));cur.clear();
	for (register int l=1,r=1;l<=e;l=r+1,r=l)
	{
		for (;r<=e && edge[l].c==edge[r].c;r++);r--;
		for (register int i=l;i<=r;i++)
		{
			int id=edge[i].ind;
			for (auto item : toq[id]) if (!visited[item]) visited[item]=true,cur.pb(item);
		}
		for (auto id : cur)
		{
			if (!ans[id]) continue;
			while (Edge[Q[id][pt[id]]].c!=edge[l].c) pt[id]++;
			int ll=pt[id],rr=ll;
			while (rr<=int(Q[id].size())-1 && Edge[Q[id][ll]].c==Edge[Q[id][rr]].c) rr++;rr--;
			bool ff=true;int cnt=0;
			for (register int i=ll;i<=rr;i++)
			{
				int xx=Edge[Q[id][i]].x,yy=Edge[Q[id][i]].y;
				if (DSU::issame(xx,yy)) {ff=false;break;}
				cnt++;DSU::update(xx,yy);
			}
			if (!ff) ans[id]=false;
			while (cnt--) DSU::undo();
		}
		for (auto item : cur) visited[item]=false;cur.clear();
		for (register int i=l;i<=r;i++)
		{
			int xx=edge[i].x,yy=edge[i].y;
			if (!DSU::issame(xx,yy)) DSU::update(xx,yy);
		}
	}
	for (register int i=1;i<=q;i++) if (ans[i]) puts("YES"); else puts("NO");
	return 0;
}
