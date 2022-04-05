#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <sstream>
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

const int MOD=1e9+3;
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

string hsh[4848],h[4848];
LL cnt[4848];

class CactusAutomorphisms
{
	int head[4848],nxt[4848],to[4848],tot=1;
	inline void addedge(int s,int t)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
	}
	bool visited[4848];
	int cnum=0,cirnum[4848],fa[4848],depth[4848];
	inline void dfs(int cur,int father)
	{
		int i,j,y;fa[cur]=father;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (!depth[y]) depth[y]=depth[cur]+1,dfs(y,cur);
			else if (y!=father && depth[y]<depth[cur])
			{
				++cnum;
				for (j=cur;;j=fa[j]) {cirnum[j]=cnum;if (j==y) break;}
			}
		}		
	}
	inline void solve(int cur)
	{
		visited[cur]=true;cnt[cur]=1;
		if (!cirnum[cur])
		{
			map<string,LL> table;table.clear();
			int i,y;
			for (i=head[cur];i;i=nxt[i])
			{
				y=to[i];
				if (!visited[y])
				{
					solve(y);
					table[h[y]]++;
					cnt[cur]=(cnt[cur]*table[h[y]])%MOD;cnt[cur]=(cnt[cur]*cnt[y])%MOD;
				}
			}
			map<string,LL>::iterator iter;
			h[cur]="";
			for (iter=table.begin();iter!=table.end();iter++)
				for (i=1;i<=iter->y;i++)
					h[cur]+="0"+iter->x+"1";
		}
		else
		{
			vector<int> cirlist;cirlist.clear();int cc=cur;cirlist.pb(cc);
			int i,y,pt;
			do
			{
				bool f=false;
				for (i=head[cc];i;i=nxt[i])
				{
					y=to[i];
					if (cirnum[y]==cirnum[cur] && !visited[y])
					{
						cc=y;cirlist.pb(cc);
						visited[cc]=true;f=true;break;
					}
				}
				if (!f) break;
			}
			while (true);
			vector<string> Cir;Cir.clear();
			for (pt=0;pt<int(cirlist.size());pt++)
			{
				map<string,LL> table;table.clear();
				for (i=head[cirlist[pt]];i;i=nxt[i])
				{
					y=to[i];
					if (!visited[y])
					{
						solve(y);
						table[h[y]]++;
						cnt[cur]=(cnt[cur]*table[h[y]])%MOD;cnt[cur]=(cnt[cur]*cnt[y])%MOD;
					}
				}
				string ins="";
				map<string,LL>::iterator iter;
				for (iter=table.begin();iter!=table.end();iter++)
					for (i=1;i<=iter->y;i++)
						ins+="0"+iter->x+"1";
				Cir.pb(ins);
			}
			string tmp1="",tmp2="";
			for (i=0;i<int(Cir.size());i++) tmp1=tmp1+Cir[i]+"2";
			tmp2=Cir[0]+"2";
			for (i=int(Cir.size())-1;i>=1;i--) tmp2=tmp2+Cir[i]+"2";
			if (tmp1==tmp2) cnt[cur]=(cnt[cur]*2)%MOD;
			if (tmp1<tmp2) h[cur]=tmp1; else h[cur]=tmp2;
		}
	}
	inline void Clear()
	{
		tot=1;cnum=0;
		memset(head,0,sizeof(head));
		memset(depth,0,sizeof(depth));
	}
	public:
		inline int count(int n,vector<string> Edges)
		{
			Clear();
			string s="";int i,x,y;
			for (i=0;i<int(Edges.size());i++) s+=Edges[i];
			istringstream ss(s);
			while (ss>>x>>y) addedge(x,y),ss.get();
			memset(visited,false,sizeof(visited));
			depth[1]=1;dfs(1,-1);
			for (i=1;i<=n;i++)
			{
				memset(visited,false,sizeof(visited));
				solve(i);
				hsh[i]=h[i];
			}
			LL ans=cnt[n];int snum=0;
			for (i=1;i<=n;i++) if (hsh[i]==h[n]) snum++;
			ans=(ans*snum)%MOD;
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,ee;
	CactusAutomorphisms A;
	while (scanf("%d%d",&nn,&ee)!=EOF)
	{
		vector<string> vv;string ss;
		getchar();
		while (ee--) getline(cin,ss),vv.pb(ss);
		cout<<A.count(nn,vv)<<endl;
	}
	return 0;
}
*/
/*
4 1
1 2,1 3,1 4
4 1
1 2,2 3,3 4,4 1
6 1
1 2,2 3,3 1,4 5,5 6,6 4,1 4 
18 3
1 2,2 3,3 4,2 4,1 5,1 10,5 10,5 6,6 7
,7 8,7 16,7 17,7 9,6 9,10 18,18 
12,12 11,11 18,12 13,12 14,12 15
200 30
1 2,2 3,3 4,4 5,5 6,6 7,7 8,8 9,9 10,10 11,11 2,1 
12,12 13,13 14,14 15,15 16,16 17,17 18,18 19,19 20
,20 21,21 12,1 22,22 23,23 24,24 25,25 26,26 27,27
 28,28 29,29 30,30 31,31 22,1 32,32 33,32 34,34 35
,35 36,36 32,1 37,37 38,37 39,39 40,40 41,41 37,1 
42,42 43,42 44,44 45,45 46,46 42,1 47,47 48,47 49,
49 50,50 51,51 47,1 52,52 53,52 54,54 55,55 56,56 
52,1 57,57 58,57 59,59 60,60 61,61 57,1 62,62 63,6
2 64,64 65,65 66,66 62,1 67,67 68,67 69,69 70,70 7
1,71 67,1 72,72 73,72 74,74 75,75 76,76 72,1 77,77
 78,78 79,79 80,80 81,81 77,1 82,82 83,83 84,84 85
,85 86,86 82,1 87,87 88,88 89,89 90,90 91,91 87,1 
92,92 93,93 94,94 95,95 96,96 92,1 97,97 98,98 99,
99 100,100 101,101 97,1 102,102 103,103 104,104 10
5,105 106,106 102,1 107,107 108,108 109,109 110,11
0 111,111 107,1 112,112 113,113 114,114 115,115 11
6,116 112,1 117,117 118,118 119,119 120,120 121,12
1 117,1 122,122 123,123 124,124 125,125 126,126 12
2,1 127,127 128,128 129,129 130,130 131,131 127,1 
132,132 133,133 134,134 135,135 136,136 132,1 137,
137 138,138 139,139 140,140 141,141 137,1 142,142 
143,142 144,142 145,1 146,146 147,146 148,146 149,
1 150,150 151,150 152,150 153,1 154,154 155,154 15
6,154 157,1 158,158 159,158 160,158 161,1 162,162 
163,162 164,162 165,1 166,166 167,167 168,166 169,
166 170,166 171,166 172,1 173,173 174,174 175,173 
176,173 177,173 178,173 179,1 180,180 181,181 182,
180 183,180 184,180 185,180 186,1 187,187 188,188 
189,187 190,187 191,187 192,187 193,1 194,194 195,
195 196,194 197,194 198,194 199,194 200
*/
