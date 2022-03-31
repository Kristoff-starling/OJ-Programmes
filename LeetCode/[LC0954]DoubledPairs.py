class Solution:
    def canReorderDoubled(self, arr: List[int]) -> bool:
        cnt = Counter(arr)
        if cnt[0] % 2 == 1: return False
        for val in sorted(cnt, key=abs):
            if cnt[val * 2] < cnt[val]: return False
            cnt[val * 2] -= cnt[val]
        return True