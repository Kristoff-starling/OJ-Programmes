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

struct node
{
	int fail;bool danger;
	int next[15];
}trie[500048];int tot=0;

void Insert(string s)
{
	int i,j,cur=1,len=s.size();
	for (i=0;i<=len-1;i++)
	{
		if (!trie[cur].next[s[i]-'0'])
		{
			trie[cur].next[s[i]-'0']=++tot;
			for (j=1;j<=10;j++) trie[tot].next[j]=0;
			trie[tot].fail=0;trie[tot].danger=false;
		}
		cur=trie[cur].next[s[i]-'0'];
		if (i==len-1) trie[cur].danger=true;
	}
}

queue<int> q;
void construct_fail()
{
	int i,cur,tmp;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=10;i++)
			if (trie[cur].next[i])
			{
				tmp=trie[cur].fail;
				while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
				trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
				q.push(trie[cur].next[i]);
			}
			else
				trie[cur].next[i]=(cur==1?1:trie[trie[cur].fail].next[i]);
	}
}

int n,X,Y,Z;
vector<string> s1,s2,s3;
string s;
LL dp[48][500048];

void dfs(int left,string cur,vector<string> &res)
{
	if (left==0)
	{
		res.pb(cur);
		return;
	}
	int i;
	for (i=1;i<=10;i++)
		if (left>=i) dfs(left-i,cur+string(1,'0'+i),res);
}

bool check(int tmp,int cur)
{
	if (trie[trie[tmp].next[cur]].danger) return false;
	if (trie[tmp].fail && !check(trie[tmp].fail,cur)) return false;
	return true;
}

LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1)
		{
			res=(res*x)%MOD;
			y--;
		}
		x=(x*x)%MOD;
		y>>=1;
	}
	return res;
}

int main ()
{
	int i,j,k,cur;
	n=getint();X=getint();Y=getint();Z=getint();
	dfs(X,"",s1);dfs(Y,"",s2);dfs(Z,"",s3);
	tot=1;
	trie[1].danger=false;trie[1].fail=0;
	for (i=1;i<=10;i++) trie[1].next[i]=0;
	for (i=0;i<int(s1.size());i++)
		for (j=0;j<int(s2.size());j++)
			for (k=0;k<int(s3.size());k++)
				if (int(s1[i].size())+int(s2[j].size())+int(s3[k].size())<=n)
				{
					s=s1[i]+s2[j]+s3[k];
					Insert(s);
				}
	construct_fail();
	dp[0][1]=1;
	for (i=0;i<=n-1;i++)
		for (j=1;j<=tot;j++)
			if (dp[i][j])
				for (cur=1;cur<=10;cur++)
					if (check(j,cur))
						dp[i+1][trie[j].next[cur]]=(dp[i+1][trie[j].next[cur]]+dp[i][j])%MOD;
	LL ans=quick_pow(10ll,n);
	for (i=1;i<=tot;i++) ans=((ans-dp[n][i])%MOD+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}