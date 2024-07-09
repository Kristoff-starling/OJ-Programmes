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

struct Treap
{
	int left,right;
	int val,prioriry,sz;
}Tree[5000048];
int Root[100048],Tot=0,rTot=0;

inline void Update(int root)
{
	Tree[root].sz=1;
	if (Tree[root].left!=-1) Tree[root].sz+=Tree[Tree[root].left].sz;
	if (Tree[root].right!=-1) Tree[root].sz+=Tree[Tree[root].right].sz;
}

int Create(int val,int priority,int left,int right)
{
	Tree[++Tot]=Treap{left,right,val,priority,0};
	Update(Tot);
	return Tot;
}

void Cop(int &a,int &b)
{
	if (b==-1) a=-1; else a=Create(0,0,-1,-1),Tree[a]=Tree[b];
}

int LeftSize(int root)
{
	int res=1;
	if (Tree[root].left!=-1) res+=Tree[Tree[root].left].sz;
	return res;
}

void Split(int root,int &a,int &b,int key)
{
	if (root==-1)
	{
		a=-1;b=-1;
		return;
	}
	if (Tree[root].val>=key)
	{
		Cop(b,root);
		Split(Tree[root].left,a,Tree[b].left,key);
		Update(b);
	}
	else
	{
		Cop(a,root);
		Split(Tree[root].right,Tree[a].right,b,key);
		Update(a);
	}
}

void Split2(int root,int &a,int &b,int key)
{
	if (root==-1)
	{
		a=-1;b=-1;
		return;
	}
	if (LeftSize(root)>key)
	{
		Cop(b,root);
		Split2(Tree[root].left,a,Tree[b].left,key);
		Update(b);
	}
	else
	{
		Cop(a,root);
		Split2(Tree[root].right,Tree[a].right,b,key-LeftSize(root));
		Update(a);
	}
}

void Merge(int root1,int root2,int &res)
{
	if (root1==-1) {res=root2;return;}
	if (root2==-1) {res=root1;return;}
	if (Tree[root1].priority<=Tree[root2].priority)
	{
		Cop(res,root1);
		Merge(Tree[root1].right,root2,Tree[res].right);
	}
	else
	{
		Cop(res,root2);
		Merge(root1,Tree[root2].left,Tree[res].left);
	}
	Update(res);
}

void Treap_insert(int val)
{
	Pair splitted;Split(Root[rTot],splitted.x,splitted.y);
	int tmp=-1;
	Merge(splitted.x,Create(val,rand(),-1,-1),tmp);
	Merge(tmp,splitted.y,Root[++rTot]);
}

void Treeap_delete(int val)
{
	Pair splitted;Split(Root[rTot],splitted.x,splitted.y,val);
	Pair splitted2;Split2(splitted.y,splitted2.x,splitted2.y,1);
	Merge(splitted.x,splitted2.y,Root[++rTot]);
}

void Treap_query(int val)
{
	Pair splitted;Split(Root[rTot],splitted.x,splitted.y,val);
	printf("%d\n",splitted.x==-1?0:Tree[splitted.x].sz);
}

struct treap
{
	int left,right;
	Pair val;int info;int priority,int sz;
}tree[5000048];
int root[100048],tot=0,rtot=0;

inline void update(int root)
{
	tree[root].sz=1;
	if (tree[root].left!=-1) tree[root].sz+=tree[tree[root].left].sz;
	if (tree[root].right!=-1) tree[root].sz+=tree[tree[root].right].sz;
}

int create(Pair val,int info,int priority,int left,int right)
{
	tree[++tot]=Create(left,right,val,info,priority,0);
	update(tot);
	return tot;
}

void cop(int &a,int b)
{
	if (b==-1) a=-1; else a=creat(mp(0,0),0,0,-1,-1),tree[a]=tree[b];
}

int leftsize(int root)
{
	int res=1;
	if (tree[root].left!=-1) res+=tree[tree[root].left].sz;
}

