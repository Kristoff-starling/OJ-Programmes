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
	int val,priority;
	int lmax,rmax,maxn,sz,sum;
	int flip;bool flushed;
	void update()
	{
		sz=1+(left==NULL?0:left->sz)+(right==NULL?0:right->sz);
		lmax=-INF;
		if (left!=NULL)
		{
			lmax=max(lmax,left->lmax);
			lmax=max(lmax,left->sum+val);
			if (right!=NULL) lmax=max(lmax,left->sum+val+right->lmax);
		}
		else
		{
			lmax=val;
			if (right!=NULL) lmax=max(lmax,val+right->lmax);
		}
		rmax=-INF;
		if (right!=NULL)
		{
			rmax=max(rmax,right->rmax);
			rmax=max(rmax,right->sum+val);
			if (left!=NULL) rmax=max(rmax,right->sum+val+left->rmax);
		}
		else
		{
			rmax=val;
			if (left!=NULL) rmax=max(rmax,val+left->rmax);
		}
		maxn=-INF;
		if (left!=NULL) maxn=max(maxn,left->maxn);
		if (right!=NULL) maxn=max(maxn,right->maxn);
		maxn=max(maxn,val+(left==NULL?0:max(left->rmax,0))+(right==NULL?0:max(right->lmax,0)));
		sum=val+(left==NULL?0:left->sum)+(right==NULL?0:right->sum);
	}
	void maintain_flip()
	{
		flip^=1;
		swap(lmax,rmax);
	}
	void maintain_flush(int x)
	{
		flushed=true;val=x;
		lmax=rmax=maxn=max(val,val*sz);
		sum=val*sz;
	}
	void pushdown()
	{
		if (flip)
		{
			if (left!=NULL) left->maintain_flip();
			if (right!=NULL) right->maintain_flip();
			flip^=1;swap(left,right);
		}
		if (flushed)
		{
			if (left!=NULL) left->maintain_flush(val);
			if (right!=NULL) right->maintain_flush(val);
			flushed=false;
		}
	}
}*Root,*res,*tmp;
typedef pair<Treap*,Treap*> pii;

int n,q;

Treap* Create(int val,int priority,Treap *left,Treap *right)
{
	res=new Treap;
	res->val=val;res->priority=priority;res->left=left;res->right=right;
	res->flushed=false;res->flip=0;
	res->update();
	return res;
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
	int i,x;
	tmp=NULL;
	if (len==0) return;
	for (i=1;i<=len;i++)
	{
		scanf("%d",&x);
		tmp=merge(tmp,Create(x,rand(),NULL,NULL));
	}
	pii splitted=split(Root,pos);
	Root=merge(merge(splitted.x,tmp),splitted.y);
}

void Delete(Treap* root)
{
	if (root->left!=NULL) Delete(root->left);
	if (root->right!=NULL) Delete(root->right);
	delete root;
}

void Treap_delete(int pos,int len)
{
	if (len==0) return;
	pii splitted=split(Root,pos-1);
	pii splitted2=split(splitted.y,len);
	Root=merge(splitted.x,splitted2.y);
	Delete(splitted2.x);
}

void Treap_flush(int pos,int len,int c)
{
	if (len==0) return;
	pii splitted=split(Root,pos-1);
	pii splitted2=split(splitted.y,len);
	splitted2.x->maintain_flush(c);
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

void Treap_rotate(int pos,int len)
{
	if (len==0) return;
	pii splitted=split(Root,pos-1);
	pii splitted2=split(splitted.y,len);
	splitted2.x->maintain_flip();
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

void Treap_getsum(int pos,int len)
{
	if (len==0)
	{
		printf("0\n");
		return;
	}
	pii splitted=split(Root,pos-1);
	pii splitted2=split(splitted.y,len);
	printf("%d\n",splitted2.x->sum);
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

int main ()
{
	int pos,len,c;char type[20];
	scanf("%d%d",&n,&q);
	Root=NULL;
	Treap_insert(0,n);
	while (q--)
	{
		scanf("%s",type+1);
		if (!(type[1]=='M' && type[3]=='X')) scanf("%d%d",&pos,&len);
		if (type[1]=='M' && type[3]=='K') scanf("%d",&c);
		if (type[1]=='I') Treap_insert(pos,len);
		if (type[1]=='D') Treap_delete(pos,len);
		if (type[1]=='M' && type[3]=='K') Treap_flush(pos,len,c);
		if (type[1]=='R') Treap_rotate(pos,len);
		if (type[1]=='G') Treap_getsum(pos,len);
		if (type[1]=='M' && type[3]=='X') printf("%d\n",Root->maxn);
	}
	return 0;
}