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
const int magic=548;
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

vector<string> add_big,add_small,del_big,del_small;
int add_bigsz,add_smallsz,del_bigsz,del_smallsz;
bool addedbig,addedsmall,delledbig,delledsmall;
string s;
int n;

struct node
{
	int fail,ind;
	int next[30];
}trie_addbig[300048],trie_addsmall[300048],trie_delbig[300048],trie_delsmall[300048];
int tot_addbig,tot_addsmall,tot_delbig,tot_delsmall;

void Insert_addbig(string s)
{
	int i,j,cur,len=int(s.size());cur=1;
	for (i=0;i<=len-1;i++)
	{
		if (!trie_addbig[cur].next[s[i]-'a'+1])
		{
			trie_addbig[cur].next[s[i]-'a'+1]=++tot_addbig;
			trie_addbig[tot_addbig].fail=trie_addbig[tot_addbig].ind=0;
			for (j=1;j<=26;j++)
				trie_addbig[tot_addbig].next[j]=0;
		}
		cur=trie_addbig[cur].next[s[i]-'a'+1];
		if (i==len-1) trie_addbig[cur].ind++;
	}
}

void Insert_addsmall(string s)
{
	int i,j,cur,len=int(s.size());cur=1;
	for (i=0;i<=len-1;i++)
	{
		if (!trie_addsmall[cur].next[s[i]-'a'+1])
		{
			trie_addsmall[cur].next[s[i]-'a'+1]=++tot_addsmall;
			trie_addsmall[tot_addsmall].fail=trie_addsmall[tot_addsmall].ind=0;
			for (j=1;j<=26;j++)
				trie_addsmall[tot_addsmall].next[j]=0;
		}
		cur=trie_addsmall[cur].next[s[i]-'a'+1];
		if (i==len-1) trie_addsmall[cur].ind++;
	}
}

void Insert_delbig(string s)
{
	int i,j,cur,len=int(s.size());cur=1;
	for (i=0;i<=len-1;i++)
	{
		if (!trie_delbig[cur].next[s[i]-'a'+1])
		{
			trie_delbig[cur].next[s[i]-'a'+1]=++tot_delbig;
			trie_delbig[tot_delbig].fail=trie_delbig[tot_delbig].ind=0;
			for (j=1;j<=26;j++)
				trie_delbig[tot_delbig].next[j]=0;
		}
		cur=trie_delbig[cur].next[s[i]-'a'+1];
		if (i==len-1) trie_delbig[cur].ind++;
	}
}

void Insert_delsmall(string s)
{
	int i,j,cur,len=int(s.size());cur=1;
	for (i=0;i<=len-1;i++)
	{
		if (!trie_delsmall[cur].next[s[i]-'a'+1])
		{
			trie_delsmall[cur].next[s[i]-'a'+1]=++tot_delsmall;
			trie_delsmall[tot_delsmall].fail=trie_delsmall[tot_delsmall].ind=0;
			for (j=1;j<=26;j++)
				trie_delsmall[tot_delsmall].next[j]=0;
		}
		cur=trie_delsmall[cur].next[s[i]-'a'+1];
		if (i==len-1) trie_delsmall[cur].ind++;
	}
}

queue<int> q;
void construct_fail_addbig()
{
	int i,tmp,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie_addbig[cur].next[i])
			{
				tmp=trie_addbig[cur].fail;
				while (tmp && !trie_addbig[tmp].next[i]) tmp=trie_addbig[tmp].fail;
				trie_addbig[trie_addbig[cur].next[i]].fail=(tmp?trie_addbig[tmp].next[i]:1);
				trie_addbig[trie_addbig[cur].next[i]].ind+=(tmp?trie_addbig[trie_addbig[tmp].next[i]].ind:0);
				q.push(trie_addbig[cur].next[i]);
			}
			else
				trie_addbig[cur].next[i]=(cur==1?1:trie_addbig[trie_addbig[cur].fail].next[i]);
	}
}

void construct_fail_addsmall()
{
	int i,tmp,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie_addsmall[cur].next[i])
			{
				tmp=trie_addsmall[cur].fail;
				while (tmp && !trie_addsmall[tmp].next[i]) tmp=trie_addsmall[tmp].fail;
				trie_addsmall[trie_addsmall[cur].next[i]].fail=(tmp?trie_addsmall[tmp].next[i]:1);
				trie_addsmall[trie_addsmall[cur].next[i]].ind+=(tmp?trie_addsmall[trie_addsmall[tmp].next[i]].ind:0);
				q.push(trie_addsmall[cur].next[i]);
			}
			else
				trie_addsmall[cur].next[i]=(cur==1?1:trie_addsmall[trie_addsmall[cur].fail].next[i]);
	}
}

void construct_fail_delbig()
{
	int i,tmp,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie_delbig[cur].next[i])
			{
				tmp=trie_delbig[cur].fail;
				while (tmp && !trie_delbig[tmp].next[i]) tmp=trie_delbig[tmp].fail;
				trie_delbig[trie_delbig[cur].next[i]].fail=(tmp?trie_delbig[tmp].next[i]:1);
				trie_delbig[trie_delbig[cur].next[i]].ind+=(tmp?trie_delbig[trie_delbig[tmp].next[i]].ind:0);
				q.push(trie_delbig[cur].next[i]);
			}
			else
				trie_delbig[cur].next[i]=(cur==1?1:trie_delbig[trie_delbig[cur].fail].next[i]);
	}
}

