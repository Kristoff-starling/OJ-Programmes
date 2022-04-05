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
int n,e,ans=0;
bool visited[148];int incircle[148],cirind;int fa[148];
int head[1048],nxt[2048],to[2048],tot,cs;
int cirlist[1048],ctot=0;int flow[148][148];
int dp[58][100048];

class SpaceshipEvacuation
{
	public:
		inline void addedge(int s,int t)
		{
			to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
		}
		inline void clear()
		{
			tot=1;ans=0;
			memset(visited,false,sizeof(visited));memset(incircle,0,sizeof(incircle));cirind=0;
			memset(head,0,sizeof(head));
		}
		inline int STRING_TO_INT(string s)
		{
			int res=0,len=int(s.size()),i;
			for (i=0;i<=len-1;i++) res=res*10+s[i]-'0';
			return res;
		}
		inline void doit_tunnel(string s)
		{
			int a[10];s+=" ";int i,pos,pos1,len=int(s.size())-1;
			for (i=1,pos=0;i<=4 && pos<=len-1;pos=pos1+1,i++)
			{
				pos1=s.find(' ',pos);
				a[i]=STRING_TO_INT(s.substr(pos,pos1-pos));
			}
			a[1]++;a[2]++;
			if (a[1]==a[2]) return;
			addedge(a[1],a[2]);addedge(a[2],a[1]);
			flow[a[1]][a[2]]=a[3];flow[a[2]][a[1]]=a[4];
		}
		inline void doit_circle(int but,int top,int curind)
		{
			int i,j,cur,ctot=0,tmp=0;
			for (cur=but;cur!=top;cur=fa[cur])
			{
				cirlist[++ctot]=cur;
				incircle[cur]=curind;
			}
			cirlist[++ctot]=cur;incircle[cur]=curind;
			reverse(cirlist+1,cirlist+ctot+1);
			cirlist[ctot+1]=cirlist[1];
			for (i=1;i<=ctot;i++)
				for (j=0;j<=cs;j++)
					dp[i][j]=(i==1?0:INF);
			for (i=2;i<=ctot;i++)
			{
				tmp=INF;
				for (j=0;j<=cs;j++)
				{
					tmp=min(tmp,dp[i-1][j]);
					dp[i][j]=min(dp[i][j],tmp+max(0,j-flow[cirlist[i]][cirlist[i+1]])+max(0,cs-j-flow[cirlist[i]][cirlist[i-1]]));
				}
			}
			tmp=INF;
			for (i=0;i<=cs;i++) tmp=min(tmp,dp[ctot][i]);
			ans+=tmp;
		}	
		inline void dfs(int cur,int father)
		{
			int i,y;
			visited[cur]=true;fa[cur]=father;
			for (i=head[cur];i;i=nxt[i])
			{
				y=to[i];
				if (y!=father)
					if (visited[y]) {if (!incircle[cur]) doit_circle(cur,y,++cirind);} else dfs(y,cur);
			}
			if (father && !(incircle[father] && incircle[cur] && incircle[cur]==incircle[father])) ans+=max(0,cs-flow[cur][father]);
		}
		inline int additionalCabins(int N,vector<string> tunnelNetwork,int crewSize)
		{
			n=N;e=int(tunnelNetwork.size());clear();cs=crewSize;int i;
			for (i=0;i<=e-1;i++) doit_tunnel(tunnelNetwork[i]);
			fa[1]=0;dfs(1,0);
			for (i=1;i<=n;i++) if (!visited[i]) return -1;
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,ee,cc;
	SpaceshipEvacuation A;
	while (scanf("%d%d%d",&nn,&ee,&cc)!=EOF)
	{
		int i;vector<string> v;string s;getchar();
		for (i=1;i<=ee;i++)
		{
			getline(cin,s);
			v.pb(s);
		}
		cout<<A.additionalCabins(nn,v,cc)<<endl;
	}
	return 0;
}
*/
/*
3 2 5
0 1 5 3
2 1 0 0

4 4 6
0 1 0 6
3 2 3 1
2 1 0 1
3 1 2 2
*/

