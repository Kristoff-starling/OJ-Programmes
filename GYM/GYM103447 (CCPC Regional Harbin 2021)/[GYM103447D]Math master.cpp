#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

LL A,B;
int abit[48],bbit[48],lena,lenb;

inline LL mygcd(LL x,LL y) {return y==0?x:mygcd(y,x%y);}

struct pair_hash
{
    size_t operator () (pair<LL,LL> const &pr) const {
        size_t h1 = hash<LL>()(pr.first);
        size_t h2 = hash<LL>()(pr.second);
        return h1 ^ h2;
    }
};

unordered_set<pair<LL,LL>, pair_hash> sa, sb;

void getbit(LL val, int bit[],int &len)
{
    int pt=0;
    while (val!=0) bit[++pt]=val%10,val/=10;
    len=pt;
}

void init_set(LL ori, int bit[], int len, unordered_set<pair<LL,LL>, pair_hash> *s)
{
    LL newval, dn;
    int cnt[10] = {0,0,0,0,0,0,0,0,0,0};

    for (int Mask=0;Mask<(1<<len)-1;Mask++)
    {
        for (int i = 0; i <= 9; i++) cnt[i] = 0;
        newval=0;
        for (int i = len; i >= 1; i--)
            if (Mask>>(i-1)&1) cnt[bit[i]]++;
            else newval=newval*10+bit[i];
        if (newval == 0) continue;
        dn = 0;
        for (int i = 9; i >= 0; i--)
            while (cnt[i]--) dn = dn * 10 + i;

        (*s).insert(make_pair(newval, dn));
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        sa.clear();sb.clear();
        scanf("%lld%lld",&A,&B);
        getbit(A, abit, lena); getbit(B, bbit, lenb);
        init_set(A, abit, lena, &sa); init_set(B, bbit, lenb, &sb);
        LL minn = A;
        for (unordered_set<pair<LL,LL>, pair_hash>::iterator iter = sa.begin(); iter!=sa.end(); iter++)
        {
            LL tmp1 = iter->first, tmp2 = B, tmp3 = A;
            LL g = mygcd(tmp1, tmp3); tmp1 /= g; tmp3 /= g;
            g = mygcd(tmp2, tmp3); tmp2 /= g; tmp3 /= g;
            if (tmp3 != 1) continue;
            if (sb.find(make_pair(tmp1 * tmp2, iter->second))!=sb.end())
                minn = min(minn, iter->first);
        }
        LL tmp1 = minn, tmp2 = B, tmp3 = A;
        LL g = mygcd(tmp1, tmp3); tmp1 /= g; tmp3 /= g;
        g = mygcd(tmp2, tmp3); tmp2 /= g; tmp3 /= g;
        assert(tmp3 == 1);
        printf("%lld %lld\n", minn, tmp1 * tmp2);
    }
    return 0;
}