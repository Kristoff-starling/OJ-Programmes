#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;

char s[148];int tot,cnt;

bool isvowel(char ch) {return ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U';}

int halfprint(int lim,bool flag)
{
    int curcnt=0;int res=-1;
    rep(i,1,tot)
    {
        if (isalpha(s[i])) curcnt++;
        if (curcnt==lim && res==-1) res=i;
        if (!isalpha(s[i])) putchar(s[i]);
        else if (curcnt<=lim || (isvowel(s[i]) && flag)) putchar(s[i]);
        else putchar('.');
    }
    puts("");
    return res;
}

int main ()
{
    char ch;int cnt=0;while ((ch=getchar())!='\n') s[++tot]=ch;
    rep(i,1,tot) if (isalpha(s[i])) cnt++,putchar('.'); else putchar(s[i]); puts("");
    int pos=halfprint(int((double)cnt/3.0+0.5),0);
    int vcnt=0;rep(i,pos+1,tot) vcnt+=isvowel(s[i]);
    if (vcnt==0) halfprint(int((double)cnt*2/3.0+0.5),0); else halfprint(int((double)cnt/3.0+0.5),1);
    return 0;
}