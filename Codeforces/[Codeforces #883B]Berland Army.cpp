#include <bits/stdc++.h>
#include <tr1/unordered_map>
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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=2e5;

int n,m,k;
vector<int> v[MAXN+48],vv[MAXN+48];
int L[MAXN+48],R[MAXN+48];
int val[MAXN+48];
int seq[MAXN+48];priority_queue<Pair> q;

inline bool cmp(int x,int y) {return R[x]>R[y];}

struct node
{
	int val,from;
	node () {}
	inline node(int vv,int ff) {val=vv;from=ff;}
	inline bool operator < (const node &x) const {return val<x.val;}
}a[MAXN+48];int tot;

bool superf=true;

inline int solve1(int cur)
{
	if (L[cur]) return L[cur];
	int maxn=0;
	for (register int i=0;i<int(v[cur].size());i++) maxn=max(maxn,solve1(v[cur][i]));
	if (val[cur])
	{
		if (maxn+1>val[cur]) superf=false;
		return L[cur]=val[cur];
	}
	return L[cur]=maxn+1;
}

inline int solve2(int cur)
{
	if (R[cur]) return R[cur];
	int minn=k+1;
	for (register int i=0;i<int(vv[cur].size());i++) minn=min(minn,solve2(vv[cur][i]));
	if (val[cur])
	{
		if (minn-1<val[cur]) superf=false;
		return R[cur]=val[cur];
	}
	return R[cur]=minn-1;
}

int d[MAXN+48];queue<int> qq;
inline bool check_cycle()
{
	int cnt=0,i,cur;
	for (i=1;i<=n;i++) if (!d[i]) qq.push(i);
	while (!qq.empty())
	{
		cur=qq.front();qq.pop();cnt++;
		for (i=0;i<int(v[cur].size());i++)
		{
			d[v[cur][i]]--;
			if (!d[v[cur][i]]) qq.push(v[cur][i]);
		}
	}
	return cnt<n;
}

int main ()
{
	int i,x,y;
	n=getint();m=getint();k=getint();
	for (i=1;i<=n;i++) val[i]=getint();
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);vv[y].pb(x);d[y]++;
	}
	if (check_cycle()) {puts("-1");return 0;}
	superf=true;
	for (i=1;i<=n;i++) L[i]=solve1(i);
	for (i=1;i<=n;i++) R[i]=solve2(i);
	if (!superf) {puts("-1");return 0;}
	for (i=1;i<=n;i++) seq[i]=i;sort(seq+1,seq+n+1,cmp);
	int pt=1;
	for (i=1;i<=n;i++) if (L[i]>k) {puts("-1");return 0;}
	for (i=k;i>=1;i--)
	{
		while (pt<=n && R[seq[pt]]==i) q.push(mp(L[seq[pt]],seq[pt])),pt++;
		if (q.empty()) {puts("-1");return 0;}
		int cur=q.top().y;q.pop();val[cur]=i;
		while (!q.empty() && q.top().x==i) val[q.top().y]=i,q.pop();
	}
	for (i=1;i<=n;i++) printf("%d ",val[i]);
	puts("");return 0;
} 
