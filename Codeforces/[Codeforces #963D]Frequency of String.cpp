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
#define DEBUG(...) 
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

int ans[100048],Len[100048];
int pos_big[100048];

struct AC_Automation
{
	struct node
	{
		int next[30];
		int fail;vector<int> mark;int ind,K;
		inline void init()
		{
			fail=0;ind=0;K=0;mark.clear();
			for (register int i=1;i<=26;i++) next[i]=0;
		}
	}trie[100048];int tot=1;
	vector<int> v[100048],allmark[100048];
	inline void clear() {for (register int i=1;i<=tot;i++) v[i].clear(),allmark[i].clear();tot=1;trie[tot].init();}
	inline void Insert(string s,int ind,int curk)
	{
		int i,len=int(s.size()),cur=1,w;
		for (i=1;i<=len;i++)
		{
			w=s[i-1]-'a'+1;
			if (!trie[cur].next[w])
			{
				trie[cur].next[w]=++tot;
				trie[tot].init();
			}
			cur=trie[cur].next[w];
			if (i==len) trie[cur].ind=ind,trie[cur].K=curk;
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
				if (trie[cur].next[i])
				{
					tmp=trie[cur].fail;
					while (tmp && !trie[tmp].next[i]) tmp=trie[tmp].fail;
					trie[trie[cur].next[i]].fail=(tmp?trie[tmp].next[i]:1);
					v[trie[trie[cur].next[i]].fail].pb(trie[cur].next[i]);
					q.push(trie[cur].next[i]);
				}
				else
					trie[cur].next[i]=(cur==1?1:trie[trie[cur].fail].next[i]);
		}
	}
	inline void go_big(string s)
	{
		int i,cur=1,tmp,w,len=int(s.size());
		for (i=1;i<=len;i++)
		{
			w=s[i-1]-'a'+1;
			cur=trie[cur].next[w];trie[cur].mark.pb(i);
		}
	}
	inline void go_small(string s)
	{
		int i,cur=1,tmp,w,len=int(s.size());
		for (i=1;i<=len;i++)
		{
			w=s[i-1]-'a'+1;
			cur=trie[cur].next[w];tmp=cur;
			while (tmp) trie[tmp].mark.pb(i),tmp=trie[tmp].fail;
		}
	}
	vector<int> tmp;
	inline vector<int> merge(vector<int> a,vector<int> b)
	{
		tmp.clear();int n1=int(a.size())-1,n2=int(b.size())-1,k1,k2;
		for (k1=0,k2=0;k1<=n1 && k2<=n2;)
			if (a[k1]<b[k2]) tmp.pb(a[k1++]); else tmp.pb(b[k2++]);
		while (k1<=n1) tmp.pb(a[k1++]);
		while (k2<=n2) tmp.pb(b[k2++]);
		return tmp;
	}
	inline void dfs(int cur)
	{
		tmp=merge(tmp,trie[cur].mark);
		for (register int i=0;i<int(v[cur].size());i++) dfs(v[cur][i]);
	}
	inline void solve_big()
	{
		int i,j,cur;
		for (cur=2;cur<=tot;cur++)
			if (trie[cur].ind)
			{
				tmp.clear();
				dfs(cur);
				int k=trie[cur].K;
				if (int(tmp.size())<k) {ans[trie[cur].ind]=-1;continue;}
				ans[trie[cur].ind]=INF;
				for (i=k-1;i<int(tmp.size());i++) ans[trie[cur].ind]=min(ans[trie[cur].ind],tmp[i]-tmp[i-k+1]+Len[trie[cur].ind]);
			}
	}
	inline void solve_small()
	{
		int i,cur;
		for (cur=2;cur<=tot;cur++)
		{
			if (trie[cur].ind)
			{
				int k=trie[cur].K;
				if (int(trie[cur].mark.size())<k) {ans[trie[cur].ind]=-1;continue;}
				ans[trie[cur].ind]=INF;
				for (i=k-1;i<int(trie[cur].mark.size());i++) {ans[trie[cur].ind]=min(ans[trie[cur].ind],trie[cur].mark[i]-trie[cur].mark[i-k+1]+Len[trie[cur].ind]);}
			}
		}
	}
}A;

int n;
string s;

struct node
{
	string s;
	int ind,k;
}big[100048],small[100048];
int btot=0,stot=0;

string tmp;int kk;
int main ()
{
	int i;cin>>s;n=getint();
	for (i=1;i<=n;i++)
	{
		cin>>kk>>tmp;Len[i]=int(tmp.size());
		if (Len[i]>magic) big[++btot]=node{tmp,i,kk}; else small[++stot]=node{tmp,i,kk};
	}
	A.clear();
	for (i=1;i<=btot;i++) A.Insert(big[i].s,big[i].ind,big[i].k);
	A.construct_fail();A.go_big(s);
	A.solve_big();
	A.clear();
	for (i=1;i<=stot;i++) A.Insert(small[i].s,small[i].ind,small[i].k);
	A.construct_fail();A.go_small(s);
	A.solve_small();
	for (i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
