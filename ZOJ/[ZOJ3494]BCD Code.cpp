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
	bool isdanger[5];
	int fail;bool danger;
	int next[5];bool exist[5];
	int father;
}trie[10048];
int tot=1;

LL DP[248][2048][2];
LL dp[248][2048][2];
LL tans[248];
char A[248],B[248];int lena,lenb;
char s[248];
int num[10][10];
int To[2048][12];
int n;

inline void TEN_TO_TWO(int x)
{
	int ind=x;
	for (int i=1;i<=4;i++) num[ind][i]=0;
	int pt=4;
	while (x)
	{
		num[ind][pt--]=x%2;
		x/=2;
	}
}

void Clear()
{
	tot=1;
	trie[tot].father=tot;
	trie[tot].fail=0;trie[tot].danger=false;
	for (int i=1;i<=2;i++) trie[tot].next[i]=0,trie[tot].exist[i]=false;
}

void Insert(int len)
{
	int i,j,cur=1;
	for (i=1;i<=len;i++)
	{
		if (!trie[cur].next[s[i]-'0'+1])
		{
			trie[cur].next[s[i]-'0'+1]=++tot;
			trie[cur].exist[s[i]-'0'+1]=true;
			trie[tot].father=cur;
			trie[tot].fail=0;trie[tot].danger=false;
			for (j=1;j<=2;j++) trie[tot].next[j]=0,trie[tot].exist[j]=false;
		}
		cur=trie[cur].next[s[i]-'0'+1];
		if (i==len) trie[cur].danger=true;
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
		for (i=1;i<=2;i++)
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

void dfs(int cur)
{
	int i,tmp;
	for (i=1;i<=2;i++)
	{
		tmp=cur;
		trie[cur].isdanger[i]=false;
		while (tmp)
		{
			if (trie[trie[tmp].next[i]].danger)
			{
				trie[cur].isdanger[i]=true;
				break;
			}
			tmp=trie[tmp].fail;
		}
	}
	for (i=1;i<=2;i++)
		if (trie[cur].exist[i]) dfs(trie[cur].next[i]);
}

int Go(int cur,int dir)
{
	if (trie[cur].isdanger[dir+1]) return -1;
	return trie[cur].next[dir+1];
}

int check(int cur,int add)
{
	int i;
	for (i=1;i<=4;i++)
	{
		cur=Go(cur,num[add][i]);
		if (cur==-1) return cur;
	}
	return cur;
}

void init_To()
{
	int i,cur;
	for (i=1;i<=tot;i++)
		for (cur=0;cur<=9;cur++)
			To[i][cur]=check(i,cur);
}

void init_dp()
{
	int i,j,cur,to;
	memset(dp,0,sizeof(dp));
	dp[0][1][0]=1;
	for (i=0;i<=max(lena,lenb)-1;i++)
		for (j=1;j<=tot;j++)
			if(dp[i][j][0])
				for (cur=0;cur<=9;cur++)
				{
					if (cur==0 && i==0) continue;
					to=To[j][cur];
					if (to!=-1)
						dp[i+1][to][0]=(dp[i+1][to][0]+dp[i][j][0])%MOD;
				}
	for (i=1;i<=max(lena,lenb);i++)
	{
		tans[i]=0;
		for (j=1;j<=tot;j++)
			tans[i]=(tans[i]+dp[i][j][0])%MOD;
	}
}

void Minus(int &len)
{
	int i,j,cur=len;
	s[cur]--;
	while (s[cur]<'0')
	{
		s[cur]+=10;
		s[--cur]--;
	}
	for (i=1;s[i]=='0' && i<=len;i++) {}
	i--;
	for (j=i+1;j<=len;j++) s[j-i]=s[j];
	len-=i;
}

LL solve(int type)
{
	int i,j,to,cur,len;
	if (type)
	{
		for (i=1;i<=lenb;i++) s[i]=B[i];
		len=lenb;
	}
	else
	{
		for (i=1;i<=lena;i++) s[i]=A[i];
		len=lena;
		Minus(len);
	}
	if (len==0) return 0;
	LL res=0;
	for (i=1;i<=len-1;i++) res=(res+tans[i])%MOD;
	memset(DP,0,sizeof(DP));
	DP[0][1][1]=1;
	for (i=0;i<=len-1;i++)
		for (j=1;j<=tot;j++)
		{
			if (DP[i][j][0])
			{
				for (cur=0;cur<=9;cur++)
				{
					if (cur==0 && i==0) continue;
					to=To[j][cur];
					if (to!=-1)
						DP[i+1][to][0]=(DP[i+1][to][0]+DP[i][j][0])%MOD;
				}
			}
			if (DP[i][j][1])
			{
				for (cur=0;cur<=s[i+1]-'0'-1;cur++)
				{
					if (cur==0 && i==0) continue;
					to=check(j,cur);
					if (to!=-1)
						DP[i+1][to][0]=(DP[i+1][to][0]+DP[i][j][1])%MOD;
				}
				to=check(j,s[i+1]-'0');
				if (to!=-1)
					DP[i+1][to][1]=(DP[i+1][to][1]+DP[i][j][1])%MOD;
			}
		}
	for (i=1;i<=tot;i++)
		res=(res+DP[len][i][0]+DP[len][i][1])%MOD;
	return res;
}

int main ()
{
	int ca,i,len;
	ca=getint();
	for (i=0;i<=9;i++) TEN_TO_TWO(i);
	while (ca--)
	{
		n=getint();
		Clear();
		for (i=1;i<=n;i++)
		{
			scanf("%s",s+1);
			len=strlen(s+1);
			//cout<<len<<endl;
			Insert(len);
		}
		construct_fail();
		dfs(1);
		init_To();
		scanf("%s%s",A+1,B+1);
		lena=strlen(A+1);lenb=strlen(B+1);
		init_dp();
		cout<<((solve(1)-solve(0))%MOD+MOD)%MOD<<endl;
	}
	return 0;
}
