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

int n;

struct node
{
	int next[30];
}trie[300048];

int depth[300048],sz[300048],son[300048];
int ans[300048];

inline void dfs(int cur)
{
	sz[cur]=1;son[cur]=0;int i,to;
	for (i=1;i<=26;i++)
		if (trie[cur].next[i])
		{
			to=trie[cur].next[i];
			depth[to]=depth[cur]+1;
			dfs(to);
			sz[cur]+=sz[to];
			if (!son[cur] || sz[to]>sz[son[cur]]) son[cur]=to;
		}
}

Pair used[300048];int utot=0;
inline void merge(int cur,int root,int ind)
{
	int i,to1,to2;
	for (i=1;i<=26;i++)
	{
		to1=trie[cur].next[i];
		if (to1)
		{
			to2=trie[root].next[i];
			if (to2)
			{
				ans[ind]++;
				merge(to1,to2,ind);
			}
			else
			{
				trie[root].next[i]=to1;
				used[++utot]=mp(root,i);
			}
		}
	}
}

inline void Dfs(int cur)
{
	int i,to;
	for (i=1;i<=26;i++)
		if (trie[cur].next[i]) Dfs(trie[cur].next[i]),ans[depth[cur]]++;
	utot=0;
	for (i=1;i<=26;i++)
		if (trie[cur].next[i] && trie[cur].next[i]!=son[cur]) merge(trie[cur].next[i],son[cur],depth[cur]);
	for (i=1;i<=utot;i++)
		trie[used[i].x].next[used[i].y]=0;
}

int main ()
{
	int i,x,y;string ch;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();cin>>ch;
		trie[x].next[ch[0]-'a'+1]=y;
	}
	depth[1]=1;dfs(1);
	Dfs(1);
	int max_depth=1;for (i=1;i<=n;i++) max_depth=max(max_depth,depth[i]);
	int Ans=INF,ansind;
	for (i=1;i<=max_depth;i++)
		if (n-ans[i]<Ans) Ans=n-ans[i],ansind=i;
	printf("%d\n%d\n",Ans,ansind);
	return 0;
}
