class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        self.x = x_center
        self.y = y_center
        self.r = radius


    def randPoint(self) -> List[float]:
        r = (random.random() ** 0.5) * self.r
        theta = random.uniform(0, 2 * math.pi)
        return [r * math.cos(theta) + self.x, r * math.sin(theta) + self.y]