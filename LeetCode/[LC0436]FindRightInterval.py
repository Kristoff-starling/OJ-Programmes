class Solution:
    def findRightInterval(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        res = [-1] * n
        starts = sorted([s, i] for i, (s, _)in enumerate(intervals))
        for i, (_, ed) in enumerate(intervals):
            pos = bisect_left(starts, ed, key = lambda x: x[0])
            if pos < n: res[i] = starts[pos][1]
        return res