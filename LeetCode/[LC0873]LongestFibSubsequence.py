class Solution:
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        table, n, ans = {}, len(arr), 0
        for num in arr: table[num] = 1
        for i in range(n):
            for j in range(i+1, n):
                cur, v1, v2 = 2, arr[i], arr[j]
                while True:
                    v3 = v1 + v2
                    if v3 in table:
                        cur += 1
                        v2, v1 = v3, v2
                    else: break
                ans = max(ans, cur)
        if ans == 2: ans = 0
        return ans