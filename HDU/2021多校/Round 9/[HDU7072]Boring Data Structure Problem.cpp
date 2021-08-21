#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

struct node
{
    int val,nxt,prev;
};

int BASE;

namespace Deque
{
    int head,tail,mid,lcnt,rcnt;node q[11000048];
    void init() {head=tail=mid=0;lcnt=rcnt=0;}
    void Create(int x,int nv) {q[x].prev=q[x].nxt=0;q[x].val=nv;}
    int push_front(int nv)
    {
        if (head==0)
        {
            head=tail=mid=BASE;
            q[head].nxt=q[head].prev=0;q[head].val=nv;
            lcnt=rcnt=0;
            return head;
        }
        Create(head-1,nv);
        q[head].prev=head-1;q[head-1].nxt=head;head--;lcnt++;
        if (lcnt-rcnt>=2)
        {
            mid=q[mid].prev;
            lcnt--;rcnt++;
        }
        return head;
    }
    int push_back(int nv)
    {
        if (head==0)
        {
            head=tail=mid=BASE;
            q[head].nxt=q[head].prev=0;q[head].val=nv;
            lcnt=rcnt=0;
            return head;
        }
        Create(tail+1,nv);
        q[tail].nxt=tail+1;q[tail+1].prev=tail;tail++;rcnt++;
        if (lcnt<rcnt)
        {
            mid=q[mid].nxt;
            lcnt++;rcnt--;
        }
        return tail;
    }
    void del(int x)
    {
        if (head==tail)
        {
            head=tail=0;
            return;
        }
        if (x==head)
        {
            head=q[head].nxt;
            q[head].prev=0;lcnt--;
            if (lcnt<rcnt) mid=q[mid].nxt,lcnt++,rcnt--;
            return;
        }
        if (x==tail)
        {
            tail=q[tail].prev;
            q[tail].nxt=0;rcnt--;
            if (lcnt-rcnt>=2) mid=q[mid].prev,lcnt--,rcnt++;
            return;
        }
        if (x==mid)
        {
            if (lcnt==rcnt) mid=q[mid].nxt,rcnt--; else mid=q[mid].prev,lcnt--;
            int pp=q[x].prev,nn=q[x].nxt;
            q[pp].nxt=nn;q[nn].prev=pp;
            return;
        } 
        int pp=q[x].prev,nn=q[x].nxt;
        q[pp].nxt=nn;q[nn].prev=pp;
        if (x<mid) lcnt--; else rcnt--;
        if (lcnt-rcnt>=2) mid=q[mid].prev,lcnt--,rcnt++;
        if (lcnt<rcnt) mid=q[mid].nxt,lcnt++,rcnt--;
    }
    int query() {return q[mid].val;}
}

char seq[10000001][1];
int pos[10000001];

int main ()
{
    int q;scanf("%d",&q);
    int c1=0,c2=0;
    rep(i,1,q)
    {
        scanf("%s",seq[i]);
        if (seq[i][0]=='L') c1++;
        if (seq[i][0]=='R') c2++;
        if (seq[i][0]=='G') scanf("%d",&pos[i]);
    }
    BASE=c1+10;int cnt=0;
    Deque::init();
    rep(i,1,q)
    {
        if (seq[i][0]=='L')
        {
            cnt++;
            pos[cnt]=Deque::push_front(cnt);
        }
        if (seq[i][0]=='R')
        {
            cnt++;
            pos[cnt]=Deque::push_back(cnt);
        }
        if (seq[i][0]=='G')
        {
            Deque::del(pos[pos[i]]);
        }
        if (seq[i][0]=='Q') printf("%d\n",Deque::query());
    }
    return 0;
}