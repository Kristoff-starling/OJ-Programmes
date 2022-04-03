class NumArray {
    #define LOWBIT(x) ((x) & (-x))
    int c[100048], a[100048], n;
public: 
    void update(int index, int val) {
        index++;
        int oldval = a[index]; a[index] = val;
        while (index <= n) c[index] += val - oldval, index += LOWBIT(index);
    }
    int query(int x)
    {
        int rt = 0;
        while (x > 0) rt += c[x], x ^= LOWBIT(x);
        return rt;
    }
    int sumRange(int left, int right) {
        left++; right++;
        return query(right) - query(left - 1);
    }
    NumArray(vector<int>& nums) {
        n = int(nums.size());
        for (int i = 1; i <= n; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) a[i] = 0, update(i - 1, nums[i-1]);
    }
};