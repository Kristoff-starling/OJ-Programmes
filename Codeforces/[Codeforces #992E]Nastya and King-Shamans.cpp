#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int 
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rlen,wlen;
	fastio () {rlen=wlen=0;}
	inline char Getchar()
	{
		if (rlen==S) rlen=0,fread(rbuf,1,S,stdin);
		return rbuf[rlen++];
	}
	template <class T> inline void Get(T &x)
	{
		T res=0;char ch;bool f;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=res;
	}
	inline void flush() {fwrite(wbuf,1,wlen,stdout);rlen=0;}
	inline void Writechar(char ch)
	{
		wbuf[wlen++]=ch;
		if (wlen==S) flush();
	}
	template <class T> inline void Print(T res,char ch)
	{
		char s[48];int pt;
		if (res==0)
		{
			pt=1;
			s[1]='0';
		}
		else
		{
			bool f=true;if (res<0) f=false,res=-res;
			pt=0;while (res) s[++pt]=res%10+'0',res/=10;
			if (!f) s[++pt]='-';
		}
		while (pt>=1) Writechar(s[pt--]);
		Writechar(ch);
	}
}io;

const int MAXN=2e5;

int n,q;
int a[MAXN+48];

namespace SegmentTree
{
	struct node
	{
		int left,right;
		int maxn;LL sum;
	}tree[MAXN*4];
	inline void pushup(int cur)
	{
		tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
		tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
			pushup(cur);
		}
		else
		{
			tree[cur].maxn=tree[cur].sum=a[left];
		}
	}
	inline void update(int cur,int pos,int newval)
	{
		if (tree[cur].left==tree[cur].right)
		{
			tree[cur].maxn=tree[cur].sum=newval;
			return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) update(cur<<1,pos,newval); else update(cur<<1|1,pos,newval);
		pushup(cur);
	}
	inline LL querysum(int cur,int left,int right)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
		LL res=0;	
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) res+=querysum(cur<<1,left,right);
		if (mid+1<=right) res+=querysum(cur<<1|1,left,right);
		return res;
	}
	inline int findpos(int cur,int left,int right,LL need)
	{
		if (left>right) return -1;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			if (tree[cur].maxn<need) return -1;
			if (tree[cur].left==tree[cur].right) return tree[cur].left;
			if (tree[cur<<1].maxn>=need) return findpos(cur<<1,left,right,need); else return findpos(cur<<1|1,left,right,need);
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		int res=-1;
		if (left<=mid) res=findpos(cur<<1,left,right,need);
		if (res!=-1) return res;
		if (mid+1<=right) res=findpos(cur<<1|1,left,right,need);
		return res;
	}
}

inline int solve()
{
	LL cursum=SegmentTree::querysum(1,1,1);int lastpos=1;
	if (!cursum) return 1;
	for (;;)
	{
		int pos=SegmentTree::findpos(1,lastpos+1,n,cursum);
		if (pos==-1) return -1;
		if (SegmentTree::querysum(1,pos,pos)==SegmentTree::querysum(1,1,pos-1)) return pos;
		cursum=SegmentTree::querysum(1,1,pos);
		lastpos=pos;
	}
}

int main ()
{
	io.Get(n);io.Get(q);
	for (register int i=1;i<=n;i++) io.Get(a[i]);
	SegmentTree::build(1,1,n);
	while (q--)
	{
		register int pos,x;
		io.Get(pos);io.Get(x);
		SegmentTree::update(1,pos,x);
		io.Print(solve(),'\n');
	}
	io.flush();return 0;
}
