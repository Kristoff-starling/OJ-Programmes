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

const int MOD=1e9+9;
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

int n,e;
Pair edge[10048];
vector<Pair> v[10048];
struct Edge
{
	int x,y;
	int ind;
};vector<Edge> tedge,ntedge;
bool istree[10048];
int L[10048],R[10048];
int a[10048],pos[10048],ind;
bool visited[10048];int depth[10048];
int sum1[10048],sum2[10048];
bool col[10048];
int node[10048],tot=0;
vector<int> ans;int ansnum;
bool ins[10048];

void dfs(int cur)
{
	node[++tot]=cur;
	visited[cur]=true;
	a[++ind]=cur;pos[cur]=ind;
	L[cur]=ind;
	int i,to;
	for (i=0;i<int(v[cur].size());i++)
	{
		to=v[cur][i].x;
		if (!visited[to])
		{
			istree[v[cur][i].y]=true;
			depth[to]=depth[cur]+1;
			col[to]=col[cur]^1;
			dfs(to);
		}
	}
	R[cur]=ind;
}

int main ()
{
	int i,j,k,x,y;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		edge[i]=mp(x,y);
		v[x].pb(mp(y,i));v[y].pb(mp(x,i));
	}
	memset(visited,false,sizeof(visited));
	int all_cnt=0,cnt;
	bool hasbaned=false;
	ansnum=0;
	for (i=1;i<=n;i++)
		if (!visited[i])
		{
			cnt=0;
			depth[i]=1;col[i]=false;
			ind=0;tot=0;
			dfs(i);
			//for (i=1;i<=n;i++) cout<<visited[i]<<' ';
			//cout<<endl;
			bool f=false;
			for (j=1;j<=tot;j++)
				for (k=0;k<int(v[node[j]].size());k++)
				{
					int eind=v[node[j]][k].y;
					if (depth[edge[eind].x]>depth[edge[eind].y]) swap(edge[eind].x,edge[eind].y);
					if (!ins[eind])
					{
						ins[eind]=true;
						if (!istree[eind])
						{
							ntedge.pb(Edge{edge[eind].x,edge[eind].y,eind});
							if (col[edge[eind].x]^col[edge[eind].y])
							{
								sum1[pos[edge[eind].x]]--;
								sum1[pos[edge[eind].y]]++;
							}
							else
							{
								hasbaned=true;f=true;cnt++;
								sum2[pos[edge[eind].x]]--;
								sum2[pos[edge[eind].y]]++;
							}
						}
						else
							tedge.pb(Edge{edge[eind].x,edge[eind].y,eind});
					}
				}
			if (f) all_cnt++;
			if (!cnt) continue;
			if (cnt==1)
			{
				ansnum=1;
				for (j=0;j<int(ntedge.size());j++)
					if (!(col[ntedge[j].x]^col[ntedge[j].y]))
					{
						ans.pb(ntedge[j].ind);
						break;
					}
			}
			for (j=1;j<=tot;j++) sum1[j]+=sum1[j-1],sum2[j]+=sum2[j-1];
			for (j=0;j<int(tedge.size());j++)
				if (sum2[R[tedge[j].y]]-sum2[L[tedge[j].y]-1]==cnt && sum1[R[tedge[j].y]]-sum1[L[tedge[j].y]-1]==0)
				{
					ansnum++;
					ans.pb(tedge[j].ind);
				}
			for (i=1;i<=tot;i++) sum1[i]=sum2[i]=0;
		}
	if (all_cnt>1)
	{
		printf("0\n");
		return 0;
	}
	if (!hasbaned)
	{
		printf("%d\n",e);
		for (i=1;i<=e;i++) printf("%d ",i);
		printf("\n");
		return 0;
	}
	printf("%d\n",ansnum);
	if (ansnum)
	{
		sort(ans.begin(),ans.end());
		for (j=0;j<int(ans.size());j++)
			printf("%d ",ans[j]);
	}
	return 0;
}
/*
7 10
1 2
1 3
2 3
1 4
2 4
1 5
2 5
6 7
7 8
8 6
*/