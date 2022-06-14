class Solution {
public:
    int bel[10], n, ans = 100000000;
    int cnt[10];
    vector<int> c;
    void check(int k)
    {
        int maxn = cnt[1];
        for (int i = 2; i <= k; i++) maxn = max(maxn, cnt[i]);
        ans = min(ans, maxn);
    }
    void dfs(int step, int k)
    {
        if (step == n+1)
        {
            check(k);
            return;
        }
        for (int i = 1; i <= k; i++)
        {
            bel[step] = i;
            cnt[i] += c[step - 1];
            if (cnt[i] < ans) dfs(step + 1, k);
            cnt[i] -= c[step - 1];
        }
    }
    int distributeCookies(vector<int>& cookies, int k) {
        c = cookies;
        n = int(cookies.size());
        dfs(1, k);
        return ans;
    }
};