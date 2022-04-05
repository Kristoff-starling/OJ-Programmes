#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=5e4;

int n,q;
int a[MAXN+48];

namespace SegmentTreap
{
	/*---Treap---*/
	struct Treap
	{
		int lson,rson;
		int val,priority,sz;
	}tree[MAXN*50];int tot=0;
	int root[MAXN*50];
	inline void update(int cur) {tree[cur].sz=tree[tree[cur].lson].sz+tree[tree[cur].rson].sz+1;}
	inline int Create(int left,int right,int val,int priority)
	{
		++tot;tree[tot].lson=left;tree[tot].rson=right;
		tree[tot].val=val;tree[tot].priority=priority;
		update(tot);return tot;
	}
	//left: <val; right: >=val
	inline Pair split1(int root,int val)
	{
		if (!root) return mp(0,0);
		if (tree[root].val>=val)
		{
			Pair splitted=split1(tree[root].lson,val);
			tree[root].lson=splitted.y;update(root);
			return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split1(tree[root].rson,val);
			tree[root].rson=splitted.x;update(root);
			return mp(root,splitted.y);
		}
	}
	//left: <=val; right:>val
	inline Pair split2(int root,int val)
	{
		if (!root) return mp(0,0);
		if (tree[root].val<=val)
		{
			Pair splitted=split2(tree[root].rson,val);
			tree[root].rson=splitted.x;update(root);
			return mp(root,splitted.y);
		}
		else
		{
			Pair splitted=split2(tree[root].lson,val);
			tree[root].lson=splitted.y;update(root);
			return mp(splitted.x,root);
		}
	}
	//left: 1~k; right: k+1~n
	inline Pair split3(int root,int k)
	{
		if (!root) return mp(0,0);
		int leftsz=tree[tree[root].lson].sz+1;
		if (leftsz>k)
		{
			Pair splitted=split3(tree[root].lson,k);
			tree[root].lson=splitted.y;update(root);
			return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split3(tree[root].rson,k-leftsz);
			tree[root].rson=splitted.x;update(root);
			return mp(root,splitted.y);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1+root2;
		if (tree[root1].priority<=tree[root2].priority)
		{
			tree[root1].rson=merge(tree[root1].rson,root2);
			update(root1);return root1;
		}
		else
		{
			tree[root2].lson=merge(root1,tree[root2].lson);
			update(root2);return root2;
		}
	}
	inline void treap_insert(int &root,int val)
	{
		int root1=Create(0,0,val,rand());
		Pair splitted=split1(root,val);
		root=merge(merge(splitted.x,root1),splitted.y);
	}
	inline void treap_delete(int &root,int val)
	{
		Pair splitted=split1(root,val);Pair splitted2=split3(splitted.y,1);
		root=merge(splitted.x,splitted2.y);
	}
	inline int treap_xrank(int &root,int val)
	{
		Pair splitted=split1(root,val);int res=tree[splitted.x].sz;
		root=merge(splitted.x,splitted.y);return res;
	}
	inline int treap_pre(int &root,int val)
	{
		Pair splitted=split1(root,val);
		if (!tree[splitted.x].sz)
		{
			root=merge(splitted.x,splitted.y);
			return -INF;
		}
		Pair splitted2=split3(splitted.x,tree[splitted.x].sz-1);
		int res=tree[splitted2.y].val;
		root=merge(merge(splitted2.x,splitted2.y),splitted.y);
		return res;
	}
	inline int treap_nxt(int &root,int val)
	{
		Pair splitted=split2(root,val);
		if (!tree[splitted.y].sz)
		{
			root=merge(splitted.x,splitted.y);
			return INF;
		}
		Pair splitted2=split3(splitted.y,1);
		int res=tree[splitted2.x].val;
		root=merge(merge(splitted.x,splitted2.x),splitted2.y);
		return res;
	}
	/*---Segment Tree---*/
	inline void build(int cur,int left,int right)
	{
		root[cur]=0;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline void Insert(int cur,int pos,int val,int l,int r)
	{
		treap_insert(root[cur],val);
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Insert(cur<<1,pos,val,l,mid); else Insert(cur<<1|1,pos,val,mid+1,r);
	}
	inline void Delete(int cur,int pos,int val,int l,int r)
	{
		treap_delete(root[cur],val);
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) Delete(cur<<1,pos,val,l,mid); else Delete(cur<<1|1,pos,val,mid+1,r);
	}
	inline int query_xrank(int cur,int left,int right,int val,int l,int r)
	{
		if (left<=l && r<=right) return treap_xrank(root[cur],val);
		int mid=(l+r)>>1,res=0;
		if (left<=mid) res+=query_xrank(cur<<1,left,right,val,l,mid);
		if (mid+1<=right) res+=query_xrank(cur<<1|1,left,right,val,mid+1,r);
		return res;
	}
	inline int query_pre(int cur,int left,int right,int val,int l,int r)
	{
		if (left<=l && r<=right) return treap_pre(root[cur],val);
		int res=-INF,mid=(l+r)>>1;
		if (left<=mid) res=max(res,query_pre(cur<<1,left,right,val,l,mid));
		if (mid+1<=right) res=max(res,query_pre(cur<<1|1,left,right,val,mid+1,r));
		return res;
	}
	inline int query_nxt(int cur,int left,int right,int val,int l,int r)
	{
		if (left<=l && r<=right) return treap_nxt(root[cur],val);
		int res=INF,mid=(l+r)>>1;
		if (left<=mid) res=min(res,query_nxt(cur<<1,left,right,val,l,mid));
		if (mid+1<=right) res=min(res,query_nxt(cur<<1|1,left,right,val,mid+1,r));
		return res;
	}
}

/*namespace SegmentTree
{
	int lson[MAXN*30*15],rson[MAXN*30*15],cnt[MAXN*30*15],tot;
	inline void build(int cur,int l,int r)
	{
		tot=max(tot,cur);
		lson[cur]=rson[cur]=cnt[cur]=0;
		if (l!=r)
		{
			int mid=(l+r)>>1;
			build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
		}
	}
	inline void updatey(int &cur,int pos,int delta,int l,int r)
	{
		if (!cur) cur=++tot,cnt[cur]=0;
		cnt[cur]+=delta;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) updatey(lson[cur],pos,delta,l,mid); else updatey(rson[cur],pos,delta,mid+1,r);
	}
	inline void updatex(int cur,int pos,int val,int delta,int l,int r)
	{
		updatey(cur,val,delta,0,1e8);
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) updatex(cur<<1,pos,val,delta,l,mid); else updatex(cur<<1|1,pos,val,delta,mid+1,r);
	}
	vector<int> sgt;
	inline void query_sgt(int cur,int left,int right,int l,int r)
	{
		if (left<=l && r<=right) {sgt.pb(cur);return;}
		int mid=(l+r)>>1;
		if (left<=mid) query_sgt(cur<<1,left,right,l,mid);
		if (mid+1<=right) query_sgt(cur<<1|1,left,right,mid+1,r);
	}
	inline int query_k(int left,int right,int k)
	{
		sgt.clear();query_sgt(1,left,right,1,n);
		int l=0,r=1e8,mid,i;
		while (l<r)
		{
			mid=(l+r)>>1;int sum=0;
			for (i=0;i<int(sgt.size());i++) sum+=cnt[lson[sgt[i]]];
			if (sum>=k)
			{
				r=mid;
				for (i=0;i<int(sgt.size());i++) sgt[i]=lson[sgt[i]];
			}
			else
			{
				k-=sum;
				for (i=0;i<int(sgt.size());i++) sgt[i]=rson[sgt[i]];
				l=mid+1;
			}
		}
		return l;
	}
}*/

int main ()
{
	int i;n=getint();q=getint();
	SegmentTreap::build(1,1,n);/*SegmentTree::build(1,1,n);*/
	SegmentTreap::tree[0].sz=SegmentTreap::tree[0].lson=SegmentTreap::tree[0].rson=0;
	for (i=1;i<=n;i++) a[i]=getint(),SegmentTreap::Insert(1,i,a[i],1,n)/*,SegmentTree::updatex(1,i,a[i],1,1,n)*/;
	int op,l,r,k,L,R,mid,ans;
	while (q--)
	{
		op=getint();
		if (op!=3) l=getint(),r=getint(),k=getint(); else l=getint(),k=getint();
		if (op==1) printf("%d\n",SegmentTreap::query_xrank(1,l,r,k,1,n)+1);
		//if (op==2) printf("%d\n",SegmentTree::query_k(l,r,k));
		if (op==2)
		{
			L=0;R=1e8;ans=0;
			while (L<=R)
			{
				mid=(L+R)>>1;
				if (SegmentTreap::query_xrank(1,l,r,mid,1,n)+1<=k) ans=mid,L=mid+1; else R=mid-1;
			}
			printf("%d\n",ans);
		}
		if (op==3)
		{
			SegmentTreap::Delete(1,l,a[l],1,n);
			//SegmentTree::updatex(1,l,a[l],-1,1,n);
			a[l]=k;
			SegmentTreap::Insert(1,l,a[l],1,n);
			//SegmentTree::updatex(1,l,a[l],1,1,n);
		}
		if (op==4) printf("%d\n",SegmentTreap::query_pre(1,l,r,k,1,n));
		if (op==5) printf("%d\n",SegmentTreap::query_nxt(1,l,r,k,1,n));
	}
	return 0;
}
