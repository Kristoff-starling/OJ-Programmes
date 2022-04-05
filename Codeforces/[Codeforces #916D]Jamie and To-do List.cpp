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
	Treap *left,*right;
	int val,priority,sz;
	void update()
	{
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
}*Root[100048];
typedef pair<Treap*,Treap*> Pii;
int Tot=0;

Treap* Create(int val,int priority,Treap *left,Treap *right)
{
	Treap *tmp=new Treap;
	tmp->left=left;tmp->right=right;tmp->val=val;tmp->priority=priority;
	tmp->update();
	return tmp;
}

void Cop(Treap *&a,Treap *b)
{
	if (b==NULL) a=NULL; else a=Create(0,rand(),NULL,NULL),*a=*b;
}

int LeftSize(Treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

void Print(Treap *root)
{
	if (root->left!=NULL) Print(root->left);
	cout<<root->val<<' ';
	if (root->right!=NULL) Print(root->right);
}

void Split(Treap *root,Treap *&a,Treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (root->val>=key)
	{
		Cop(b,root);
		Split(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		Cop(a,root);
		Split(root->right,a->right,b,key);
		a->update();
	}
}

void Split2(Treap *root,Treap *&a,Treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (LeftSize(root)>key)
	{
		Cop(b,root);
		Split2(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		Cop(a,root);
		Split2(root->right,a->right,b,key-LeftSize(root));
		a->update();
	}
}

void Merge(Treap *root1,Treap *root2,Treap *&res)
{
	if (root1==NULL) {res=root2;return;}
	if (root2==NULL) {res=root1;return;}
	if (root1->priority<=root2->priority)
	{
		Cop(res,root1);
		Merge(root1->right,root2,res->right);
	}
	else
	{
		Cop(res,root2);
		Merge(root1,root2->left,res->left);
	}
	res->update();
}

void Treap_insert(int val)
{
	Pii splitted;Split(Root[Tot],splitted.x,splitted.y,val);
	Treap *tmp=NULL;Root[++Tot]=NULL;
	Merge(splitted.x,Create(val,rand(),NULL,NULL),tmp);
	Merge(tmp,splitted.y,Root[Tot]);
}

void Treap_delete(int val)
{
	Pii splitted;Split(Root[Tot],splitted.x,splitted.y,val);
	Pii splitted2;Split2(splitted.y,splitted2.x,splitted2.y,1);
	Root[++Tot]=NULL;
	Merge(splitted.x,splitted2.y,Root[Tot]);
}

void Treap_query(int val)
{
	Pii splitted;Split(Root[Tot],splitted.x,splitted.y,val);
	int res=0;if (splitted.x!=NULL) res+=splitted.x->sz;
	printf("%d\n",res);
}

struct treap
{
	treap *left,*right;
	Pair val;int info;int priority;int sz;
	void update()
	{
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
}*root[100048];
typedef pair<treap*,treap*> pii;
int tot=0;

treap* create(Pair val,int info,int priority,treap *left,treap *right)
{
	treap *tmp=new treap;
	tmp->left=left;tmp->right=right;tmp->val=val;tmp->info=info;tmp->priority=priority;
	tmp->update();
	return tmp;
}

void cop(treap *&a,treap *b)
{
	if (b==NULL) a=NULL; else a=create(mp(0,0),0,rand(),NULL,NULL),*a=*b;
}

int leftsize(treap *root)
{
	int res=1;
	if (root->left!=NULL) res+=root->left->sz;
	return res;
}

void print(treap *root)
{
	if (root->left!=NULL) print(root->left);
	cout<<root->val.x<<' '<<root->val.y<<' '<<root->info<<"----";
	if (root->right!=NULL) print(root->right);
}

void split(treap *root,treap *&a,treap *&b,Pair key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (root->val>=key)
	{
		cop(b,root);
		split(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		cop(a,root);
		split(root->right,a->right,b,key);
		a->update();
	}
}

void split2(treap *root,treap *&a,treap *&b,int key)
{
	if (root==NULL)
	{
		a=NULL;b=NULL;
		return;
	}
	if (leftsize(root)>key)
	{
		cop(b,root);
		split2(root->left,a,b->left,key);
		b->update();
	}
	else
	{
		cop(a,root);
		split2(root->right,a->right,b,key-leftsize(root));
		a->update();
	}
}

void merge(treap *root1,treap *root2,treap *&res)
{
	//cout<<"^"<<endl;
	if (root1==NULL) {res=root2;return;}
	if (root2==NULL) {res=root1;return;}
	if (root1->priority<=root2->priority)
	{
		cop(res,root1);
		merge(root1->right,root2,res->right);
	}
	else
	{
		cop(res,root2);
		merge(root1,root2->left,res->left);
	}
	res->update();
}

int treap_find(Pair val)
{
	pii splitted;split(root[tot],splitted.x,splitted.y,val);
	pii splitted2;split2(splitted.y,splitted2.x,splitted2.y,1);
	if (splitted2.x==NULL || splitted2.x->val!=val) return -1;
	return splitted2.x->info;
}

void treap_insert(Pair val,int info)
{
	pii splitted;split(root[tot],splitted.x,splitted.y,val);
	//cout<<"&"<<endl;
	root[++tot]=NULL;treap *tmp=NULL;
	merge(splitted.x,create(val,info,rand(),NULL,NULL),tmp);
	merge(tmp,splitted.y,root[tot]);
}

void treap_delete(Pair val)
{
	pii splitted;split(root[tot],splitted.x,splitted.y,val);
	pii splitted2;split2(splitted.y,splitted2.x,splitted2.y,1);
	root[++tot]=NULL;
	merge(splitted.x,splitted2.y,root[tot]);
}

const int p1=19260817,p2=998244353,p3=1e9+7;
inline Pair gethash(string s)
{
	int i;LL res1=0,res2=0;
	for (i=0;i<int(s.size());i++)
	{
		res1=(res1*p1+s[i])%p2;
		res2=(res2*p1+s[i])%p3;
	}
	return mp(res1,res2);
}

int main ()
{
	int q,x;scanf("%d",&q);string type,name;Pair val;
	Tot=tot=0;Root[0]=NULL;root[0]=NULL;
	while (q--)
	{
		cin>>type;
		if (type[0]=='s')
		{
			cin>>name;scanf("%d",&x);val=gethash(name);
			//cout<<val.x<<' '<<val.y<<endl;
			int info=treap_find(val);
			if (info==-1)
			{
				Treap_insert(x);
				//cout<<"*"<<endl;
				treap_insert(val,x);
				//cout<<"*"<<endl;	
			}
			else
			{
				Treap_delete(info);
				treap_delete(val);
				Treap_insert(x);
				treap_insert(val,x);
				Cop(Root[Tot-1],Root[Tot]);
				cop(root[tot-1],root[tot]);
				Tot--;tot--;
			}
		}
		if (type[0]=='r')
		{
			cin>>name;val=gethash(name);
			int info=treap_find(val);
			if (info!=-1)
			{
				Treap_delete(info);
				treap_delete(val);
			}
			else
			{
				Cop(Root[Tot+1],Root[Tot]);
				cop(root[tot+1],root[tot]);
				Tot++;tot++;
			}
		}
		if (type[0]=='q')
		{
			//Print(Root[Tot]);cout<<endl;print(root[tot]);cout<<endl;
			cin>>name;val=gethash(name);
			//cout<<val.x<<' '<<val.y<<endl;
			int info=treap_find(val);
			if (info==-1) printf("-1\n"); else Treap_query(info);
			Cop(Root[Tot+1],Root[Tot]);
			cop(root[tot+1],root[tot]);
			Tot++;tot++;
		}
		if (type[0]=='u')
		{
			scanf("%d",&x);
			int tTot=Tot-x,ttot=tot-x;
			Cop(Root[++Tot],Root[tTot]);
			cop(root[++tot],root[ttot]);
		}
		fflush(stdout);
	}
	return 0;
}