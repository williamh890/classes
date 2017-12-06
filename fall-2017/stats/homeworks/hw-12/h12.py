def s_xy(x, y):
    assert len(x) == len(y)

    n = len(x)
    return sum([xi * yi for xi, yi in zip(x, y)]) - (sum(x) * sum(y) / n)


def s_xx(x):
    n = len(x)

    return sum([xi**2 for xi in x]) - (sum(x) ** 2 / n)


def mean(vals):
    return sum(vals) / len(vals)


class LeastSquares:
    def __init__(self, x, y):
        assert len(x) == len(y)

        self.x = x
        self.y = y

    @property
    def b0(self):
        return mean(self.y) - self.b1 * mean(self.x)

    @property
    def b1(self):
        return s_xy(self.x, self.y) / s_xx(self.x)


def q17():
    x = [99.0, 101.1, 102.7, 103.0, 105.4, 107.0, 108.7,
         110.8, 112.1, 112.4, 113.6, 113.8, 115.1, 115.4, 120.0]
    y = [28.8, 27.9, 27.0, 25.2, 22.8, 21.5, 20.9,
         19.6, 17.1, 18.9, 16.0, 16.7, 13.0, 13.6, 10.8]

    r = LeastSquares(x, y)

    print(f"y = {r.b0: 2.3f} + {r.b1: 2.3f}x")


if __name__ == "__main__":
    q17()
