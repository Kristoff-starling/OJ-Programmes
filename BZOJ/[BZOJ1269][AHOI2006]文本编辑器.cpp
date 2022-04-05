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

int q;
char s[2000048];

struct Treap
{
	Treap *left,*right;
	int priority;
	int flip;char ch;int sz;
	void update()
	{
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
	void pushdown()
	{
		if (flip)
		{
			if (left!=NULL) left->flip^=1;
			if (right!=NULL) right->flip^=1;
			flip^=1;swap(left,right);
		}
	}
}*Root,*res,*tmp;
typedef pair<Treap*,Treap*> pii;

inline int LeftSize(Treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

Treap* Create(int priority,char ch,Treap *left,Treap *right)
{
	res=new Treap;
	res->priority=priority;res->ch=ch;
	res->left=left;res->right=right;res->flip=0;
	res->update();
	return res;
}

pii split(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	root->pushdown();
	if (LeftSize(root)>key)
	{
		pii splitted=split(root->left,key);
		root->left=splitted.y;
		root->update();
		return mp(splitted.x,root);
	}
	else
	{
		pii splitted=split(root->right,key-LeftSize(root));
		root->right=splitted.x;
		root->update();
		return mp(root,splitted.y);
	}
}

Treap* merge(Treap *root1,Treap *root2)
{
	if (root1==NULL) return root2;
	if (root2==NULL) return root1;
	if (root1->priority<=root2->priority)
	{
		root1->pushdown();
		root1->right=merge(root1->right,root2);
		root1->update();
		return root1;
	}
	else
	{
		root2->pushdown();
		root2->left=merge(root1,root2->left);
		root2->update();
		return root2;
	}
}

void Treap_insert(int pos,int len)
{
	tmp=NULL;
	int i,prior;char ch;
	for (i=1;i<=len;i++)
	{
		ch=getchar();prior=rand();
		tmp=merge(tmp,Create(prior,ch,NULL,NULL));
	}
	pii splitted=split(Root,pos);
	Root=merge(merge(splitted.x,tmp),splitted.y);
}

void Treap_delete(int pos,int len)
{
	pii splitted=split(Root,pos);
	pii splitted2=split(splitted.y,len);
	Root=merge(splitted.x,splitted2.y);
}

void Treap_rotate(int pos,int len)
{
	pii splitted=split(Root,pos);
	pii splitted2=split(splitted.y,len);
	splitted2.x->flip^=1;
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

void Treap_get(int pos)
{
	pii splitted=split(Root,pos);
	pii splitted2=split(splitted.y,1);
	printf("%c\n",splitted2.x->ch);
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

int main ()
{
	srand(time(NULL));
	int pos=0,len;char type[10];
	Root=NULL;pii splitted;
	scanf("%d",&q);
	while (q--)
	{
		scanf("%s",type+1);
		//puts(type+1);
		if (type[1]=='I')
		{
			scanf("%d",&len);getchar();
			Treap_insert(pos,len);
		}
		if (type[1]=='M')
		{
			scanf("%d",&len);
			pos=len;
		}
		if (type[1]=='D')
		{
			scanf("%d",&len);
			Treap_delete(pos,len);
		}
		if (type[1]=='R')
		{
			scanf("%d",&len);
			Treap_rotate(pos,len);
		}
		if (type[1]=='G') Treap_get(pos);
		if (type[1]=='N') pos++;
		if (type[1]=='P') pos--;
	}
	return 0;
}