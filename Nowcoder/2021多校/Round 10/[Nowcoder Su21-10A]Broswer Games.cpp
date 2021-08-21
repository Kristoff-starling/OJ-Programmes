#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;

int n;
struct node
{
    char s[101];int id;
    bool operator < (const node &other) const
    {
        int pt=1;
        while (s[pt]==other.s[pt]) pt++;
        return s[pt]<other.s[pt];
    }
}a[MAXN+48];

int pos[MAXN+48],lcp[MAXN+48];

int query_lcp(char X[],char Y[])
{
    int res=0,pt=1;
    while (X[pt]==Y[pt]) res++,pt++;
    return res;
}

int ST[MAXN+48][18],Log[MAXN+48];

void init_ST()
{
    rep(i,1,n-1) ST[i][0]=lcp[i];
    rep(j,1,17) rep(i,1,n-1)
    {
        ST[i][j]=ST[i][j-1];
        if (i+(1<<(j-1))<=n-1) ST[i][j]=min(ST[i][j],ST[i+(1<<(j-1))][j-1]);
    }
    Log[1]=0;rep(i,2,n) Log[i]=Log[i>>1]+1;
}

int query_lcp(int L,int R)
{
    int l=L,r=R,k=r-l+1;
    return min(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
}

int cnt;
int fcnt,asi[256];

int ql[MAXN+48],qr[MAXN+48];

struct Deque_node
{
    int val,prev,nxt;
}qq[MAXN+48];int tot=0;

struct Deque
{
    int head,tail;
    void clear() {head=tail=0;}
    int Create(int nv) {++tot;qq[tot].val=nv;qq[tot].prev=qq[tot].nxt=0;return tot;}
    bool empty() {return head==0;}
    void push_back(int nv)
    {
        int id=Create(nv);
        if (head==0) {head=tail=id;return;}
        qq[tail].nxt=id;qq[id].prev=tail;tail=id;
    }
    void push_front(int nv)
    {
        int id=Create(nv);
        if (head==0) {head=tail=id;return;}
        qq[head].prev=id;qq[id].nxt=head;head=id;
    }
    void pop_back()
    {
        if (head==tail) {head=tail=0;return;}
        tail=qq[tail].prev;qq[tail].nxt=0;
    }
    void pop_front()
    {
        if (head==tail) {head=tail=0;return;}
        head=qq[head].nxt;qq[head].prev=0;
    }
    int front() {return qq[head].val;}
    int back() {return qq[tail].val;}
};

namespace DSU
{
    int pre[MAXN+48],L[MAXN+48],R[MAXN+48];Deque q[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i,L[i]=R[i]=i,q[i].clear();}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y)
    {
        x=find_anc(x);y=find_anc(y);
        R[x]=R[y];pre[y]=x;
        if (q[x].empty()) {q[x]=q[y];return;}
        if (!q[y].empty())
        {
            qq[q[x].tail].nxt=q[y].head;qq[q[y].head].prev=q[x].tail;
            q[x].tail=q[y].tail;
        }
    }
    bool check(int x,int lb,int rb)
    {
        if (lb<=ql[x] && qr[x]<rb) return true;
        return false;
    }
    void doit1(int x,int lb,int rb)
    {
        while (!q[x].empty() && check(q[x].back(),lb,rb)) cnt++,q[x].pop_back();
    }
    void doit2(int x,int lb,int rb)
    {
        while (!q[x].empty() && check(q[x].front(),lb,rb)) cnt++,q[x].pop_front();
    }
}

bool visited[MAXN+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%s",a[i].s+1),a[i].id=i;
    fcnt=0;
    rep(i,1,n)
    {
        int ch=a[i].s[1];
        if (!asi[ch]) fcnt++;
        asi[ch]++;
    }
    sort(a+1,a+n+1);rep(i,1,n) pos[a[i].id]=i;
    rep(i,1,n-1) lcp[i]=query_lcp(a[i].s,a[i+1].s);
    init_ST();
    rep(i,1,n-1)
    {
        if (i==1 || query_lcp(1,i-1)>=lcp[i]) ql[i]=0;
        int l=1,r=i-1,mid;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if(query_lcp(mid,i-1)>=lcp[i]) r=mid-1; else ql[i]=mid,l=mid+1;
        }
        if (i==n-1 || query_lcp(i+1,n-1)>=lcp[i]) qr[i]=n;
        l=i+1;r=n-1;
        while (l<=r)
        {
            mid=(l+r)>>1;
            if (query_lcp(i+1,mid)>=lcp[i]) l=mid+1; else qr[i]=mid,r=mid-1;
        }
    }
    rep(i,0,n+1) visited[i]=false;
    DSU::init();cnt=0;
    rep(i,1,n-1)
    {
        int p=pos[i];visited[p]=true;
        if (!visited[p-1] && !visited[p+1]) {printf("%d\n",i-cnt);continue;}
        if (visited[p-1] && visited[p+1])
        {
            int lp=DSU::find_anc(p-1),rp=DSU::find_anc(p+1);
            DSU::q[lp].push_back(p-1);DSU::q[rp].push_front(p);
            int lb=DSU::L[lp]-1,rb=DSU::R[rp]+1;
            DSU::doit1(lp,lb,rb);DSU::doit2(rp,lb,rb);
            DSU::update(lp,rp);
            printf("%d\n",i-cnt);continue;
        }
        if (visited[p-1])
        {
            int lp=DSU::find_anc(p-1);
            int lb=DSU::L[lp]-1,rb=p+1;
            DSU::q[lp].push_back(p-1);
            DSU::doit1(lp,lb,rb);
            DSU::R[lp]=p;DSU::pre[p]=lp;
            printf("%d\n",i-cnt);continue;
        }
        assert(visited[p+1]);
        int rp=DSU::find_anc(p+1);
        int lb=p-1,rb=DSU::R[rp]+1;
        DSU::q[rp].push_front(p);
        DSU::doit2(rp,lb,rb);
        DSU::L[rp]=p;DSU::pre[p]=rp;
        printf("%d\n",i-cnt);
    }
    printf("%d\n",fcnt);
    return 0;
}