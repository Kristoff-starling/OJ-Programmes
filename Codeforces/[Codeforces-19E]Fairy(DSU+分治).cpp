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

struct Ope
{
	int x,y;
	bool type;
}ope[100048];
int tot=0;

int pre[20048],rnk[20048];
int find_anc(int x)
{
	while (pre[x]!=x) x=pre[x];
	return x;
}
void update(int x,int y)
{
	x=find_anc(x);y=find_anc(y);
	if (x==y)
	{
		ope[++tot]=Ope{x,y,false};
		return;
	}
	if (rnk[x]>=rnk[y])
	{
		pre[y]=x;
		ope[++tot]=Ope{x,y,false};
		if (rnk[x]==rnk[y]) rnk[x]++,ope[tot].type=true;
	}
	else
	{
		ope[++tot]=Ope{y,x,false};
		pre[x]=y;
	}
}
void undo()
{
	int x=ope[tot].x,y=ope[tot].y;
	pre[y]=y;
	if (ope[tot].type) rnk[x]--;
	tot--;
}

int n,e;
Pair edge[10048];
int ansnum;
vector<int> ans;
bool Conflict=false;

void Add(int x,int y)
{
	//if (find_anc(x)==find_anc(y+n)) Conflict=true;
	update(x,y+n);
	//if (find_anc(x+n)==find_anc(y)) Conflict=true;
	update(x+n,y);
	if (find_anc(x)==find_anc(x+n) || find_anc(y)==find_anc(y+n)) Conflict=true;
}

void solve(int left,int right)
{
	if (left==right)
	{
		ansnum++;
		ans.pb(left);
		return;
	}
	int i,mid=(left+right)>>1;
	Conflict=false;
	for (i=left;i<=mid;i++)
		Add(edge[i].x,edge[i].y);
	if (!Conflict) solve(mid+1,right);
	for (i=left;i<=mid;i++) undo(),undo();
	Conflict=false;
	for (i=mid+1;i<=right;i++)
		Add(edge[i].x,edge[i].y);
	if (!Conflict) solve(left,mid);
	for (i=mid+1;i<=right;i++) undo(),undo();
	Conflict=false;
}

int main ()
{
	int i;
	n=getint();e=getint();
	if (e==0)
	{
		printf("0\n");
		return 0;
	}
	for (i=1;i<=e;i++) edge[i].x=getint(),edge[i].y=getint();
	for (i=1;i<=n*2;i++) pre[i]=i,rnk[i]=1;
	solve(1,e);
	printf("%d\n",ansnum);
	if (ansnum)
	{
		sort(ans.begin(),ans.end());
		for (i=0;i<int(ans.size());i++)
			printf("%d ",ans[i]);
	}
	return 0;
}