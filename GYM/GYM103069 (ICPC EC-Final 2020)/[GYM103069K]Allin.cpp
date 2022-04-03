#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
#define x first
#define y second
#define mp make_pair
using namespace std;

enum{HighCard=1, Pair, TwoPairs, Three, Straight, Flush, House, Four, StraightFlush, Royal};

bool rev(pair<int,int> i1, pair<int,int> i2)
{
    if (i1.x!=i2.x) return i1.x>i2.x;
    return i1.y>i2.y;
}

struct Hand
{
    pair<int,int> a[5];
    void arrange() {sort(a,a+5,rev);}
    void print()
    {
        for (int i=0;i<=4;i++)
        printf("%d %d\n",a[i].x,a[i].y);
        puts("----");
    }
    int isRoyalFlush()
    {
        rep(i,1,4) if (a[i].y!=a[0].y) return 0;
        if (a[0].x==14 && a[1].x==13 && a[2].x==12 && a[3].x==11 && a[4].x==10) return 1; else return 0;
    }
    int isStraightFlush()
    {
        rep(i,1,4) if (a[i].y!=a[0].y) return 0;
        if (a[0].x==14 && a[1].x==5 && a[2].x==4 && a[3].x==3 && a[4].x==2) return 5;
        rep(i,0,3) if (a[i+1].x+1!=a[i].x) return 0;
        return a[0].x;
    }
    int isFour()
    {
        if (a[0].x==a[1].x && a[0].x==a[2].x && a[0].x==a[3].x) return a[0].x*16+a[4].x;
        if (a[1].x==a[2].x && a[1].x==a[3].x && a[1].x==a[4].x) return a[1].x*16+a[0].x;
        return 0;
    }
    int isHouse()
    {
        if (a[0].x==a[1].x && a[0].x==a[2].x && a[3].x==a[4].x) return a[0].x*16+a[3].x;
        if (a[0].x==a[1].x && a[2].x==a[3].x && a[2].x==a[4].x) return a[2].x*16+a[0].x;
        return 0;
    }
    int isFlush()
    {
        rep(i,1,4) if (a[i].y!=a[0].y) return 0;
        return a[4].x+a[3].x*16+a[2].x*256+a[1].x*4096+a[0].x*65536;
    }
    int isStraight()
    {
        if (a[0].x==14 && a[1].x==5 && a[2].x==4 && a[3].x==3 && a[4].x==2) return 5;
        rep(i,0,3) if (a[i+1].x+1!=a[i].x) return 0;
        return a[0].x;
    }
    int isThree()
    {
        if (a[0].x==a[1].x && a[0].x==a[2].x) return a[0].x*256+a[3].x*16+a[4].x;
        if (a[1].x==a[2].x && a[1].x==a[3].x) return a[1].x*256+a[0].x*16+a[4].x;
        if (a[2].x==a[3].x && a[2].x==a[4].x) return a[2].x*256+a[0].x*16+a[1].x;
        return 0;
    }
    int isTwoPairs()
    {
        if (a[0].x==a[1].x && a[2].x==a[3].x) return a[0].x*256+a[2].x*16+a[4].x;
        if (a[0].x==a[1].x && a[3].x==a[4].x) return a[0].x*256+a[3].x*16+a[2].x;
        if (a[1].x==a[2].x && a[3].x==a[4].x) return a[1].x*256+a[3].x*16+a[0].x;
        return 0;
    }
    int isPair()
    {
        if (a[0].x==a[1].x) return a[0].x*4096+a[2].x*256+a[3].x*16+a[4].x;
        if (a[1].x==a[2].x) return a[1].x*4096+a[0].x*256+a[3].x*16+a[4].x;
        if (a[2].x==a[3].x) return a[2].x*4096+a[0].x*256+a[1].x*16+a[4].x;
        if (a[3].x==a[4].x) return a[3].x*4096+a[0].x*256+a[1].x*16+a[2].x;
        return 0;
    }
    int isHighCard()
    {
        int res=0;
        rep(i,0,4) res=(res<<16)+a[i].x;
        return res;
    }
    pair<int,int> judgetype()
    {
        arrange();int rt;
        if ((rt=isRoyalFlush())!=0)    return mp(Royal,rt);
        if ((rt=isStraightFlush())!=0) return mp(StraightFlush,rt);
        if ((rt=isFour())!=0)          return mp(Four,rt);
        if ((rt=isHouse())!=0)         return mp(House,rt);
        if ((rt=isFlush())!=0)         return mp(House,rt);
        if ((rt=isStraight())!=0)      return mp(Straight,rt);
        if ((rt=isThree())!=0)         return mp(Three,rt);
        if ((rt=isTwoPairs())!=0)      return mp(TwoPairs,rt);
        if ((rt=isPair())!=0)          return mp(Pair,rt);
        if ((rt=isHighCard())!=0)      return mp(HighCard,rt);
        assert(0);
    }
}my;

pair<int,int> h[2],c[3];

inline int judgenum(char ch)
{
    switch(ch)
    {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return ch-'0';
        case 'T': return 10;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default: assert(0);
    }
}

inline int judgecol(char ch)
{
    switch(ch)
    {
        case 'C': return 1;
        case 'D': return 2;
        case 'H': return 3;
        case 'S': return 4;
        default: assert(0);
    }
}

bool exist[20];

int main ()
{
    int ca;scanf("%d",&ca);
    char s[10];
    while (ca--)
    {
        memset(exist,false,sizeof(exist));
        rep(i,0,1)
        {
            scanf("%s",s);
            h[i].x=judgenum(s[0]);h[i].y=judgecol(s[1]);
            exist[h[i].x]=true;
        }
        rep(i,0,2)
        {
            scanf("%s",s);
            c[i].x=judgenum(s[0]);c[i].y=judgecol(s[1]);
            exist[c[i].x]=true;
        }
        my.a[0]=h[0];my.a[1]=h[1];my.a[2]=c[0];my.a[3]=c[1];my.a[4]=c[2];
        pair<int,int> res=my.judgetype();
        if (res.x==Royal) puts("allin");
        else if (res.x!=StraightFlush) puts("check");
        else
        {
            int lim=res.y;bool allin=true;
            for (int i=lim+1;i<=14;i++)
            {
                int cnt=0;
                for (int j=i;j>=i-4;j--)
                {
                    if (h[0].x==j || h[1].x==j) {cnt=-1;break;}
                    if (!exist[j]) cnt++;
                }
                if (cnt!=-1 && cnt<=4) allin=false;
            }
            puts(allin?"allin":"check");
        }
    }
    return 0;
}