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
	Treap *left,*right;
	int value,priority;
}*Root,*res;
typedef pair<Treap*,Treap*> pii;

int n;

inline int myabs(int x)
{
	return x>=0?x:-x;
}

Treap* Create(int key,int priority,Treap *left,Treap *right)
{
	res=new Treap;
	res->left=left;res->right=right;
	res->value=key;res->priority=priority;
	return res;
}

pii split(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	if (root->value<=key)
	{
		pii splitted=split(root->right,key);
		root->right=splitted.x;
		return mp(root,splitted.y);
	}
	else
	{
		pii splitted=split(root->left,key);
		root->left=splitted.y;
		return mp(splitted.x,root);
	}
}

Treap* add(Treap *root,int key,int priority)
{
	if (root==NULL) return Create(key,priority,NULL,NULL);
	if (priority<root->priority)
	{
		pii splitted=split(root,key);
		return Create(key,priority,splitted.x,splitted.y);
	}
	else
	{
		if (root->value<=key)
		{
			root->right=add(root->right,key,priority);
			return root;
		}
		else
		{
			root->left=add(root->left,key,priority);
			return root;
		}
	}
}

int query(Treap *root,int key)
{
	if (root==NULL) return INF;
	if (root->value==key) return 0;
	if (root->value<key)
	{
		int res=query(root->right,key),ret=root->value;
		if (myabs(ret-key)<res) return myabs(ret-key); else return res;
	}
	else
	{
		int res=query(root->left,key),ret=root->value;
		if (myabs(ret-key)<res) return myabs(ret-key); else return res;
	}
}


int main ()
{
	int i,x,prior;
	Root=NULL;
	scanf("%d",&n);
	int ans=0;
	for (i=1;i<=n;i++)
	{
		if (scanf("%d",&x)==EOF) x=0;
		prior=rand();
		if (i==1) ans+=x; else ans+=query(Root,x);
		Root=add(Root,x,prior);
	}
	printf("%d\n",ans);
	return 0;
}
