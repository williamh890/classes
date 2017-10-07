# hw3.py
# William Horn
# Sep 25, 2017

from scipy.stats import binom
import math


def q13():
    pmf = [0.10, 0.15, .20, 0.25, 0.20, 0.06, 0.04]
    lt3 = pmf[:4]
    print(lt3)
    print("3 or less lines in use: {}".format(sum(lt3)))

    print("fewer than 3 lines in use: {}".format(sum(pmf[:3])))
    print("at least 3 lines in use: {}".format(sum(pmf[3:])))
    print("between 2 and 5 lines in use: {}".format(sum(pmf[2:6])))
    print("between two and four are not in use: {}".format(sum(pmf[2:5])))
    print("at least 4 lines are not in use: {}".format(sum(pmf[:3])))


def q21():
    print(list(range(10)))
    pmf = [math.log10(x + (1 / x)) for x in range(1, 10)]

    print("pmf: ")

    for i, v in enumerate(pmf):
        print(" {} = {}".format(i + 1, v))

    print("cdf: ")

    for i, v in enumerate([math.log10(x) for x in range(1, 10)]):
        print(" {} = {}".format(i + 1, v))


def q32():
    X, pX = [16, 18, 20], [0.2, 0.5, 0.3]

    Ex = sum([x * px for x, px in zip(X, pX)])
    print("E(X) = {}".format(Ex))

    print("E(X^2) = {}".format(Ex_2))

    print("V(X) = {}".format(Ex_2 - Ex**2))

    Ehx = sum([(x * 70 - 650) * px for x, px in zip(X, pX)])
    print("E(h(x)) = {}".format(Ehx))

    Vhx = sum([((x * 70 - 650) - 624)**2 * px for x, px in zip(X, pX)])
    print("V(h(x)) = {}".format(Vhx))

    Efx = sum([(1 - 0.008 * x) * px for x, px in zip(X, pX)])
    print("E(1-0.008X) = {}".format(Efx))

    print("E(X-0.008X^2) = {}".format(Ex - 0.008 * Ex_2))


def ncr(n, r):
    if r > n:
        raise RuntimeError("r cannot be > n (r = {}, n = {})".format(r, n))

    f = math.factorial
    return f(n) / f(r) / f(n - r)


class Poisson(object):
    def __init__(self, mu):
        self.mu = mu

    def __call__(self, x):
        return math.e**( -self.mu ) * self.mu**x / math.factorial(x)


class Binomial(object):
    def __init__(self, n, p):
        self.p = p
        self.n = n

    def __call__(self, x):
        return ncr(self.n, x) * (self.p)**x * (1 - self.p)**(self.n - x)

    @property
    def expected_val(self):
        return self.p * self.n

    @property
    def varience(self):
        return self.p * self.n * (1 - self.p)

    @property
    def std_dev(self):
        return math.sqrt(self.varience)


def q33():
    px = [x / 15 for x in [1, 2, 3, 4, 3, 2]]

    n3 = 1 / 15 + 2 * 2 / 15 + 3 * 12 / 15
    print("If 3 magazines are bought: {}".format(n3))
    g = 4 * (41 / 15) - 6
    print("Profit: {}".format(g))

    n4 = 1 / 15 + 2 * 2 / 15 + 3 * 3 / 15 + 4 * 9 / 15
    print("If 4 magazines are bought: {}".format(n4))

    g = 4 * (n4) - 8
    print("Profit: {}".format(g))


def q48():
    X = Binomial(25, 0.05)

    pxle3 = sum([X(x) for x in range(4)])
    print("P(x <= 3) = {}".format(pxle3))

    plt3 = sum([X(x) for x in range(3)])
    print("P(x < 3) = {}".format(plt3))

    pxge4 = sum([X(x) for x in range(4, 26)])
    print("P(X >= 4) = {}".format(pxge4))

    p1lexle3 = sum([X(x) for x in range(1, 4)])
    print("P(1 <= x <= 3) = {}".format(p1lexle3))

    print("E(X) = {}".format(X.expected_val))
    print("stdXdev(X) = {}".format(X.std_dev))
    X2 = Binomial(50, 0.05)

    non_with_allergies = X2(0)
    print("nwa = {}".format(non_with_allergies))


def q57():
    X = Binomial(10, 0.9 * 0.9)

    print("P(x=9) = {}".format(X(9) + X(10)))


def q82():
    X = Poisson(0.2)

    print("P(x=1) = {}".format(-X(1) + X(0)))


if __name__ == "__main__":
    q82()
