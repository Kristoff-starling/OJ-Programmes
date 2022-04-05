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

struct node
{
	int fail,ind;
	int next[5];
	int depth,nearest;
}trie[10048];
int tot=1;

char s[1048];int len;
int table[148];

LL dp[1048][148][20];
int n,num;

void Insert(int len)
{
	int i,j,cur=1;
	for (i=1;i<=len;i++)
	{
		if (!trie[cur].next[table[s[i]]])
		{
			trie[cur].next[table[s[i]]]=++tot;
			trie[tot].fail=trie[tot].ind=0;
			trie[tot].depth=trie[cur].depth+1;
			for (j=1;j<=4;j++) trie[tot].next[j]=0;
		}
		cur=trie[cur].next[table[s[i]]];
		if (i==len) trie[cur].ind=1;
	}
}

queue<int> q;
void construct_fail()
{
	int i,cur,tmp;
	q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=4;i++)
			if (trie[cur].next[i])
			{
				tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
				q.push(trie[cur].next[i]);
			}
	}
}

void dfs(int cur,int tp)
{
	int i;
	trie[cur].nearest=tp;
	for (i=1;i<=4;i++)
		if (trie[cur].next[i])
			dfs(trie[cur].next[i],trie[trie[cur].next[i]].ind?trie[trie[cur].next[i]].depth:tp);
}

int main ()
{
	int i,j,k,cur,tmp;
	n=getint();num=getint();
	table['A']=1;table['T']=2;table['G']=3;table['C']=4;
	trie[1].fail=trie[1].ind=trie[1].depth=0;
	for (i=1;i<=4;i++) {trie[1].next[i]=0;}
	for (i=1;i<=num;i++)
	{
		scanf("%s",s+1);
		len=strlen(s+1);
		if (len<=n) Insert(len);
	}
	construct_fail();
	dfs(1,0);
	dp[0][1][0]=1;
	for (i=0;i<=n-1;i++)
		for (j=1;j<=tot;j++)
			for (k=0;k<=trie[j].depth;k++)
				if (dp[i][j][k])
				{
					for (cur=1;cur<=4;cur++)
					{
						tmp=j;
						while (tmp && !trie[tmp].next[cur]) tmp=trie[tmp].fail;
						int newk=k+1,tt=trie[tmp].next[cur];
						while (tt && trie[tt].depth>=k+1)
						{
							newk=min(newk,trie[tt].depth-trie[tt].nearest);
							tt=trie[tt].fail;
						}
						if (tmp && trie[trie[tmp].next[cur]].depth>=newk)
							dp[i+1][trie[tmp].next[cur]][newk]=(dp[i+1][trie[tmp].next[cur]][newk]+dp[i][j][k])%MOD;
					}
				}
	LL ans=0;
	for (i=2;i<=tot;i++)
		ans=(ans+dp[n][i][0])%MOD;
	cout<<ans<<endl;
	return 0;
}