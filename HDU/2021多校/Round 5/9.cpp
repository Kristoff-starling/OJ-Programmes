#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define pb push_back
using namespace std;

const int MAXN=1e6+10;

int n;
vector<int> v[MAXN+48];
int LIM;

int tot,a[MAXN+48],sum[MAXN+48];

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
    }
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template <class T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

struct SegmentTree
{
    LL sum[MAXN<<2],lazy[MAXN<<2],len[MAXN<<2];
    void build(int cur,int l,int r,bool type)
    {
        sum[cur]=lazy[cur]=0;
        if (!type) len[cur]=r-l+1; else len[cur]=1ll*(l+r)*(r-l+1)/2;
        if (l==r) return;
        int mid=(l+r)>>1;
        build(cur<<1,l,mid,type);build(cur<<1|1,mid+1,r,type);
    }
    void pushdown(int cur)
    {
        if (lazy[cur])
        {
            lazy[cur<<1]+=lazy[cur];
            sum[cur<<1]+=lazy[cur]*len[cur<<1];
            lazy[cur<<1|1]+=lazy[cur];
            sum[cur<<1|1]+=lazy[cur]*len[cur<<1|1];
            lazy[cur]=0;
        }
    }
    void pushup(int cur) {sum[cur]=sum[cur<<1]+sum[cur<<1|1];}
    void modify(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            lazy[cur]++;
            sum[cur]+=len[cur];
            return;
        }
        pushdown(cur);
        int mid=(l+r)>>1;
        if (left<=mid) modify(cur<<1,left,right,l,mid);
        if (mid+1<=right) modify(cur<<1|1,left,right,mid+1,r);
        pushup(cur);
    }
    LL query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return sum[cur];
        pushdown(cur);
        int mid=(l+r)>>1;LL res=0;
        if (left<=mid) res+=query(cur<<1,left,right,l,mid);
        if (mid+1<=right) res+=query(cur<<1|1,left,right,mid+1,r);
        pushup(cur);return res;
    }
    void Clear(int cur,int l,int r)
    {
        if (sum[cur]==0) return;
        sum[cur]=lazy[cur]=0;
        if (l==r) return;
        int mid=(l+r)>>1;
        Clear(cur<<1,l,mid);Clear(cur<<1|1,mid+1,r);
    }
}tree1,tree2;

int main ()
{
    // double T=clock();
    // freopen ("a.in","r",stdin);
    // freopen ("a.out","w",stdout);
    int ca;io.Get(ca);
    tree1.build(1,0,MAXN,false);tree2.build(1,0,MAXN,true);
    while (ca--)
    {
        rep(i,0,MAXN) v[i].clear();
        io.Get(n);int x;
        rep(i,1,n) io.Get(x),v[x].pb(i);
        LL ans=0;
        rep(val,0,MAXN)
        {
            tot=0;for (auto item : v[val]) a[++tot]=item;a[0]=0;sum[0]=0;
            if (!tot) continue;
            int BASE=0;int maxn=-1e9;
            rep(i,1,tot)
            {
                sum[i]=sum[i-1]-(a[i]-a[i-1]-1)+1;
                maxn=max(maxn,sum[i]);
                if (sum[i]<BASE) BASE=sum[i];
            }
            if (sum[tot]-(n-a[tot])<BASE) BASE=sum[tot]-(n-a[tot]);
            BASE=-BASE;BASE++;
            // LIM=BASE+maxn;cerr<<LIM<<endl;
            tree1.modify(1,BASE+sum[tot]-(n-a[tot]),BASE+sum[tot],0,MAXN);
            tree2.modify(1,BASE+sum[tot]-(n-a[tot]),BASE+sum[tot],0,MAXN);
            REP(i,tot,1)
            {
                int L=sum[i-1]-(a[i]-a[i-1]-1)+BASE,R=sum[i-1]+BASE;
                LL res=tree1.query(1,R+1,MAXN,0,MAXN);res*=(R-L+1);
                ans+=res;
                LL res1=tree1.query(1,L,R,0,MAXN);res=tree2.query(1,L,R,0,MAXN);
                res-=res1*L;ans+=res;
                if (i!=1) tree1.modify(1,L,R,0,MAXN),tree2.modify(1,L,R,0,MAXN);
            }
            // cerr<<ans<<endl;
            tree1.Clear(1,0,MAXN);tree2.Clear(1,0,MAXN);
        }
        io.Print(ans,'\n');
    }
    io.flush();
    // cerr<<(clock()-T)/CLOCKS_PER_SEC<<endl;
    return 0;
}