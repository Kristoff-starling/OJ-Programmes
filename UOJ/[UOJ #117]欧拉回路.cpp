//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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
template<typename T> inline T myabs(T x) {if (x<0) x=-x;return x;}

const int MAXN=2e5;

namespace type1
{
	int n,m;
	int head[MAXN+48],cur[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],ind[MAXN*2+48],tot;
	int deg[MAXN+48];bool visited[MAXN*2+48],exist[MAXN+48];
	int seq[MAXN*2+48],stot;
	inline void addedge(int s,int t,int id)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;ind[tot]=id;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;ind[tot]=-id;
		deg[s]++;deg[t]++;exist[s]=true;exist[t]=true;
	}
	inline void dfs(int x)
	{
		for (register int &i=cur[x];i;i=nxt[i])
		{
			if (visited[myabs(ind[i])]) continue;
			int tmp=ind[i];visited[myabs(tmp)]=true;dfs(to[i]);seq[++stot]=tmp;
		}
	}
	inline void solve()
	{
		Get(n,m);int x,y;tot=0;
		if (!m) {puts("YES");return;}
		rep(i,1,m) Get(x,y),addedge(x,y,i);
		memcpy(cur+1,head+1,n<<2);
		rep(i,1,n) if (deg[i]&1) {puts("NO");return;}
		int st=1;while (!exist[st]) st++;
		stot=0;dfs(st);
		if (stot!=m) puts("NO");
		else
		{
			puts("YES");
			rep(i,1,stot) printf("%d ",-seq[i]);puts("");
		}
	}
}

namespace type2
{
	int n,m;
	int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],ind[MAXN+48],tot=0;
	int deg[MAXN+48],seq[MAXN+48],stot;bool visited[MAXN+48];
	bool exist[MAXN+48];
	inline void addedge(int s,int t,int id)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;ind[tot]=id;
		deg[s]--;deg[t]++;exist[s]=true;exist[t]=true;
	}
	inline void dfs(int x)
	{
		for (register int &i=cur[x];i;i=nxt[i])
		{
			if (visited[ind[i]]) continue;
			int tmp=ind[i];visited[tmp]=true;dfs(to[i]),seq[++stot]=tmp;
		}
	}
	inline void solve()
	{
		Get(n,m);int x,y;
		if (!m) {puts("YES");return;}
		rep(i,1,m) Get(x,y),addedge(x,y,i);
		memcpy(cur+1,head+1,n<<2);
		rep(i,1,n) if (deg[i]) {puts("NO");return;}
		int st=1;while (!exist[st]) st++;
		stot=0;dfs(st);
		if (stot!=m) puts("NO");
		else
		{
			puts("YES");
			REP(i,stot,1) printf("%d ",seq[i]);puts("");
		}
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
	int type;Get(type);
	if (type==1) type1::solve(); else type2::solve();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
