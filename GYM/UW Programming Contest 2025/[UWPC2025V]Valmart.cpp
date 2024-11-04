#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 2e4 + 10;

int n;
int a[MAXN];

int barcode[20], l[20];
char ch[20];
bool dp[MAXN]; int sol[MAXN];

void print_sol(int pos)
{
    if (pos == 7)
        return;
    int len = l[sol[pos]];
    print_sol(pos - len - 1);
    printf("%c", ch[sol[pos]]);
}

bool match(int l, int r, int id)
{
    if (!(1 <= l && l <= r && r <= n))
        return false;
    int num = 0;
    for (int i = l; i <= r; i++)
        num = num * 10 + a[i];
    return num == barcode[id];
}

int main ()
{
    // freopen("v.in", "r", stdin);
    int ca;
    scanf("%d", &ca);
    barcode[0] = 101011;
    barcode[1] = 1101011;
    barcode[2] = 1001011;
    barcode[3] = 1100101;
    barcode[4] = 1011011;
    barcode[5] = 1101101;
    barcode[6] = 1001101;
    barcode[7] = 1010011;
    barcode[8] = 1101001;
    barcode[9] = 110101;
    barcode[10] = 101101;
    barcode[11] = 1011001;
    l[0] = 6;
    l[1] = 7;
    l[2] = 7;
    l[3] = 7;
    l[4] = 7;
    l[5] = 7;
    l[6] = 7;
    l[7] = 7;
    l[8] = 7;
    l[9] = 6;
    l[10] = 6;
    l[11] = 7;
    ch[0] = '0';
    ch[1] = '1';
    ch[2] = '2';
    ch[3] = '3';
    ch[4] = '4';
    ch[5] = '5';
    ch[6] = '6';
    ch[7] = '7';
    ch[8] = '8';
    ch[9] = '9';
    ch[10] = '-';
    while (ca--)
    {
        scanf("%d", &n);
        int x; 
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &x);
            if (x < 128)
                a[i] = 1;
            else
                a[i] = 0;
        }
        if (n <= 15)
        {
            puts("INVALID");
            continue;
        }
        if (!(match(1, 7, 11) && match(n - 6, n, 11) && a[8] == 0 && a[n - 7] == 0))
        {
            puts("INVALID");
            continue;
        }
        int L = 8, R = n - 8;
        dp[7] = true;
        for (int i = L; i <= R; i++)
        {
            dp[i] = false;
            for (int id = 0; id <= 10; id++)
                if (match(i - l[id] + 1, i, id) && a[i - l[id]] == 0 && dp[i - l[id] - 1])
                {
                    dp[i] = true;
                    sol[i] = id;
                }
        }
        if (!dp[R])
            puts("INVALID");
        else
        {
            print_sol(R);
            puts("");
        }
    }
}
/*
1
31
4 231 7 55 252 253 107 182 76 249 135 5 195 79 99 244 97 119 226 104 248 98 110 247 46 186 80 113 243 136 80
23
113 229 24 4 130 161 44 251 59 224 145 85 28 169 14 161 15 128 98 81 198 227 30
15
13 239 12 8 230 139 19 222 11 154 76 31 218 129 4
30
29 250 39 5 232 135 80 168 118 46 246 116 252 45 60 176 46 219 98 61 134 73 136 4 253 15 86 247 208 76
15
83 249 96 48 213 204 105 184 113 151 42 43 182 250 100
*/