class MyCircularQueue:

    def __init__(self, k: int):
        self.q = []
        self.len = k


    def enQueue(self, value: int) -> bool:
        if len(self.q) == self.len: return False
        self.q.append(value)
        return True


    def deQueue(self) -> bool:
        if len(self.q) == 0: return False
        self.q = self.q[1:]
        return True


    def Front(self) -> int:
        if len(self.q) == 0: return -1
        return self.q[0]


    def Rear(self) -> int:
        if len(self.q) == 0: return -1
        return self.q[-1]


    def isEmpty(self) -> bool:
        return True if len(self.q) == 0 else False

    def isFull(self) -> bool:
        return True if len(self.q) == self.len else False