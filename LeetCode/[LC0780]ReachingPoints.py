class Solution:
    def reachingPoints(self, sx: int, sy: int, tx: int, ty: int) -> bool:
        while tx >= sx and ty >= sy and not (sx == tx and sy == ty):
            if tx >= ty: tx -= max((tx - sx) // ty, 1) * ty
            else: ty -= max((ty - sy) // tx, 1) * tx
        return True if sx == tx and sy == ty else False
    