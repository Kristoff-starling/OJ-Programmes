class Solution {
    int val[100048], n, ll, rr, l, r;
public:
    bool isPalindrome(ListNode* head) {
        n = 0;
        while (head != NULL) val[++n] = head->val, head = head->next;
        l = 1; r = n;
        while (l <= r && val[l] == val[r]) l++, r--;
        if (l > r) return true;
        ll = l + 1; rr = r;
        while (ll <= rr && val[ll] == val[rr]) ll++, rr--;
        if (ll > rr) return true;
        ll = l; rr = r - 1;
        while (ll <= rr && val[ll] == val[rr]) ll++, rr--;
        if (ll > rr) return true;
        return false;
    }
};