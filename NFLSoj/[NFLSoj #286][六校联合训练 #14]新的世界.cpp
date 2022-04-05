#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=500;

int n,m;
int a[MAXN+48][MAXN+48],L[MAXN+48][MAXN+48];

int sx,sy,ex,ey,l;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

priority_queue<pair<int,Pair> > q;

inline int calc(int x,int y)
{
	int maxn=max(0,a[x][y]);
	for (register int dir=0;dir<=3;dir++)
	{
		int xx=x+dx[dir],yy=y+dy[dir];
		if (1<=xx && xx<=n && 1<=yy && yy<=m) check_max(maxn,L[xx][yy]);
	}
	return maxn-a[x][y];
}

int main ()
{
	Get(n);Get(m);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			Get(a[i][j]);
	Get(sx);Get(sy);Get(l);Get(ex);Get(ey);
	L[sx][sy]=l;
	for (register int dir=0;dir<=3;dir++)
	{
		int xx=sx+dx[dir],yy=sy+dy[dir];
		if (1<=xx && xx<=n && 1<=yy && yy<=m && calc(xx,yy)!=L[xx][yy]) L[xx][yy]=calc(xx,yy),q.push(mp(calc(xx,yy),mp(xx,yy)));
	}
	while (!q.empty())
	{
		int x=q.top().y.x,y=q.top().y.y,dd=q.top().x;q.pop();
		if (dd<L[x][y]) continue;
		for (register int dir=0;dir<=3;dir++)
		{
			int xx=x+dx[dir],yy=y+dy[dir];
			if (1<=xx && xx<=n && 1<=yy && yy<=m && (!(xx==sx && yy==sy)) && calc(xx,yy)>L[xx][yy])
			{
				L[xx][yy]=calc(xx,yy);
				q.push(mp(L[xx][yy],mp(xx,yy)));
			}
		}
	}
	//print();
	printf("%d\n",L[ex][ey]);
	return 0;
}
