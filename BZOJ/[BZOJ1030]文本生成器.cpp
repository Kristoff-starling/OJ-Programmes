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

const int MOD=10007;
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
	bool danger;
	int next[48];
	int fail;
}trie[100048];

int n,m,tot=1;
char s[148];
LL dp[148][10048];

void Insert()
{
	int i,j,cur=1,len=strlen(s+1);
	for (i=1;i<=len;i++)
	{
		if (!trie[cur].next[s[i]-'A'+1])
		{
			trie[cur].next[s[i]-'A'+1]=++tot;
			for (j=1;j<=26;j++) trie[tot].next[j]=0;
			trie[tot].fail=0;trie[tot].danger=false;
		}
		cur=trie[cur].next[s[i]-'A'+1];
		if (i==len) trie[cur].danger=true;
	}
}

queue<int> q;
void construct_fail()
{
	int i,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie[cur].next[i])
			{
				int tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=tmp?trie[tmp].next[i]:1;
				q.push(trie[cur].next[i]);
			}
			else
				trie[cur].next[i]=cur==1?1:trie[trie[cur].fail].next[i];
	}
}

bool Safe(int cur,int k)
{
	if (trie[cur].next[k] && trie[trie[cur].next[k]].danger) return false;
	if (!trie[cur].fail) return true;
	return Safe(trie[cur].fail,k);
}

int main ()
{
	int i,j,k;
	n=getint();m=getint();
	trie[1].danger=false;
	for (i=1;i<=26;i++) trie[1].next[i]=0;
	trie[1].fail=0;
	for (i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		Insert();
	}
	construct_fail();
	dp[0][1]=1;
	for (i=0;i<=m-1;i++)
		for (j=1;j<=tot;j++)
			for (k=1;k<=26;k++)
				if (Safe(j,k))
					dp[i+1][trie[j].next[k]]=(dp[i+1][trie[j].next[k]]+dp[i][j])%MOD;
	LL ans=1;
	for (i=1;i<=m;i++) ans=(ans*26)%MOD;
	for (i=1;i<=tot;i++) ans=((ans-dp[m][i])%MOD+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}