void construct_fail_delsmall()
{
	int i,tmp,cur;q.push(1);
	while (!q.empty())
	{
		cur=q.front();q.pop();
		for (i=1;i<=26;i++)
			if (trie_delsmall[cur].next[i])
			{
				tmp=trie_delsmall[cur].fail;
				while (tmp && !trie_delsmall[tmp].next[i]) tmp=trie_delsmall[tmp].fail;
				trie_delsmall[trie_delsmall[cur].next[i]].fail=(tmp?trie_delsmall[tmp].next[i]:1);
				trie_delsmall[trie_delsmall[cur].next[i]].ind+=(tmp?trie_delsmall[trie_delsmall[tmp].next[i]].ind:0);
				q.push(trie_delsmall[cur].next[i]);
			}
			else
				trie_delsmall[cur].next[i]=(cur==1?1:trie_delsmall[trie_delsmall[cur].fail].next[i]);
	}
}

int query_addbig(string s)
{
	int i,cur=1,len=int(s.size()),res=0;
	for (i=0;i<=len-1;i++)
	{
		cur=trie_addbig[cur].next[s[i]-'a'+1];
		res+=trie_addbig[cur].ind;
	}
	return res;
}

int query_addsmall(string s)
{
	int i,cur=1,len=int(s.size()),res=0;
	for (i=0;i<=len-1;i++)
	{
		cur=trie_addsmall[cur].next[s[i]-'a'+1];
		res+=trie_addsmall[cur].ind;
	}
	return res;
}

int query_delbig(string s)
{
	int i,cur=1,len=int(s.size()),res=0;
	for (i=0;i<=len-1;i++)
	{
		cur=trie_delbig[cur].next[s[i]-'a'+1];
		res+=trie_delbig[cur].ind;
	}
	return res;
}

int query_delsmall(string s)
{
	int i,cur=1,len=int(s.size()),res=0;
	for (i=0;i<=len-1;i++)
	{
		cur=trie_delsmall[cur].next[s[i]-'a'+1];
		res+=trie_delsmall[cur].ind;
	}
	return res;
}

LL solve()
{
	int i;
	if (addedbig)
	{
		tot_addbig=1;
		trie_addbig[1].fail=trie_addbig[1].ind=0;
		for (i=1;i<=26;i++) trie_addbig[1].next[i]=0;
		for (i=0;i<int(add_big.size());i++)
			Insert_addbig(add_big[i]);
		construct_fail_addbig();
	}
	if (addedsmall)
	{
		tot_addsmall=1;
		trie_addsmall[1].fail=trie_addsmall[1].ind=0;
		for (i=1;i<=26;i++) trie_addsmall[1].next[i]=0;
		for (i=0;i<int(add_small.size());i++)
			Insert_addsmall(add_small[i]);
		construct_fail_addsmall();
	}
	if (delledbig)
	{
		tot_delbig=1;
		trie_delbig[1].fail=trie_delbig[1].ind=0;
		for (i=1;i<=26;i++) trie_delbig[1].next[i]=0;
		for (i=0;i<int(del_big.size());i++)
			Insert_delbig(del_big[i]);
		construct_fail_delbig();
	}
	if (delledsmall)
	{
		tot_delsmall=1;
		trie_delsmall[1].fail=trie_delsmall[1].ind=0;
		for (i=1;i<=26;i++) trie_delsmall[1].next[i]=0;
		for (i=0;i<int(del_small.size());i++)
			Insert_delsmall(del_small[i]);
		construct_fail_delsmall();
	}
	LL res=0;
	res+=query_addbig(s);res+=query_addsmall(s);
	res-=query_delbig(s);res-=query_delsmall(s);
	return res;
}

int main ()
{
	int type,i;
	n=getint();
	add_bigsz=add_smallsz=del_bigsz=del_smallsz=0;
	addedbig=addedsmall=delledbig=delledsmall=false;
	tot_addbig=tot_addsmall=tot_delbig=tot_delsmall=1;
	while (n--)
	{
		type=getint();cin>>s;
		if (type==1)
		{
			add_small.pb(s);
			if (!addedsmall) addedsmall=true;
			add_smallsz+=int(s.size());
		}
		if (type==2)
		{
			del_small.pb(s);
			if (!delledsmall) delledsmall=true;
			del_smallsz+=int(s.size());
		}
		if (type==3)
		{
			if (add_smallsz>magic)
			{
				addedbig=true;
				add_bigsz+=add_smallsz;add_smallsz=0;
				for (i=0;i<int(add_small.size());i++) add_big.pb(add_small[i]);
				add_small.clear();
			}
			if (del_smallsz>magic)
			{
				delledbig=true;
				del_bigsz+=del_smallsz;del_smallsz=0;
				for (i=0;i<int(del_small.size());i++) del_big.pb(del_small[i]);
				del_small.clear();
			}
			printf("%lld\n",solve());
			fflush(stdout);
			addedbig=addedsmall=delledbig=delledsmall=false;
		}
	}
	return 0;
}