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
	int next[30];
	int val,fail;
	int maxn[15];
	inline void init()
	{
		val=fail=0;
		for (int i=1;i<=26;i++) next[i]=0;
		for (int i=1;i<=10;i++) maxn[i]=0;
	}
}SAM[800048];int tot=0;
int root,last;
vector<int> v[100048];

char s1[100048],s2[100048];
int len1,len2;

inline void extend(int w)
{
	int p=last,np=++tot;SAM[np].init();
	SAM[np].val=SAM[p].val+1;v[SAM[np].val].pb(np);
	while (p && !SAM[p].next[w]) SAM[p].next[w]=np,p=SAM[p].fail;
	if (!p)
		SAM[np].fail=root;
	else
	{
		int q=SAM[p].next[w];
		if (SAM[p].val+1==SAM[q].val)
			{SAM[np].fail=q;}
		else
		{
			int nq=++tot;SAM[nq].init();
			memcpy(SAM[nq].next,SAM[q].next,sizeof(SAM[q].next));
			SAM[nq].val=SAM[p].val+1;v[SAM[nq].val].pb(nq);
			SAM[nq].fail=SAM[q].fail;
			SAM[q].fail=nq;SAM[np].fail=nq;
			while (p && SAM[p].next[w]==q) SAM[p].next[w]=nq,p=SAM[p].fail;
		}
	}
	last=np;
}

int main ()
{
	int i,j;
	scanf("%s",s1+1);len1=strlen(s1+1);
	root=last=++tot;SAM[root].init();
	for (i=1;i<=len1;i++)
		extend(s1[i]-'a'+1);
	int len,ans=0,cur,ind=0;
	while (scanf("%s",s2+1)!=EOF)
	{
		++ind;
		len2=strlen(s2+1);cur=root;len=0;
		for (i=1;i<=len2;i++)
		{
			int w=s2[i]-'a'+1;
			if (SAM[cur].next[w])
			{
				len++;
				cur=SAM[cur].next[w];
			}
			else
			{
				while (cur && !SAM[cur].next[w]) cur=SAM[cur].fail;
				if (!cur)
					len=0,cur=root;
				else
				{
					len=SAM[cur].val+1;
					cur=SAM[cur].next[w];
				}
			}
			SAM[cur].maxn[ind]=max(SAM[cur].maxn[ind],len);
		}
	}
	for (len=len1;len>=1;len--)
		for (i=0;i<int(v[len].size());i++)
			for (j=1;j<=ind;j++)
				if (SAM[v[len][i]].fail) 
				{
					SAM[SAM[v[len][i]].fail].maxn[j]=max(SAM[SAM[v[len][i]].fail].maxn[j],SAM[v[len][i]].maxn[j]);
				}
	for (i=1;i<=tot;i++)
	{
		int res=INF;
		for (j=1;j<=ind;j++)
			res=min(res,SAM[i].maxn[j]);
		res=min(res,SAM[i].val);
		ans=max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
