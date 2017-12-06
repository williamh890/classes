import numpy as np
import matplotlib.pyplot as plt


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

    @property
    def n(self):
        return len(self.x)

    @property
    def s(self):
        top = self.sse
        bot = self.n - 2

        return (top / bot) ** (1 / 2.)

    @property
    def line(self):
        return lambda x: self.b0 + self.b1 * x

    @property
    def s_b1(self):
        return self.s / (s_xx(self.x) ** (1 / 2))

    @property
    def sse(self):
        return s_xx(self.y) - self.b1 * s_xy(self.x, self.y)

    @property
    def sst(self):
        return s_xx(self.y)

    @property
    def r(self):
        return (1 - (self.sse / self.sst)) ** (1 / 2.)

    def scatter(self, plt_name=""):
        x, y = self.x, self.y
        plt.plot(np.unique(x), np.poly1d(np.polyfit(x, y, 1))(np.unique(x)))
        plt.scatter(x, y, alpha=.3)
        plt.show()

        if plt_name != ":":
            plt.savefig(plt_name)

    def overview(self):
        print(f"n = {len(self.x)}")
        print(f"y = {self.b0: 2.3f} + {self.b1: 2.3f}x")

        print(f"s = {self.s}")
        print(f"r^2 = {self.r ** 2}")


def q17():
    x = [99.0, 101.1, 102.7, 103.0, 105.4, 107.0, 108.7,
         110.8, 112.1, 112.4, 113.6, 113.8, 115.1, 115.4, 120.0]
    y = [28.8, 27.9, 27.0, 25.2, 22.8, 21.5, 20.9,
         19.6, 17.1, 18.9, 16.0, 16.7, 13.0, 13.6, 10.8]

    r = LeastSquares(x, y)

    print(f"y = {r.b0: 2.3f} + {r.b1: 2.3f}x")

    print(f"e1 = {28.8 - r.line(99)}")
    print(f"e2 = {27.9 - r.line(101.1)}")

    print(f"s = {r.s}")
    print(f"r^2 = {r.r ** 2}")


def q31():
    x = [635, 644, 711, 708, 836, 820, 810, 870, 856, 923, 878, 937, 948]
    y = [100, 93, 88, 84, 77, 75, 74, 63, 57, 55, 47, 43, 38]

    r = LeastSquares(x, y)

    r.overview()

    print(f"s_b1 = {r.s_b1}")
    print(f"b1 = {r.b1}")
    t = 2.201
    diff = t * r.s_b1
    ci = (r.b1 - diff, r.b1 + diff)
    print(f"ci(95%) = {ci[0]: 2.3f}")


def q34():
    y = [4.55, 4.49, 4.50, 4.47, 4.47, 4.45, 4.40, 4.34, 4.43,
         4.43, 4.42, 4.40, 4.33, 4.44, 4.40, 4.26, 4.32, 4.34]
    x = [4.35, 4.79, 5.57, 5.20, 5.07, 5.79, 5.36, 6.40, 5.66,
         5.90, 6.49, 5.70, 6.49, 6.37, 6.51, 7.88, 6.74, 7.08]

    r = LeastSquares(x, y)
    r.overview()

    t_stat = (r.b1 + 0.05) / r.s_b1
    print(f"t_stat = {t_stat}")


if __name__ == "__main__":
    q34()
