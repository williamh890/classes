import math
from statistics import stdev

import numpy as np
import matplotlib.pyplot as plt


def nu(s1, m, s2, n):
    r1, r2 = (s1**2) / m, (s2**2) / n
    top = (r1 + r2)**2
    bot = ((r1**2) / (m - 1)) + ((r2**2) / (n - 1))

    return math.floor(top / bot)


def t_stat(xbar, ybar, delta, s1, m, s2, n):
    top = xbar - ybar - delta
    bot = ((s1**2 / m) + (s2**2 / n))**(1 / 2)

    return top / bot


def q19():
    s1, m, s2, n = 5.03, 6., 5.38, 6.
    xbar, ybar, alpha, delta = 115.7, 129.3, 0.01, -10.

    dof = nu(s1, m, s2, n)
    stat = t_stat(xbar, ybar, delta, s1, m, s2, n)

    print(f"t_stat = {stat}")
    print(f"Nu = {dof}")

    def q20():
        mid = xbar - ybar
        t_val = 2.260
        diff = t_val * ((s1**2 / m) + (s2**2 / n))**(1 / 2)
        ci = (mid - diff, mid + diff)

        print(f"CI = {ci}")

    q20()


def q32():

    s1, m, s2, n = 117., 28., 72., 16.
    xbar, ybar, alpha, delta = 801., 780., .01, 0.

    dof = nu(s1, m, s2, n)
    print(f"Nu = {dof}")

    def a():
        mid = xbar - ybar
        t_val = 2.704
        diff = t_val * ((s1**2 / m) + (s2**2 / n))**(1 / 2)
        ci = (mid - diff, mid + diff)

        print(f"CI = {ci}")

    def b():
        stat = t_stat(xbar, ybar, delta, s1, m, s2, n)

        print(f"t_stat = {stat}")

    a(), b()


def d_stat(d, s, n, delta=0):
    return (d - delta) / (s / n**(1 / 2))


def q36():
    u = [36.4, 55.0, 51.5, 38.7, 43.2, 48.8, 25.6, 49.8]
    a = [28.5, 20.0, 46.0, 34.5, 36.5, 52.5, 26.5, 46.5]
    delta = 0

    D = [-ui + ai for ui, ai in zip(a, u)]
    n = len(D)
    d_bar = sum(D) / n

    dof = len(u) - 1
    s = stdev(D)

    test = d_stat(d_bar, s, n)

    print(f"dBar = {d_bar}")
    print(f"s = {s}")

    print(f"t_stat = {test}")


def q38():
    sli = [30, 35, 40, 25, 20, 30, 35, 62, 40, 51, 25, 42, 33]
    dig = [25, 16, 15, 15, 10, 20, 7, 16, 15, 13, 11, 19, 19]

    data = [sli, dig]

    plt.figure()
    plt.boxplot(data)
    plt.savefig('38a.png')

    D = [s - d for s, d in zip(sli, dig)]
    n = len(D)
    s = stdev(D)
    d_bar = sum(D) / n
    t = 3.055

    diff = t * (s / (n**(1 / 2)))
    ci = (d_bar - diff, d_bar + diff)
    print(f"CI (99%) = {ci}")


def z_stat(p1, m, p2, n, p):
    q = 1 - p

    top = p1 - p2
    bot = (p * q * (1 / m + 1 / n))**(1 / 2)

    return top / bot


def p_calc(x, y, m, n):
    return (x + y) / (m + n)


def q49():
    p1, m, p2, n = 164. / 200, 200, 140. / 200, 200.
    p = p_calc(164., 140., 200., 200.)
    test = z_stat(p1, m, p2, n, p)
    print(f"params = {(p1, m, p2, n)}")

    print(f"z_stat = {test}")


def calc_ci(p1, m, p2, n, z_alpha):
    mid = p1 - p2

    q1, q2 = 1 - p1, 1 - p2
    dif = z_alpha * (((p1 * p1 / m) + (p2 * q2 / n))**(1 / 2))

    print(mid, dif)
    return (mid - dif, mid + dif)


def q52():
    p1, m, p2, n = 224. / 395, 395., 126 / 266., 266.
    z_alpha = 1.96

    ci = calc_ci(p1, m, p2, n, z_alpha)
    print(f"CI = {ci}")


def q54():
    p1, m, p2, n = 18. / 56, 56., 12. / 51, 51.
    p = p_calc(18., 12., 56., 51.)
    test = z_stat(p1, m, p2, n, p)
    print(f"params = {(p1, m, p2, n)}")

    print(f"z_stat = {test}")


if __name__ == "__main__":
    q54()
