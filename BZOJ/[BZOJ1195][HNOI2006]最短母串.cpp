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
#define Pair pair<int,short>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=1e9+7;
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
	int nxt[27];
	int Mask;int fail;
	inline void clear()
	{
		memset(nxt,0,sizeof(nxt));
		Mask=0;fail=0;
	}
}trie[602];int tot=1;

char s[602];
pair<Pair,short> pre[4097][501];
short dist[4097][501];

inline void Insert(int ind)
{
	int cur=1,len=strlen(s+1),i,w;
	for (i=1;i<=len;i++)
	{
		w=s[i]-'A'+1;
		if (!trie[cur].nxt[w])
		{
			trie[cur].nxt[w]=++tot;
			trie[tot].clear();
		}
		cur=trie[cur].nxt[w];
		if (i==len) trie[cur].Mask|=(1<<(ind-1));
	}
}

queue<int> q;
inline void construct_fail()
{
	q.push(1);int i,cur,tmp;
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie[cur].nxt[i])
			{
				tmp=trie[cur].fail;
				while (tmp && !trie[tmp].nxt[i]) tmp=trie[tmp].fail;
				trie[trie[cur].nxt[i]].fail=(tmp?trie[tmp].nxt[i]:1);
				trie[trie[cur].nxt[i]].Mask|=trie[trie[trie[cur].nxt[i]].fail].Mask;
				q.push(trie[cur].nxt[i]);
			}
			else
				trie[cur].nxt[i]=(cur==1?1:trie[trie[cur].fail].nxt[i]);
	}
}

int cc,minlen;
inline void bfs()
{
	pre[0][1]=mp(mp(-1,-1),0);
	q.push(0);q.push(1);
	int i,Mask,cur,toMask,to;
	for (Mask=0;Mask<=(1<<n)-1;Mask++)
		for (i=1;i<=tot;i++)
			dist[Mask][i]=3000;
	dist[0][1]=0;
	while (!q.empty())
	{
		Mask=q.front();q.pop();cur=q.front();q.pop();
		if (Mask==(1<<n)-1 && !cc) {cc=cur;minlen=dist[Mask][cc];}
		for (i=1;i<=26;i++)
		{
			to=trie[cur].nxt[i];
			toMask=(Mask|trie[to].Mask);
			if (dist[Mask][cur]+1<dist[toMask][to])
			{
				dist[toMask][to]=dist[Mask][cur]+1;
				pre[toMask][to]=mp(mp(Mask,cur),i);
				q.push(toMask);q.push(to);
			}
		}
	}
}

inline void getans(int cur,int Mask,int pos)
{
	if (pre[Mask][cur].y==0) return;
	s[pos]=pre[Mask][cur].y+'A'-1;
	getans(pre[Mask][cur].x.y,pre[Mask][cur].x.x,pos-1);
}

int main ()
{
	int i;n=getint();
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert(i);
	}
	construct_fail();
	bfs();
	//memset(s,'\0',sizeof(s));
	getans(cc,(1<<n)-1,minlen);
	for (i=1;i<=minlen;i++) printf("%c",s[i]);
	puts("");
	return 0;
}
