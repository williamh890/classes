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

    Ex_2 = sum([x**2 * px for x, px in zip(X, pX)])
    print("E(X^2) = {}".format(Ex_2))

    print("V(X) = {}".format(Ex_2 - Ex**2))

    Ehx = sum([(x * 70 - 650) * px for x, px in zip(X, pX)])
    print("E(h(x)) = {}".format(Ehx))

    Vhx = sum([((x * 70 - 650) - 624)**2 * px for x, px in zip(X, pX)])
    print("V(h(x)) = {}".format(Vhx))

    Efx = sum([(1 - 0.008 * x) * px for x, px in zip(X, pX)])
    print("E(1-0.008X) = {}".format(Efx))

    print("E(X-0.008X^2) = {}".format(Ex - 0.008*Ex_2))


if __name__ == "__main__":
    q32()
