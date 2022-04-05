#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cctype>
#define LL long long
#define LB long double
#define mp make_pair
#define pb push_back
#define pf push_front 
#define Pair pair<int,int>
#define x first
#define y second
#define LOWBIT(X) x & (-x)
using namespace std;

const int MOD=1e6;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;bool f;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
int Tree_type;

inline int myabs(int x)
{
	return x>=0?x:-x;
}

struct Treap
{
	Treap *left,*right;
	int value,priority;
}*Root,*res;
typedef pair<Treap*,Treap*> pii;

inline int getfinal(int num1,int num2,int key)
{
	if (num1==-1) return num2;
	if (num2==-1) return num1;
	if (key-num1<=num2-key) return num1; else return num2;
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

Treap* Create(int key,int priority,Treap *left,Treap *right)
{
	res=new Treap;
	res->value=key;res->priority=priority;
	res->left=left;res->right=right;
	return res;
}

Treap* add(Treap *root,int key,int priority)
{
	if (root==NULL) return Create(key,priority,NULL,NULL);
	if (priority>root->priority)
	{
		pii splitted=split(root,key);
		return Create(key,priority,splitted.x,splitted.y);
	}
	else
	{
		if (root->value<=key)
			root->right=add(root->right,key,priority);
		else
			root->left=add(root->left,key,priority);
		return root;
	}
}

Treap* merge(Treap *root1,Treap *root2)
{
	if (root1==NULL) return root2;
	if (root2==NULL) return root1;
	if (root1->priority<=root2->priority)
	{
		root1->right=merge(root1->right,root2);
		return root1;
	}
	else
	{
		root2->left=merge(root1,root2->left);
		return root2;
	}
}

Treap* Delete(Treap *root,int key)
{
	if (root==NULL) return NULL;
	if (root->value==key) return merge(root->left,root->right);
	if (root->value<key)
		root->right=Delete(root->right,key);
	else
		root->left=Delete(root->left,key);
	return root;
}

int find_pre(Treap *root,int key)
{
	if (root->value==key) return root->value;
	if (root->value<key)
	{
		int ret=-1;
		if (root->right!=NULL) ret=find_pre(root->right,key);
		return max(root->value,ret);
	}
	else
	{
		int ret=-1;
		if (root->left!=NULL) ret=find_pre(root->left,key);
		return ret;
	}
}

int find_suf(Treap *root,int key)
{
	if (root->value==key) return root->value;
	if (root->value<key)
	{
		int ret=-1;
		if (root->right!=NULL) ret=find_suf(root->right,key);
		return ret;
	}
	else
	{
		int ret=-1;
		if (root->left!=NULL) ret=find_suf(root->left,key);
		if (ret==-1) return root->value; else return ret;
	}
}

int main ()
{
	srand(1968);
	n=getint();
	int type,key,prior,num1,num2,final;
	LL ans=0;
	while (n--)
	{
		type=getint();key=getint();
		if (Root==NULL)
		{
			Tree_type=type;prior=rand();
			Root=add(Root,key,prior);
			continue;
		}
		if (type==Tree_type)
		{
			prior=rand();
			Root=add(Root,key,prior);
		}
		else
		{
			num1=find_pre(Root,key);num2=find_suf(Root,key);
			final=getfinal(num1,num2,key);
			ans=(ans+myabs(final-key))%MOD;Root=Delete(Root,final);
		}
	}
	cout<<ans<<endl;
	return 0;
}
