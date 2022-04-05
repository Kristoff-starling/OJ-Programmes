#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LFIN=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=5e5;

namespace splay
{
	struct node
	{
		int val,ch[2],father,sz,cnt;
		inline void clean() {sz=cnt=father=val=ch[0]=ch[1]=0;}
	}tree[MAXN+48];int tot=0,root;
	inline void print(int cur)
	{
		if (tree[cur].ch[0]) print(tree[cur].ch[0]);
		cout<<tree[cur].val<<endl;
		if (tree[cur].ch[1]) print(tree[cur].ch[1]);
	}
	inline void update(int cur) {if (cur) tree[cur].sz=tree[cur].cnt+tree[tree[cur].ch[0]].sz+tree[tree[cur].ch[1]].sz;}
	inline void rotate(int x)
	{
		int y=tree[x].father,z=tree[y].father;
		int k=(tree[y].ch[1]==x);
		tree[z].ch[tree[z].ch[1]==y]=x;
		tree[y].ch[k]=tree[x].ch[k^1];
		tree[x].ch[k^1]=y;
		tree[x].father=z;tree[y].father=x;tree[tree[y].ch[k]].father=y;
		update(y);update(x);
	}
	inline void splay(int x,int target)
	{
		while (tree[x].father!=target)
		{
			int y=tree[x].father,z=tree[y].father;
			if (z!=target)
				((tree[z].ch[1]==y)^(tree[y].ch[1]==x))?rotate(x):rotate(y);
			rotate(x);
		}
		if (!target) root=x;
	}
	inline int find(int val)
	{
		int cur=root,res=0;
		for (;;)
		{
			if (tree[cur].val==val) {res+=tree[tree[cur].ch[0]].sz;splay(cur,0);break;}
			if (val<tree[cur].val)
			{
				if (!tree[cur].ch[0]) break;
				cur=tree[cur].ch[0];
			}
			else
			{
				res+=tree[tree[cur].ch[0]].sz+tree[cur].cnt;
				if (!tree[cur].ch[1]) break;
				cur=tree[cur].ch[1];
			}
		}
		return res;
	}
	inline int findx(int k)
	{
		int cur=root;
		for (;;)
		{
			if (tree[tree[cur].ch[0]].sz>=k) {cur=tree[cur].ch[0];continue;}
			if (tree[tree[cur].ch[0]].sz+tree[cur].cnt>=k) return tree[cur].val;
			k-=tree[tree[cur].ch[0]].sz;k-=tree[cur].cnt;
			cur=tree[cur].ch[1];
		}
	}
	inline void insert(int val)
	{
		if (!root)
		{
			root=++tot;
			tree[root].ch[0]=tree[root].ch[1]=0;
			tree[root].sz=tree[root].cnt=1;tree[root].val=val;
			return;
		}
		int cur=root,k;
		while (tree[cur].val!=val)
		{
			k=(val>tree[cur].val);
			if (tree[cur].ch[k]) cur=tree[cur].ch[k]; else break;
		}
		if (tree[cur].val==val)
			tree[cur].cnt++,tree[cur].sz++;
		else
		{
			int cc=cur;tree[cur].ch[k]=++tot;cur=tot;
			tree[cur].val=val;tree[cur].cnt=tree[cur].sz=1;
			tree[cur].ch[0]=tree[cur].ch[1]=0;tree[cur].father=cc;
		}
		splay(cur,0);
	}
	inline int find_pre(int val)
	{
		if (!tree[root].ch[0]) return -2147483647;
		int cur=tree[root].ch[0];
		while (tree[cur].ch[1]) cur=tree[cur].ch[1];
		return cur;
	}
	inline int find_nxt(int val)
	{
		if (!tree[root].ch[1]) return 2147483647;
		int cur=tree[root].ch[1];
		while (tree[cur].ch[0]) cur=tree[cur].ch[0];
		return cur;
	}
	inline void del(int val)
	{
		find(val);	
		if (tree[root].cnt>1)
		{
			tree[root].cnt--;tree[root].sz--;
			return;
		}
		if (!tree[root].ch[0] && !tree[root].ch[1])
		{
			tree[root].clean();root=0;
			return;
		}
		if (!tree[root].ch[0] || !tree[root].ch[1])
		{
			int k=(tree[root].ch[1]==0);
			int oldroot=root;root=tree[root].ch[k^1];
			tree[root].father=0;
			tree[oldroot].clean();return;
		}
		int cur=find_pre(val);splay(cur,root);
		int oldroot=root;root=tree[root].ch[0];
		tree[root].ch[1]=tree[oldroot].ch[1];tree[tree[root].ch[1]].father=root;
		tree[root].father=0;
		update(root);tree[oldroot].clean();
	}
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int n,op,x;n=getint();int cc=0;
	while (n--)
	{
		++cc;
		op=getint();x=getint();
		if (op==1) splay::insert(x);
		if (op==2) splay::del(x);
		if (op==3) printf("%d\n",splay::find(x)+1);
		if (op==4) printf("%d\n",splay::findx(x));
		if (op==5)
		{
			splay::insert(x);
			printf("%d\n",splay::tree[splay::find_pre(x)].val);
			splay::del(x);
		}
		if (op==6)
		{
			splay::insert(x);
			printf("%d\n",splay::tree[splay::find_nxt(x)].val);
			splay::del(x);
		}
		/*if (cc)
		{
			cout<<"###"<<endl;
			splay::print(splay::root);
			cout<<"###"<<endl;
		}*/
	}
	return 0;
}
