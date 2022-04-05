#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
bool visited[148][148];

class ColorfulMaze
{
	char s[148][148];int n,m,cnum,sx,sy,ex,ey;
	double p[48];
	bool reachable[48][48];
	inline bool check_valid(int x,int y,int col)
	{
		if (s[x][y]=='#') return false;
		if (s[x][y]=='!') return false;
		if (isupper(s[x][y]) && s[x][y]-'A'+1==col) return false;
		return true;
	}
	inline bool dfs(int x,int y,int col1,int col2)
	{
		visited[x][y]=true;
		if (isupper(s[x][y]) && s[x][y]-'A'+1==col1) return true;
		int i,dir,tox,toy;
		for (dir=0;dir<=3;dir++)
		{
			tox=x+dx[dir];toy=y+dy[dir];
			if (1<=tox && tox<=n && 1<=toy && toy<=m && !visited[tox][toy] && check_valid(tox,toy,col2))
			{
				bool res=dfs(tox,toy,col1,col2);
				if (res) return true;
			}
		}
		return false;
	}
	inline bool check_Mask(int dind,int Mask)
	{
		if (!(Mask&(1<<(dind-1))) && dind<=cnum) return false;
		int i,j;
		for (i=1;i<=cnum;i++)
			if (Mask&(1<<(i-1)))
				for (j=1;j<=cnum;j++)
					if (!(Mask&(1<<(i-1))) && !reachable[j][i]) return false;
		return true;
	}
	inline double calc_Mask(int dind,int Mask)
	{
		double res=1;int i;
		if (dind<=cnum) res*=p[dind];
		for (i=1;i<=cnum;i++) if (Mask&(1<<(i-1)) && i!=dind) res*=(1.0-p[i]);
		return res;
	}
	inline double calc_pro(int x,int y,int Mask)
	{
		if (!isupper(s[x][y])) return 1;
		int ind=s[x][y]-'A'+1;
		if (Mask&(1<<(ind-1))) return 1; else return 1-p[ind];
	}
	double dist[58][58];
	typedef pair<double,Pair> pp;
	priority_queue<pp> q;
	inline void dijkstra(int dind,int Mask)
	{
		int i,j,dir,x,y,xx,yy;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				dist[i][j]=0;
		dist[sx][sy]=1;
		q.push(mp(1,mp(sx,sy)));
		memset(visited,false,sizeof(visited));
		while (!q.empty())
		{
			double curd=q.top().x;x=q.top().y.x;y=q.top().y.y;q.pop();
			if (curd<dist[x][y]) continue;
			visited[x][y]=true;
			for (dir=0;dir<=3;dir++)
			{
				xx=x+dx[dir];yy=y+dy[dir];
				if (1<=xx && xx<=n && 1<=yy && yy<=m && s[xx][yy]!='#' && s[xx][yy]-'A'+1!=dind && !visited[xx][yy])
				{
					double mul=calc_pro(xx,yy,Mask);
					if (dist[x][y]*mul>dist[xx][yy])
					{
						dist[xx][yy]=dist[x][y]*mul;
						q.push(mp(dist[xx][yy],mp(xx,yy)));
					}
				}
			}
		}
	}
	public:
		inline double getProbability(vector<string> maze,vector<int> trap)
		{
			n=int(maze.size());m=int(maze[0].size());int i,j,Mask;
			for (i=1;i<=n;i++)
				for (j=1;j<=m;j++)
				{
					s[i][j]=maze[i-1][j-1];
					if (s[i][j]=='$') sx=i,sy=j;
					if (s[i][j]=='!') ex=i,ey=j;
				}
			for (i=1;i<=7;i++) p[i]=trap[i-1]*1.0/100;
			cnum=7;while (p[cnum]<eps) cnum--;
			for (i=1;i<=cnum;i++)
				for (j=1;j<=cnum;j++)
					if (i!=j)
					{
						memset(visited,false,sizeof(visited));
						reachable[i][j]=dfs(sx,sy,i,j);
					}
			double ans=0;
			for (i=1;i<=cnum;i++)
				for (Mask=0;Mask<=(1<<cnum)-1;Mask++)
					if (check_Mask(i,Mask))
					{
						cout<<i<<' '<<Mask<<endl;
						dijkstra(i,Mask);
						double curans=calc_Mask(i,Mask)*dist[ex][ey];
						cout<<calc_Mask(i,Mask)<<endl;
						ans+=curans;
					}
			return ans;
		}
};

/*---Debug Part---*/
int main ()
{
	ColorfulMaze A;
	int nn;string ss;int xx,i;
	while (scanf("%d",&nn)!=EOF)
	{
		vector<string> vv;vector<int> nu;
		for (i=1;i<=nn;i++)
		{
			cin>>ss;
			vv.pb(ss);
		}
		for (i=1;i<=7;i++) xx=getint(),nu.pb(xx);
		cout<<A.getProbability(vv,nu)<<endl;
	}
	return 0;
}
