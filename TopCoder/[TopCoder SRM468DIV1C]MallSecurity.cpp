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

class MallSecurity
{
	int n,num[148],t,sum[148];
	struct Edge {int ind1,ind2,layer;}edge[10048],tmp[10048],ttmp[10048];int etot,ttot,tttot;
	bool bef[148],aft[148];
	int head[100048],to[200048],nxt[200048],f[200048],tot;
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	inline void clear()
	{
		etot=0;tot=1;t=0;
		memset(head,0,sizeof(head));
		memset(num,0,sizeof(num));memset(sum,0,sizeof(sum));
		ttot=tttot=0;
	}
	inline int STRING_TO_INT(string s)
	{
		int res=0,i;
		for (i=0;i<int(s.size());i++) res=res*10+s[i]-'0';
		return res;
	}
	inline void doit_single(string s)
	{
		int x,y,z,p1,p2;
		p1=s.find(' ');p2=s.find(' ',p1+1);
		x=STRING_TO_INT(s.substr(0,p1));
		y=STRING_TO_INT(s.substr(p1+1,p2-p1-1));
		z=STRING_TO_INT(s.substr(p2+1,int(s.size())-p2));
		edge[++etot]=Edge{x,y,z};
	}
	inline void doit_edge(vector<string> info)
	{
		string s="";int i;
		for (i=0;i<int(info.size());i++) s+=info[i];s+=",";
		int pos,pos1;
		for (pos=0;pos<=int(s.size())-1;pos=pos1+1)
		{
			pos1=s.find(',',pos);
			doit_single(s.substr(pos,pos1-pos));
		}
	}
	inline void Count()
	{
		int i;
		for (i=1;i<=etot;i++)
		{
			num[edge[i].layer]=max(num[edge[i].layer],edge[i].ind1);
			num[edge[i].layer%n+1]=max(num[edge[i].layer%n+1],edge[i].ind2);
		}
		for (i=1;i<=n;i++) t+=num[i],sum[i]=sum[i-1]+num[i];
		t++;
	}
	inline int getind(int layer,int ind)
	{
		return sum[layer-1]+ind;
	}
	inline void construct_edge()
	{
		int i,j,node1,node2;
		for (i=1;i<=etot;i++)
		{
			node1=getind(edge[i].layer,edge[i].ind1);node2=getind(edge[i].layer%n+1,edge[i].ind2);
			if (edge[i].layer%2==0) swap(node1,node2);
			addedge(node1,node2,INF);
		}
		for (i=1;i<=n;i++)
			for (j=1;j<=num[i];j++)
			{
				node1=getind(i,j);
				if (i%2==1) addedge(0,node1,1); else addedge(node1,t,1);
			}
	}
	int depth[100048];queue<int> q;
	inline bool bfs()
	{
		int i,x,y;
		for (i=0;i<=t;i++) depth[i]=-1;
		depth[0]=0;q.push(0);
		while (!q.empty())
		{
			x=q.front();q.pop();
			for (i=head[x];i;i=nxt[i])
			{
				y=to[i];
				if (depth[y]==-1 && f[i])
				{
					depth[y]=depth[x]+1;
					q.push(y);
				}
			}
		}
		if (depth[t]==-1) return false; else return true;
	}
	inline int dfs(int x,int maxf)
	{
		if (x==t || !maxf) return maxf;
		int i,y,now,minf,ans=0;
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
			if (ans>=maxf) return ans;
		}
		if (!ans) depth[x]=0;
		return ans;
	}
	inline bool judge(int cur,int gap)
	{
		if (cur<gap) return cur%2==1; else return cur%2==0;
	}
	public:
		inline int maxGuards(int N,vector<string> escDescription)
		{
			n=N;clear();
			doit_edge(escDescription);
			Count();
			if (N%2==0)
			{
				construct_edge();
				int ans=0;
				while (bfs()) ans+=dfs(0,2e9);
				return sum[n]-ans;
			}
			else
			{
				int minn=INF,minpos,Mask,i,j;
				for (i=1;i<=n;i++)
					if (num[i]<minn) minn=num[i],minpos=i;
				for (i=1;i<=etot;i++)
					if (edge[i].layer==minpos || edge[i].layer==(minpos-1==0?n:minpos-1))
						tmp[++ttot]=edge[i];
					else
						ttmp[++tttot]=edge[i];
				etot=tttot;
				for (i=1;i<=etot;i++) edge[i]=ttmp[i];
				int res=0,curans;
				for (Mask=0;Mask<=(1<<minn)-1;Mask++)
				{
					tot=1;for (i=0;i<=t;i++) head[i]=0;
					memset(bef,true,sizeof(bef));memset(aft,true,sizeof(aft));
					curans=__builtin_popcount(Mask);
					for (i=1;i<=ttot;i++)
						if (tmp[i].layer==minpos)
						{
							if (Mask&(1<<(tmp[i].ind1-1))) aft[tmp[i].ind2]=false;
						}
						else
						{
							if (Mask&(1<<(tmp[i].ind2-1))) bef[tmp[i].ind1]=false;
						}
					for (i=1;i<=etot;i++)
					{
						int node1=getind(edge[i].layer,edge[i].ind1),node2=getind(edge[i].layer%n+1,edge[i].ind2);
						if (!judge(edge[i].layer,minpos)) swap(node1,node2);
						addedge(node1,node2,INF);
					}
					for (i=1;i<=n;i++)
					{
						if (i==minpos) continue;
						for (j=1;j<=num[i];j++)
						{
							if (i==minpos%n+1 && !aft[j]) continue;
							if (i==(minpos-1==0?n:minpos-1) && !bef[j]) continue;
							int nde=getind(i,j);curans++;
							if (judge(i,minpos)) addedge(0,nde,1); else addedge(nde,t,1);
						}
					}
					while (bfs()) curans-=dfs(0,2e9);
					res=max(res,curans);
				}
				return res;
			}
		}
};

/*---Debug Part---*/
/*
int main ()
{
	MallSecurity A;int nn;vector<string> ss;
	while (scanf("%d",&nn)!=EOF)
	{
		int mm;mm=getint();string s;ss.clear();
		while (mm--)
		{
			getline(cin,s);
			ss.pb(s);
		}
		printf("%d\n",A.maxGuards(nn,ss));
	}
	return 0;
}
*/
/*
10
2
1 1 1,1 1 2,1 1 3,1 1 4,1 1 5,1 1 6,1 1 7,1 1 8,1 
1 9,1 1 10
10 9
1 1 7,1 2 9,2 1
 8,1 2 6,1 1 8,1 2 3,1 2 2,2 
2 4,1 1 1,2 1 2,3 2 3,1 1 5,2 1 1,4 
1 7,1 1 10,3 2 5,1 2 5,3 3 1,
3 2 8,3 1 2,1 1 3,4 4 2,2
 4 6,4 2 5,2 3 3,6 4 1,5 2 8,1 3 6,1 3 7,
4 3 8,1 3 8,5 2 3,4 2 8,2 6 7,1 3 9,
1 1 4,6 1 1,2 3 1,5 1 5,6 1 8,5 
2 2,3 2 10,3 3 9,1 5 2,4 1 1,1 5 10
*/
