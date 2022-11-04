#include <bits/stdc++.h>
using namespace std;

string s;

string process(int l, int r)        // process(l, r) 用于展开 l 到 r 的字符串
{
    if (l > r) return "";
    if (s[l] == '[')                // 遇到 []，递归展开 [] 里面的内容
    {
        int cnt = 1, pt = l;
        while (cnt != 0)
        {
            pt++;
            if (s[pt] == '[') cnt++;
            if (s[pt] == ']') cnt--;
        }
        return process(l + 1, pt - 1) + process(pt + 1, r);
    }
    else if (isdigit(s[l]))         // 遇到数字：递归获取后面的内容，根据数字重复
    {
        int repeat = 0, pt = l;
        while (isdigit(s[pt]))
        {
            repeat = repeat * 10 + s[pt] - '0';
            pt++;
        }
        string tmp = process(pt, r), res = "";
        while (repeat--) res += tmp;
        return res;
    }
    else
        return string(1, s[l]) + process(l + 1, r);  // 普通情况：把第一个字符截下来，
                                                     //         后面的部分递归处理
}

int main ()
{
    cin >> s;
    cout << process(0, int(s.size()) - 1);
    return 0;
}