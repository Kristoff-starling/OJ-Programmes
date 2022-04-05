//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uing unsigned int
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

int n,m,sx,sy,ex,ey;
char Map[548][548];int val[548][548];
vector<Pair> v[548][548];vector<int> monster[548][548];

int s[548][548],d[548][548];

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

inline int getind(int x,int y) {return (x-1)*m+y;}
inline void getcor(int id,int &x,int &y) {x=id/m;if (id%m) x++;y=id-(x-1)*m;}

priority_queue<pair<Pair,int> > q;
bool inq[548][548];

inline void input()
{
	Get(n,m,sx,sy,ex,ey);
	rep(i,1,n) scanf("%s",Map[i]+1);
}

inline void Clear()
{
	rep(i,1,n) rep(j,1,m) monster[i][j].clear(),v[i][j].clear(),inq[i][j]=false;
}

inline int getsafe(int x1,int y1,int x2,int y2)
{
	int res=0;
	if (islower(Map[x2][y2])) res+=Map[x2][y2]-'a'+1;
	rep(i,0,int(monster[x2][y2].size())-1)
	{
		bool f=true;
		rep(j,0,int(monster[x1][y1].size())-1) if (monster[x1][y1][j]==monster[x2][y2][i]) {f=false;break;}
		if (f)
		{
			int xx,yy;getcor(monster[x2][y2][i],xx,yy);
			res+=Map[xx][yy]-'A'+1;
		}
	}
	return res;
}

inline void dijkstra()
{
	rep(i,1,n) rep(j,1,m) s[i][j]=d[i][j]=INF;
	s[sx][sy]=d[sx][sy]=0;inq[sx][sy]=true;
	q.push(mp(mp(0,0),getind(sx,sy)));
	while (!q.empty())
	{
		int id=q.top().y;q.pop();
		int cx,cy,tox,toy;getcor(id,cx,cy);
		inq[cx][cy]=false;
		rep(i,0,int(v[cx][cy].size())-1)
		{
			int tmp=v[cx][cy][i].x;getcor(tmp,tox,toy);
			int vs=getsafe(cx,cy,tox,toy);
			if (s[cx][cy]+vs<s[tox][toy] || (s[cx][cy]+vs==s[tox][toy] && d[cx][cy]+v[cx][cy][i].y<d[tox][toy]))
			{
				s[tox][toy]=s[cx][cy]+vs;
				d[tox][toy]=d[cx][cy]+v[cx][cy][i].y;
				if (!inq[tox][toy]) inq[tox][toy]=true,q.push(mp(mp(-s[tox][toy],-d[tox][toy]),getind(tox,toy)));
			}
		}
	}
}

inline void solve()
{
	rep(i,1,n) rep(j,1,m)
		if (Map[i][j]!='#' && !isupper(Map[i][j]))
		{
			rep(dir,0,3)
			{
				int x=i+dx[dir],y=j+dy[dir];
				if (1<=x && x<=n && 1<=y && y<=m && isupper(Map[x][y])) monster[i][j].pb(getind(x,y));
			}
		}
	rep(i,1,n) rep(j,1,m)
		if (Map[i][j]!='#' && !isupper(Map[i][j]))
		{
			rep(dir,0,3)
			{
				int x=i+dx[dir],y=j+dy[dir];
				if (1<=x && x<=n && 1<=y && y<=m && Map[x][y]!='#' && !isupper(Map[x][y])) v[i][j].pb(mp(getind(x,y),1));
			}
		}
	rep(i,1,n) rep(j,1,m)
		if (isupper(Map[i][j]))
		{
			vector<int> neighbor;neighbor.clear();
			rep(dir,0,3)
			{
				int x=i+dx[dir],y=j+dy[dir];
				if (1<=x && x<=n && 1<=y && y<=m && Map[x][y]!='#') neighbor.pb(getind(x,y));
			}
			rep(pt1,0,int(neighbor.size())-1) rep(pt2,0,int(neighbor.size())-1)
				if (pt1!=pt2)
				{
					int x1,y1;getcor(neighbor[pt1],x1,y1);
					v[x1][y1].pb(mp(neighbor[pt2],2));
				}
		}
	dijkstra();
	printf("%d %d\n",s[ex][ey],d[ex][ey]);
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
