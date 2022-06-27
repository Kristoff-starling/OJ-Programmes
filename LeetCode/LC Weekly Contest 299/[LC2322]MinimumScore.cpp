const int MAXN = 2000;
class Solution {
    vector<int> v[MAXN + 48];
    int val[MAXN + 48], n;
    pair<int,int> edge[MAXN + 48];int tot;
    int depth[MAXN + 48], xsum[MAXN + 48];
    bool anc[MAXN + 48][MAXN + 48];
    int fa[MAXN + 48];
public:
    void addedge(int x, int y)
    {
        v[x].push_back(y);
        v[y].push_back(x);
        edge[++tot] = make_pair(x, y);
    }
    void dfs(int cur,int father)
    {
        fa[cur] = father;
        depth[cur] = depth[father] + 1;
        xsum[cur] = val[cur];
        for (auto y : v[cur]) if (y != father) dfs(y, cur), xsum[cur] ^= xsum[y];
    }
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        n = int(nums.size());
        int total = 0;
        for (int i = 0; i < n; i++) val[i+1] = nums[i], total ^= nums[i];
        for (auto item : edges)
            addedge(item[0] + 1, item[1] + 1);
        dfs(1, 0);
        for (int i = 1; i <= n; i++)
        {
            int cur = fa[i];
            while (cur) anc[i][cur] = true, cur = fa[cur];
        }
        int ans = 1000000000;
        for (int i = 1; i <= tot - 1; i++)
            for (int j = i + 1; j <= tot; j++)
            {
                int x1 = edge[i].first, y1 = edge[i].second;
                int x2 = edge[j].first, y2 = edge[j].second;
                if (depth[x1] < depth[y1]) swap(x1, y1);
                if (depth[x2] < depth[y2]) swap(x2, y2);
                if (depth[x1] < depth[x2]) swap(x1, x2), swap(y1, y2);
                int sum1 = xsum[x1], sum2, sum3;
                if (anc[x1][x2]) sum2 = xsum[x2] ^ xsum[x1]; else sum2 = xsum[x2];
                sum3 = total ^ sum1 ^ sum2;
                int maxn = max(max(sum1, sum2), sum3);
                int minn = min(min(sum1, sum2), sum3);
                ans = min(ans, maxn - minn);
            }
        return ans;
    }
};