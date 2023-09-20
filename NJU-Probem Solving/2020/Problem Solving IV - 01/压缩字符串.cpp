#include <bits/stdc++.h>
using namespace std;

char s[3000048];int tot,stot,curnum;
int sta1[3000048],sta2[3000048];

int main ()
{
    char ch;
    while ((ch=getchar())!='\n')
    {
        if (ch=='{')
            sta1[++stot]=curnum,sta2[stot]=tot,curnum=0;
        else if (ch=='}')
        {
            int cnt=sta1[stot]-1,l=sta2[stot],r=tot;stot--;
            while (cnt--) for (int j=l;j<r;++j) s[tot++]=s[j];
        }
        else if (isdigit(ch)) curnum=curnum*10+ch-'0';
        else s[tot++]=ch;
    }
    for (int i=0;i<tot;i++) printf("%c",s[i]);
    return 0;
}