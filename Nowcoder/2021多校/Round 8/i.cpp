#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define mp make_pair
#define x first
#define y second
using namespace std;

struct card
{
    int type,num;
    int id() {return (type-1)*13+num-1;}
    void input()
    {
        char s[5];scanf("%s",s+1);
        if (s[1]=='C') type=1;
        if (s[1]=='D') type=2;
        if (s[1]=='H') type=3;
        if (s[1]=='S') type=4;
        if ('2'<=s[2] && s[2]<='9') num=s[2]-'0';
        if (s[2]=='T') num=10;
        if (s[2]=='J') num=11;
        if (s[2]=='Q') num=12;
        if (s[2]=='K') num=13;
        if (s[2]=='A') num=14;
    }
    bool operator < (card &other) const {return num>other.num;}
};

card tocard(int num)
{
    card res;
    res.type=(num-1)/13+1;res.num=num-(res.type-1)*13;
    return res;
}

struct hand
{
    card a[6];
};

bool samenum(hand A,int l,int r)
{
    rep(i,l,r) if (A.a[i].num!=A.a[l].num) return false;
    return true;
}

bool sametype(hand A,int l,int r)
{
    rep(i,l,r) if (A.a[i].type!=A.a[l].type) return false;
    return true;
}

int judgetype(hand &A)
{
    sort(A.a+1,A.a+6);
    // royal flush
    if (A.a[1].num==14 && A.a[2].num==13 && A.a[3].num==12 && A.a[4].num==11 && A.a[5].num==10 && sametype(A,1,5)) return 1;
    // straight flush
    if (sametype(A,1,5))
    {
        if (A.a[1].num==14 && A.a[2].num==5 && A.a[3].num==4 && A.a[4].num==3 && A.a[4].num==2)
        {
            card tmp=A.a[1];rep(i,1,4) A.a[i]=A.a[i+1];
            A.a[5]=tmp;
            return 2;
        }
        bool f=true;
        rep(i,1,4) if (A.a[i].num!=A.a[i+1].num+1) {f=false;break;}
        if (f) return 2;
    }
    // four of a kind
    if (samenum(A,1,4)) return 3;
    if (samenum(A,2,5))
    {
        card tmp=A.a[1];rep(i,1,4) A.a[i]=A.a[i+1];A.a[5]=tmp;
        return 3;
    }
    // full house
    if (samenum(A,1,3) && samenum(A,4,5)) return 4;
    if (samenum(A,1,2) && samenum(A,3,4))
    {
        card tmp1=A.a[1],tmp2=A.a[2];
        rep(i,1,3) A.a[i]=A.a[i+2];A.a[4]=tmp1;A.a[5]=tmp2;
        return 4;
    }
    // flush
    if (A.a[1].num>A.a[2].num && A.a[2].num>A.a[3].num && A.a[3].num>A.a[4].num && A.a[4].num>A.a[5].num)
    {
        if (sametype(A,1,5)) return 5;
    }
    // straight
    if (A.a[1].num==14 && A.a[2].num==5 && A.a[3].num==4 && A.a[4].num==3 && A.a[4].num==2)
    {
        card tmp=A.a[1];
        rep(i,1,4) A.a[i]=A.a[i+1];
        A.a[5]=tmp;
        return 6;
    }
    {
        bool f=true;
        rep(i,1,4) if (A.a[i].num!=A.a[i+1].num) {f=false;break;}
        if (f) return 6;
    }
    // three of a kind
    if (samenum(A,1,3)) return 7;
    if (samenum(A,2,4))
    {
        card tmp=A.a[1];
        rep(i,1,3) A.a[i]=A.a[i+1];
        A.a[4]=tmp;
        return 7;
    }
    if (samenum(A,3,5))
    {
        card tmp1=A.a[1],tmp2=A.a[2];
        rep(i,1,3) A.a[i]=A.a[i+2];
        A.a[4]=tmp1;A.a[5]=tmp2;
        return 7;
    }
    // two pairs
    if (A.a[1].num==A.a[2].num && A.a[3].num==A.a[4].num) return 8;
    if (A.a[1].num==A.a[2].num && A.a[4].num==A.a[5].num)
    {
        card tmp=A.a[3];
        rep(i,3,4) A.a[i]=A.a[i+1];
        A.a[5]=tmp;
        return 8;
    }
    if (A.a[2].num==A.a[3].num && A.a[4].num==A.a[5].num)
    {
        card tmp=A.a[1];
        rep(i,1,4) A.a[i]=A.a[i+1];
        A.a[5]=tmp;
        return 8;
    }
    // one pair
    if (A.a[1].num==A.a[2].num) return 9;
    if (A.a[2].num==A.a[3].num)
    {
        card tmp=A.a[1];
        A.a[1]=A.a[2];A.a[2]=A.a[3];A.a[3]=tmp;
        return 9;
    }
    if (A.a[3].num==A.a[4].num)
    {
        card tmp1=A.a[1],tmp2=A.a[2];
        A.a[1]=A.a[3];A.a[2]=A.a[4];A.a[3]=tmp1;A.a[4]=tmp2;
        return 9;
    }
    if (A.a[4].num==A.a[5].num)
    {
        card tmp1=A.a[4],tmp2=A.a[5];
        for (int i=5;i>=3;i--) A.a[i]=A.a[i-2];
        A.a[1]=tmp1;A.a[2]=tmp2;
        return 9;
    }
    return 10;
}

bool cmp(hand A,hand B)
{
    int t1=judgetype(A),t2=judgetype(B);
    if (t1!=t2) return t1<t2;
    rep(i,1,5)
    {
        if (A.a[i].num>B.a[i].num) return true;
        if (A.a[i].num<B.a[i].num) return false;
    }
    return false;
}

bool cmp(hand A,int t1,hand B,int t2)
{
    if (t1!=t2) return t1<t2;
    rep(i,1,5)
    {
        if (A.a[i].num>B.a[i].num) return true;
        if (A.a[i].num<B.a[i].num) return false;
    }
    return false;
}

struct Set
{
    card a[8];
    pair<int,hand> querymax()
    {
        int t=11;hand res,cur;int tot;
        rep(i,1,6) rep(j,i+1,7)
        {
            tot=0;
            rep(k,1,7) if (k!=i && k!=j) cur.a[++tot]=a[k];
            int tmp=judgetype(cur);
            if (cmp(cur,tmp,res,t)) t=tmp,res=cur;
        }
        return mp(t,res);
    }
};

card my[3],pub[6];

int mark[100];

long long C(int x,int y)
{
    long long res=1;
    rep(i,x-y+1,x) res=res*i;
    rep(i,1,y) res=res/i;
    return res;
}

pair<int,int> vv[10048];int tt;

int main ()
{
    my[1].input();my[2].input();rep(i,1,5) pub[i].input();
    rep(i,1,2) mark[my[i].id()]=1;rep(i,1,5) mark[pub[i].id()]=1;
    Set tmp;rep(i,1,2) tmp.a[i]=my[i];rep(i,1,5) tmp.a[2+i]=pub[i];
    pair<int,hand> My=tmp.querymax();
    rep(i,1,51) rep(j,i+1,52) if (!mark[i] && !mark[j])
    {
        tmp.a[1]=tocard(i);tmp.a[2]=tocard(j);
        pair<int,hand> cur=tmp.querymax();
        if (cmp(My.y,My.x,cur.y,cur.x)) vv[++tt]=mp(i,j);
    }
    long long div=C(45,2)*C(43,2)*C(41,2)*C(39,2)*C(37,2);
}