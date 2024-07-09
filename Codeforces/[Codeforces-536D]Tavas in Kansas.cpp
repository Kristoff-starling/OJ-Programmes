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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=2000;
const int MAXM=1e5;

int n,e,s,t;
int p[MAXN+48];
vector<Pair> v[MAXN+48];
LL da[MAXN+48],db[MAXN+48],val[MAXN+48];int tot,N,M;
LL dp[MAXN+48][MAXN+48][2];

priority_queue<pLL> q;
inline void dijkstra(int st,LL dist[],int &lim)
{
	for (register int i=1;i<=n;i++) dist[i]=LINF;
	dist[st]=0;q.push(mp(0,st));
	while (!q.empty())
	{
		LL dd=-q.top().x;int cur=q.top().y;q.pop();
		if (dist[cur]<dd) continue;
		for (auto item : v[cur])
		{
			int to=item.x;
			if (dist[cur]+item.y<dist[to])
			{
				dist[to]=dist[cur]+item.y;
				q.push(mp(-dist[to],to));
			}
		}
	}
	for (register int i=1;i<=n;i++) val[i]=dist[i];tot=n;
	sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
	for (register int i=1;i<=n;i++) dist[i]=lower_bound(val+1,val+tot+1,dist[i])-val;
	lim=tot;
}

struct Pt
{
	int x,y,val,ind;
	Pt () {}
	inline Pt (int _x,int _y,int _v,int _i) {x=_x;y=_y;val=_v;ind=_i;}
}a[MAXN+48],tmp[MAXN+48];int to;

inline bool cmp_x(Pt x,Pt y) {return x.x<y.x;}
inline bool cmp_y(Pt x,Pt y) {return x.y<y.y;}

pair<int,LL> player[2][MAXN+48][MAXN+48];

inline void update(int &pos,LL &sum,int npos,int val)
{
	if (pos==npos) {sum+=val;return;}
	pos=npos;sum=val;
}

inline void init()
{
	for (register int i=1;i<=n;i++) a[i]=Pt(da[i],db[i],p[i],i);
	int pos,k;LL sum;
	for (register int i=M;i>=0;i--)
	{
		to=0;
		for (register int j=1;j<=n;j++) if (a[j].y>i) tmp[++to]=a[j];
		sort(tmp+1,tmp+to+1,cmp_x);pos=INF;sum=0;k=to;
		for (register int j=N;j>=0;j--)
		{
			while (k && tmp[k].x>j) update(pos,sum,tmp[k].x,tmp[k].val),k--;
			player[0][j][i]=mp(pos,sum);
		}
	}
	for (register int i=N;i>=0;i--)
	{
		to=0;
		for (register int j=1;j<=n;j++) if (a[j].x>i) tmp[++to]=a[j];
		sort(tmp+1,tmp+to+1,cmp_y);pos=INF;sum=0;k=to;
		for (register int j=M;j>=0;j--)
		{
			while (k && tmp[k].y>j) update(pos,sum,tmp[k].y,tmp[k].val),k--;
			player[1][i][j]=mp(pos,sum);
		}
	}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
#endif
	Get(n);Get(e);Get(s);Get(t);int x,y,c;
	for (register int i=1;i<=n;i++) Get(p[i]);
	for (register int i=1;i<=e;i++)
	{
		Get(x);Get(y);Get(c);
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	dijkstra(s,da,N);dijkstra(t,db,M);init();
	for (register int i=N;i>=0;i--)
		for (register int j=M;j>=0;j--)
		{
			if (player[0][i][j].x>=INF) {dp[i][j][0]=dp[i][j][1]=0;continue;}
			dp[i][j][0]=max(dp[player[0][i][j].x][j][0]+player[0][i][j].y,dp[player[0][i][j].x][j][1]+player[0][i][j].y);
			dp[i][j][1]=min(dp[i][player[1][i][j].x][0]-player[1][i][j].y,dp[i][player[1][i][j].x][1]-player[1][i][j].y);
		}
	LL res=dp[0][0][0];
	if (res>0) puts("Break a heart");
	else if (res==0) puts("Flowers");
	else puts("Cry");
	return 0;
}