void split(int root,int &a,int &b,Pair key)
{
	if (root==-1)
	{
		a=-1;b=-1;
		return;
	}
	if (tree[root].val>=key)
	{
		cop(b,root);
		split(tree[root].left,a,tree[b].left,key);
		update(b);
	}
	else
	{
		cop(a,root);
		split(tree[root].right,tree[a].right,b,key);
		update(a);
	}
}

void split2(int root,int &a,int &b,int key)
{
	if (root==-1)
	{
		a=-1;b=-1;
		return;
	}
	if (leftsize(root)>key)
	{
		cop(b,root);
		split2(tree[root].left,a,tree[b].left,key);
		update(b);
	}
	else
	{
		cop(a,root);
		split2(tree[root].right,tree[a].right,b,key-leftsize(root));
		update(a);
	}
}

void merge(int root1,int root2,int &res)
{
	if (root1==-1) {res=root2;return;}
	if (root2==-1) {res=root1;return;}
	if (tree[root1].priority<=tree[root2].priority)
	{
		cop(res,root1);
		merge(tree[root1].right,root2,tree[res].right);
	}
	else
	{
		cop(res,root2);
		merge(root1,tree[root2].left,tree[res].left);
	}
	update(res);
}

int treap_find(Pair val)
{
	Pair splitted;split(root[rtot],splitted.x,splitted.y,val);
	Pair splitted2;split2(splitted.y,splitted2.x,splitted2.y,1);
	if (splitted2.x!=-1 || tree[splitted2.x].val!=val) return -1;
	return tree[splitted2.x].info;
}

void treap_insert(Pair val,int info)
{
	Pair splitted;split(root[rtot],splitted.x,splitted.y,val);
	int tmp=-1;
	merge(splitted.x,create(val,info,rand(),-1,-1),tmp);
	merge(tmp,splitted.y,root[++rtot]);
}

void treap_delete(Pair val)
{
	Pair splitted;split(root[rtot],splitted.x,splitted.y,val);
	Pair splitted2;split2(splitted.y,splitted2.x,splitted2.y,1);
	merge(splitted.x,splitted2.y,root[++rtot]);
}

const int p1=19260817,p2=998244353,p3=1e9+7;
inline Pair gethash(string s)
{
	int i;LL res1=0,res2=0;
	for (i=0;i<int(s.size());i++)
	{
		res1=(res1*p1+s[i])%p2;
		res2=(res2*p2+s[i])%p3;
	}
	return mp(res1,res2);
}

int main ()
{
	int q,x;scanf("%d",&q);string type,name;Pair val;
	Tot=tot=rTot=rtot=0;Root[0]=root[0]=-1;
	while (q--)
	{
		cin>>type;
		if (type[0]=='s')
		{
			cin>>name;scanf("%d",&x);val=gethash(name);
			int info=treap_find(val);
			if (info==-1)
			{
				Treap_insert(x);
				treap_insert(val,x);
			}
			else
			{
				Treap_delete(info);
				treap_delete(val);
				Treap_insert(x);
				treap_insert(val,x);
				Cop(Root[rTot-1],Root[rTot]);
				Cop(root[rtot-1],root[rtot]);
				rTot--;rtot--;
			}
		}
		if (type[0]=='r')
		{
			cin>>name;val=gethash(name);
			int info=treap_inf(val);
			if (info!=-1)
			{
				Treap_delete(info);
				treap_delete(val);
			}
			else
			{
				Cop(Root[rTot+1],Root[rTot]);
				cop(root[rtot+1],root[rtot]);
				rTot++;rtot++;
			}
		}
		if (type[0]=='q')
		{
			cin>>name;val=gethash(name);
			int info=treap_find(val);
			if (info==-1) printf("-1\n"); else Treap_query(info);
			Cop(Root[rTot+1],Root[rTot]);
			cop(root[rtot+1],root[rtot]);
			rTot++;rtot++;
		}
		if (type[0]=='u')
		{
			scanf("%d",&x);
			int tTot=rTot-x,ttot=rtot-x;
			Cop(Root[++rTot],Root[tTot]);
			cop(root[++rtot],root[ttot]);
		}
		fflush(stdout);
	}
	return 0;
}