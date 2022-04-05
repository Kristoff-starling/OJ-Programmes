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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

struct node
{
	int next[30],father,fail;
	vector<int> ind;
	vector<Pair> query;
	inline void clear(int fa)
	{
		for (int i=1;i<=26;i++) next[i]=0;
		father=fa;fail=0;
		ind.clear();query.clear();
	}
}trie[600048];int tot;

int q;
char s[100048];int len;
int ind[100048];
int ans[100048];

int L[100048],R[100048];
int head[300048],to[300048],nxt[300048],etot=1;
inline void addedge(int s,int t)
{
	to[++etot]=t;nxt[etot]=head[s];head[s]=etot;
}

void Insert()
{
	int i,itot=0,cur=1;
	tot=1;trie[1].clear(0);
	for (i=1;i<=len;i++)
	{
		if (s[i]=='P') {trie[cur].ind.pb(++itot);ind[itot]=cur;continue;}
		if (s[i]=='B') {cur=trie[cur].father;continue;}
		int w=s[i]-'a'+1;
		if (!trie[cur].next[w])
		{
			trie[cur].next[w]=++tot;
			trie[tot].clear(cur);
		}
		cur=trie[cur].next[w];
	}
}

queue<int> que;
void construct_fail()
{
	int i,cur,tmp;que.push(1);
	while (!que.empty())
	{
		cur=que.front();que.pop();
		for (i=1;i<=26;i++)
			if (trie[cur].next[i])
			{
				tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
				if (tmp) addedge(trie[tmp].next[i],trie[cur].next[i]); else addedge(1,trie[cur].next[i]);
				que.push(trie[cur].next[i]);
			}
	}
}

int tme=0;
inline void dfs(int cur)
{
	L[cur]=++tme;int i,y;
	for (i=head[cur];i;i=nxt[i])
		dfs(to[i]);
	R[cur]=tme;
}

namespace BIT
{
	int c[100048];
	inline void update(int x,int delta)
	{
		while (x<=tot)
		{
			c[x]+=delta;
			x+=LOWBIT(x);
		}
	}
	inline int query(int x)
	{
		int res=0;
		while (x)
		{
			res+=c[x];
			x-=LOWBIT(x);
		}
		return res;
	}
	inline int calc(int left,int right)
	{
		return query(right)-query(left-1);
	}
}

void Dfs(int cur)
{
	int i;
	if (cur!=1) BIT::update(L[cur],1);
	if (cur!=1)
		for (i=0;i<int(trie[cur].query.size());i++)
			ans[trie[cur].query[i].x]=BIT::calc(L[ind[trie[cur].query[i].y]],R[ind[trie[cur].query[i].y]]);
	for (i=1;i<=26;i++)
		if (trie[cur].next[i])
			Dfs(trie[cur].next[i]);
	if (cur!=1) BIT::update(L[cur],-1);
}

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);
	Insert();construct_fail();dfs(1);
	q=getint();int i,x,y;
	for (i=1;i<=q;i++)
	{
		x=getint();y=getint();
		trie[ind[y]].query.pb(mp(i,x));
	}
	Dfs(1);
	for (i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
