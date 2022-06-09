class Solution:
    def __init__(self, rects: List[List[int]]):
        self.rects = rects
        self.sum = [0]
        for a, b, x, y in rects:
            self.sum.append(self.sum[-1] + (x - a + 1) * (y - b + 1))
    def pick(self) -> List[int]:
        index = randrange(self.sum[-1])
        recindex = bisect_right(self.sum, index) - 1
        a, b, x, y = self.rects[recindex]
        da, db = (index - self.sum[recindex]) // (y - b + 1), (index - self.sum[recindex]) % (y - b + 1)
        return [a + da, b + db]