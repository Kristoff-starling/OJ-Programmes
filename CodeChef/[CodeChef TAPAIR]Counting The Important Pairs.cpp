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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get (T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
template<typename T> inline T myabs(T x) {return (x>0)?x:-x;}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline void Add(T x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T x,T y) {x=sub(x-y);}

const int MAXN=3e5;

int n,m;

Pair edge[MAXN+48];
vector<int> v[MAXN+48];

inline int getanother(int ind,int x) {if (edge[ind].x==x) return edge[ind].y; else return edge[ind].x;}

map<vector<LL>,int> Mp;
LL mark[MAXN+48][15],xsum[MAXN+48][15];bool intree[MAXN+48];int depth[MAXN+48];
vector<LL> fv[MAXN+48];
map<vector<LL>,int> Mp2;

inline LL gen_rand()
{
	return ((1ll*rand())<<20)+((1ll*rand())<<10)+rand();
}

inline void dfs(int cur,int father)
{
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=getanother(v[cur][i],cur);
		if (!depth[y]) depth[y]=depth[cur]+1,intree[v[cur][i]]=true,dfs(y,cur);
		else if (y!=father && depth[y]<depth[cur])
		{
			vector<LL> tmp;tmp.clear();
			for (register int k=0;k<=9;k++)
			{
				LL val=gen_rand();tmp.pb(val);
				mark[cur][k]^=val;mark[y][k]^=val;
			}
			Mp[tmp]=1;
		}
	}
}

inline void Dfs(int cur,int father)
{
	memcpy(xsum[cur],mark[cur],sizeof(mark[cur]));
	for (register int i=0;i<int(v[cur].size());i++)
		if (intree[v[cur][i]])
		{
			int y=getanother(v[cur][i],cur);
			if (y!=father)
			{
				Dfs(y,cur);
				for (register int k=0;k<=9;k++) xsum[cur][k]^=xsum[y][k];
			}
		}
}

int main ()
{
#ifdef LOCAL
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	srand(time(NULL));
	Get(n);Get(m);int x,y;
	for (register int i=1;i<=m;i++)
	{
		Get(x);Get(y);edge[i]=mp(x,y);
		v[x].pb(i);v[y].pb(i);
	}
	depth[1]=1;dfs(1,-1);Dfs(1,-1);int cnt=0;LL ans=0;
	for (register int i=2;i<=n;i++)
	{
		fv[i].clear();bool f=true;
		for (register int j=0;j<=9;j++) {fv[i].pb(xsum[i][j]);if (xsum[i][j]) f=false;}
		if (f) cnt++;
		if (Mp.find(fv[i])!=Mp.end()) ans++;
		Mp2[fv[i]]++;
	}
	ans+=1ll*cnt*(m-cnt);
	for (map<vector<LL>,int>::iterator iter=Mp2.begin();iter!=Mp2.end();iter++)
		ans+=1ll*(iter->y)*(iter->y-1)/2;
	printf("%lld\n",ans);
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
