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

int mright[5048];
char s[3000048];
char ans[3000048];
int n,k;
Pair ope[5048];

void doit(int maxright,int ind)
{
	mright[ind+1]=maxright;
	if (ind==0) return;
	if (ope[ind].y>=maxright)
	{
		doit(maxright,ind-1);
		return;
	}
	if (ope[ind].y*2-ope[ind].x+1>=maxright)
	{
		doit(ope[ind].y,ind-1);
		return;
	}
	doit(maxright-(ope[ind].y-ope[ind].x+1),ind-1);
}

struct Treap
{
	Treap *left,*right;
	char ch;int priority;
	int sz;
	void update()
	{
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
}*Root;
typedef pair<Treap*,Treap*> pii;

Treap* Create(char ch,int priority,Treap *left,Treap *right)
{
	Treap *tmp=new Treap;
	tmp->ch=ch;tmp->priority=priority;tmp->left=left;tmp->right=right;
	tmp->update();
	return tmp;
}

inline int LeftSize(Treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

pii split(Treap *root,int key)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
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
		root1->right=merge(root1->right,root2);
		root1->update();
		return root1;
	}
	else
	{
		root2->left=merge(root1,root2->left);
		root2->update();
		return root2;
	}
}

void even_odd_split(Treap *root,Treap *&a,Treap *&b,int nlen)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (LeftSize(root)-1>=nlen)
	{
		even_odd_split(root->left,a,b,nlen);
		return;
	}
	if (LeftSize(root)>=nlen)
	{
		pii splitted;even_odd_split(root->left,splitted.x,splitted.y,nlen-1);
		if (LeftSize(root)&1)
		{
			a=splitted.x;
			b=merge(splitted.y,Create(root->ch,root->priority,NULL,NULL));
		}
		else
		{
			a=merge(splitted.x,Create(root->ch,root->priority,NULL,NULL));
			b=splitted.y;
		}
		return;
	}
	pii splitted1,splitted2;
	even_odd_split(root->left,splitted1.x,splitted1.y,LeftSize(root)-1);
	even_odd_split(root->right,splitted2.x,splitted2.y,nlen-LeftSize(root));
	if (LeftSize(root)&1)
		splitted1.y=merge(splitted1.y,Create(root->ch,root->priority,NULL,NULL));
	else
		splitted1.x=merge(splitted1.x,Create(root->ch,root->priority,NULL,NULL));
	if (LeftSize(root)&1)
	{
		a=merge(splitted1.x,splitted2.y);
		b=merge(splitted1.y,splitted2.x);
	}
	else
	{
		a=merge(splitted1.x,splitted2.x);
		b=merge(splitted1.y,splitted2.y);
	}
}

int cnt=0;
void print(Treap *root)
{
	if (root->left!=NULL) print(root->left);
	printf("%c",root->ch);cnt++;
	if (root->right!=NULL) print(root->right);
}

void Treap_ope(int left,int right,int nlen)
{
	pii splitted1=split(Root,left-1);
	pii splitted2=split(splitted1.y,right-left+1);
	Treap *a,*b;
	even_odd_split(splitted2.x,a,b,nlen);
	Root=merge(merge(merge(merge(splitted1.x,splitted2.x),a),b),splitted2.y);
}

void Delete(Treap *root)
{
	if (root->left!=NULL) Delete(root->left);
	if (root->right!=NULL) Delete(root->right);
	delete root;
}

int main ()
{
	srand(time(NULL));
	int i;
	scanf("%s",s+1);
	k=getint();n=getint();
	for (i=1;i<=n;i++)
		ope[i].x=getint(),ope[i].y=getint();
	doit(k,n);
	int maxright=mright[1];
	Root=NULL;
	for (i=1;i<=maxright;i++)
		Root=merge(Root,Create(s[i],rand(),NULL,NULL));
	for (i=1;i<=n;i++)
	{
		if (ope[i].y>Root->sz) continue;
		Treap_ope(ope[i].x,ope[i].y,ope[i].y-ope[i].x+1);
		if (Root->sz>mright[i+1])
		{
			pii splitted=split(Root,mright[i+1]);
			Root=splitted.x;if (!(rand()%2)) Delete(splitted.y);
		}
	}
	print(Root);printf("\n");
	return 0;
}