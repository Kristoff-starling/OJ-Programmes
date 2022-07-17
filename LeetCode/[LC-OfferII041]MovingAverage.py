class MovingAverage:
    def __init__(self, size: int):
        self.size = size
        self.sum = 0
        self.q = []
    def next(self, val: int) -> float:
        self.q.append(val)
        self.sum += val
        if len(self.q) > self.size:
            dv = self.q.pop(0)
            self.sum -= dv
        return self.sum / len(self.q)