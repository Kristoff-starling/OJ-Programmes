class Solution:
    def findKthNumber(self, m: int, n: int, k: int) -> int:
        if k == 1: return 1
        l, r, ans = 2, k, 0
        while l <= r:
            mid, cnt1, cnt2 = (l + r) // 2, 0, 0
            for i in range(1, min(mid+1, m+1)):
                cnt1 += min((mid - 1) // i, n)
                cnt2 += min(mid // i, n)
            if cnt1 < k and cnt2 >= k: return mid
            if cnt2 >= k: r = mid - 1
            else: l = mid + 1
        return ans