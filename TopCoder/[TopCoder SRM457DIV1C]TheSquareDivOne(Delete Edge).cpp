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
#define DEBUG(...) 
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
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

int n,num;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int D[1048];bool visited[1048];
int head[1048],nxt[100048],to[100048],f[100048],cost[100048],tot;
inline void addedge(int s,int t,int cap,int c)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=c;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-c;
}

struct TheSquareDivOne
{
	int R[48];bool taboo[48][48];
	inline int PairToInd(int x,int y) {return (x-1)*n+y;}
	struct ANS
	{
		int maxflow,mincost;
		vector<string> board;
	}ans,curans;
	inline void clear_edge()
	{
		tot=1;
		memset(head,0,sizeof(head));
		memset(D,0,sizeof(D));
	}
	inline int aug(int cur,int maxf)
	{
		if (cur==num) {curans.mincost+=maxf*(-D[0]);return maxf;}
		visited[cur]=true;int i,y,now,minf,ans=0;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (!visited[y] && f[i] && D[cur]+cost[i]-D[y]==0)
			{
				minf=min(maxf-ans,f[i]);
				now=aug(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
				if (ans>=maxf) return ans;
			}
		}
		return ans;
	}
	inline bool relabel()
	{
		int d=INF,i,cur,y;
		for (cur=0;cur<=num;cur++)
			if (visited[cur])
				for (i=head[cur];i;i=nxt[i])
				{
					y=to[i];
					if (!visited[y] && f[i]) d=min(d,D[cur]+cost[i]-D[y]);
				}
		if (d>=INF) return false;
		for (cur=0;cur<=num;cur++)
			if (visited[cur]) D[cur]-=d;
		return true;
	}
	vector<string> collect_board()
	{
		vector<string> res;string ins;
		int i,j,edge,cur,y;
		for (i=1;i<=n;i++)
		{
			ins="";
			for (j=1;j<=n;j++)
			{
				bool ff=false;cur=PairToInd(i,j);
				for (edge=head[cur];edge;edge=nxt[edge])
				{
					y=to[edge];
					if (n*n+1<=y && y<=n*n+n && !f[edge]) {ins+=string(1,'C');ff=true;break;}
				}
				if (!ff) ins+=string(1,'.');
			}
			res.pb(ins);
		}
		return res;
	}
	inline bool doit(vector<string> board,bool flag)
	{
		int i,j,dir,xx,yy,now;
		clear_edge();num=n*n+n+1;
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (board[i-1][j-1]=='C') addedge(0,PairToInd(i,j),1,0);
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				for (dir=0;dir<=3;dir++)
				{
					xx=i+dx[dir];yy=j+dy[dir];
					if (1<=xx && xx<=n && 1<=yy && yy<=n) addedge(PairToInd(i,j),PairToInd(xx,yy),INF,1);
				}
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (!taboo[i][j]) addedge(PairToInd(i,j),n*n+j,1,0);
		for (i=1;i<=n;i++) addedge(n*n+i,num,R[i],0);
		curans.maxflow=curans.mincost=0;
		do
			do
			{
				memset(visited,false,sizeof(visited));
				now=aug(0,INF);curans.maxflow+=now;
				if (!flag) DEBUG("%d\n",now);
			}
			while (now);
		while (relabel());
		if (!flag)
		{
			DEBUG("%d*\n",curans.maxflow);
			curans.board=collect_board();
			ans=curans;return true;
		}
		else
		{
			if (curans.maxflow==ans.maxflow && curans.mincost==ans.mincost)
			{
				curans.board=collect_board();ans=curans;
				return true;
			}
			else
				return false;
		}
	}
	vector<string> solve(vector<string> board)
	{
		n=int(board.size());int i,j;
		for (i=1;i<=n;i++)
		{
			R[i]=0;
			for (j=1;j<=n;j++)
				if (board[i-1][j-1]=='C') R[i]++;
		}
		memset(taboo,false,sizeof(taboo));
		doit(board,false);
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
			{
				taboo[i][j]=true;
				if (!doit(board,true)) taboo[i][j]=false;
			}
		return ans.board;
	}
};

/*---Debug Part---*/
/*
vector<string> v,ans;string s;
int main ()
{
	int nn,i,j;TheSquareDivOne A;
	while (scanf("%d",&nn)!=EOF)
	{
		v.clear();
		while (nn--)
		{
			cin>>s;
			v.pb(s);
		}
		ans=A.solve(v);
		for (i=0;i<int(ans.size());i++) cout<<ans[i]<<endl;
	}
	return 0;
}
*/
/*---Test BigInt---*/
/*
int main ()
{
	BigInt a,b;int x,y;
	x=getint();y=getint();
	a.len=b.len=0;a.type=b.type=true;
	while (x)
	{
		a.num[++a.len]=x%10;
		x/=10;
	}
	while (y)
	{
		b.num[++b.len]=y%10;
		y/=10;
	}
	BigInt c=a-b;
	if (!c.type) cout<<"-";
	for (int i=c.len;i>=1;i--) cout<<c.num[i];
	cout<<endl;
	return 0;
}
*/
