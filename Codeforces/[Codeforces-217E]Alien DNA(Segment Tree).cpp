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
#include <ctime>
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
	int left,right;
	int len;
}tree[3000048*3];

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;tree[cur].len=(right-left+1);
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
	}
}

void update(int cur,int pos)
{
	tree[cur].len--;
	if (tree[cur].left==tree[cur].right) return;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos); else update(cur<<1|1,pos);
}

int query(int cur,int key)
{
	if (tree[cur].left==tree[cur].right) return tree[cur].left;
	if (tree[cur<<1].len>=key) return query(cur<<1,key); else return query(cur<<1|1,key-tree[cur<<1].len);
}

int tmp[3000048];
char ans[3000048];
char s[3000048];
int n,k,curlen;
vector<Pair> step[5048];
Pair ope[5048];

void Copy(int cleft,int cright,int left,int right,int ind)
{
	int i,j,dir;
	if (cleft==cright)
	{
		if (left==right)
			step[ind].pb(mp(query(1,cright+1),query(1,cright)));
		return;
	}
	for (i=cleft+1,dir=0,j=left;!(dir==1 && i>cright) && j<=right;(i+2<=cright?i+=2:i=cleft),j++)
		step[ind].pb(mp(query(1,j),query(1,i)));
}

void Delete(int left,int right)
{
	int i;
	for (i=left;i<=right;i++) tmp[i]=query(1,i);
	for (i=left;i<=right;i++)
		update(1,tmp[i]);
}

int cc=0;
void go_tree(int cur)
{
	if (tree[cur].left==tree[cur].right)
	{
		ans[tree[cur].left]=s[++cc];
		return;
	}
	if (tree[cur<<1].len) go_tree(cur<<1);
	if (tree[cur<<1|1].len) go_tree(cur<<1|1);
}

int main ()
{
	int i,j;
	scanf("%s",s+1);
	k=getint();n=getint();
	build(1,1,k);
	for (i=1;i<=n;i++) ope[i].x=getint(),ope[i].y=getint();
	curlen=k;
	for (i=n;i>=1;i--)
		if (ope[i].y<curlen)
		{
			Copy(ope[i].x,ope[i].y,ope[i].y+1,min(ope[i].y*2-ope[i].x+1,curlen),i);
			Delete(ope[i].y+1,min(ope[i].y*2-ope[i].x+1,curlen));
			if (ope[i].y*2-ope[i].x+1<=curlen)
				curlen-=ope[i].y-ope[i].x+1;
			else
				curlen=ope[i].y;
		}
	go_tree(1);
	for (i=1;i<=n;i++)
		for (j=0;j<int(step[i].size());j++)
			ans[step[i][j].x]=ans[step[i][j].y];
	puts(ans+1);
	return 0;
}