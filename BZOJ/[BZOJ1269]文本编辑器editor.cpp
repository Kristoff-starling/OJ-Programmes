#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <stack>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <cmath>
#include <cctype>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

struct Treap
{
	Treap *left,*right;
	int priority,sz;char value;
	int flip;
	void pushdown ()
	{
		if (flip)
		{
			if (left!=NULL) left->flip^=1;
			if (right!=NULL) right->flip^=1;
			flip^=1;
			swap(left,right);
		}
	}
	void update ()
	{
		pushdown(); 
		sz=1;
		if (left!=NULL) sz+=left->sz;
		if (right!=NULL) sz+=right->sz;
	}
}*Root,*res,*croot;
typedef pair<Treap*,Treap*> pii;

int n;
string type,s;
int cur_insert=0;

inline int LeftSize(Treap *root)
{
	int ret=1;
	if (root->left!=NULL) ret+=root->left->sz;
	return ret;
}

Treap* Create(char value,int priority,Treap *left,Treap *right)
{
	res=new Treap;
	res->value=value;res->priority=priority;
	res->left=left;res->right=right;res->flip=0;
	res->update();
	return res;
}

pii split(Treap *root,int value)
{
	if (root==NULL) return make_pair<Treap*,Treap*>(NULL,NULL);
	root->pushdown();
	if (LeftSize(root)<=value)
	{
		pii splitted=split(root->right,value-LeftSize(root));
		root->right=splitted.x;
		root->update();
		return mp(root,splitted.y);
	}
	else
	{
		pii splitted=split(root->left,value);
		root->left=splitted.y;
		root->update();
		return mp(splitted.x,root);
	}
}

Treap* add(Treap *root,char value,int pos,int priority)
{
	if (root==NULL) return Create(value,priority,NULL,NULL);
	root->pushdown();
	if (priority>root->priority)
	{
		pii splitted=split(root,pos);
		root=Create(value,priority,splitted.x,splitted.y);
		root->update();return root;
	}
	else
	{
		if (LeftSize(root)<=pos)
			root->right=add(root->right,value,pos-LeftSize(root),priority);
		else 
			root->left=add(root->left,value,pos,priority);
		root->update();
		return root;
	}
}

Treap* merge (Treap *root1,Treap *root2)
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

string ss;
inline void getstring(int len)
{
	//getchar();
	//gets(ss+1);
	getline(cin,ss);
}

void Treap_insert()
{
	int len=getint();
	getstring(len);
	//cout<<ss<<endl;
	//cout<<s<<endl;
	//puts(ss+1);
	//return;
	croot=NULL;
	for (int i=0;i<=len-1;i++)
	{
		//cout<<i<<endl;
		int prior=rand();
	    croot=add(croot,ss[i],i+1,prior);
	}
	pii splitted=split(Root,cur_insert);
	Root=merge(merge(splitted.x,croot),splitted.y);
}

void Treap_delete(int len)
{
	pii sx=split(Root,cur_insert);
	pii sy=split(sx.y,len);
	Root=merge(sx.x,sy.y);
}

void Treap_rotate(int len)
{
	pii sx=split(Root,cur_insert);
	pii sy=split(sx.y,len);
	sy.x->flip^=1;
	Root=merge(merge(sx.x,sy.x),sy.y);
}

char Treap_get()
{
	pii sx=split(Root,cur_insert);
	pii sy=split(sx.y,1);
	char res=sy.x->value;
	Root=merge(merge(sx.x,sy.x),sy.y);
	return res;
}

int main ()
{
	//freopen ("result.out","w",stdout);
	srand(1968);
	n=getint();
	Root=NULL;
	int i,x,prior,len,cnt=0;
	while (n--)
	{
		cin>>type;
		if (type[0]=='M') cur_insert=getint();
		if (type[0]=='I') Treap_insert();
		if (type[0]=='D')
		{
			len=getint();
			Treap_delete(len);
		}
		if (type[0]=='R')
		{
			len=getint();
			Treap_rotate(len);
		}
		
		if (type[0]=='G')
		{
			if (cnt) cout<<endl;
			++cnt;
			//printf("%c",Treap_get());
			cout<<Treap_get();
		}
		if (type[0]=='P') --cur_insert;
		if (type[0]=='N') ++cur_insert;
	}
	return 0;
}
