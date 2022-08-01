class Solution {
    int pre[100048], sz[100048];
    int find_anc(int x) {if (pre[x] != x) pre[x] = find_anc(pre[x]); return pre[x];}
    void update(int x, int y) {x = find_anc(x); y = find_anc(y); pre[x] = y; sz[y] += sz[x];}
    struct node
    {
        int val, pos;
        bool operator < (const node &other) const {return val > other.val;}
    }a[100048];
    int n;
    bool alive[100048];
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        n = int(nums.size());
        for (int i = 0; i < n; i++) a[i+1].val = nums[i], a[i+1].pos = i+1;
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) pre[i] = i, sz[i] = 1;
        int ptr = 1;
        for (int length = 1; length <= n; length++)
        {
            int t = threshold / length;
            while (ptr <= n && a[ptr].val > t)
            {
                alive[a[ptr].pos] = true;
                if (alive[a[ptr].pos-1]) update(a[ptr].pos, a[ptr].pos-1);
                if (alive[a[ptr].pos+1]) update(a[ptr].pos, a[ptr].pos+1);
                if (sz[find_anc(a[ptr].pos)] >= length) return length;
                ptr++;
            }
        }
        return -1;
    }
};