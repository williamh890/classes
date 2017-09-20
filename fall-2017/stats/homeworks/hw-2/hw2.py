import numpy as np


def q45():
    vals = np.array([[.082, .106, .008, .004],
                     [.135, .141, .018, .006],
                     [.215, .200, .065, .020]])

    print("P(A) = {}".format(sum(vals[:, 1])))
    print("P(C) = {}".format(sum(vals[2, :])))
    print("P(AnB) = {}".format(vals[2, 1]))

    print("\nP(A|C) = {}".format(vals[2, 1] / sum(vals[:, 1])))
    print("P(C|A) = {}".format(vals[2, 1] / sum(vals[2, :])))
    BcnE1 = sum(vals[0, [0, 1, 3]])
    print("P(BcnE1) = {}".format(BcnE1))
    Bc = sum(vals[:, 0] + vals[:, 1] + vals[:, 3])
    print("P(Bc) = {}".format(Bc))

    print("P(E1|Bc) = {}".format(BcnE1 / Bc))


def q51():
    Ka = 0.08
    Sr = 0.39
    Kam = 0.3

    KanSr = Ka * Sr

    print("P(KanSr) = {}".format(KanSr))
    print("P(KanKam) = {}".format(Ka * Kam))


def q59():
    A1, A2, A3 = 0.4, 0.35, 0.25
    B, C, D = 0.3, 0.6,  0.5

    print("P(A2nB) = {}".format(A2 * C))
    Tf = A1 * B + A2 * C + A3 * D

    print("P(Tf) = {}".format(Tf))

    print("P(A1|Tf) = {}".format((B * A1) / Tf))
    print("P(A2|Tf) = {}".format((C * A2) / Tf))
    print("P(A3|Tf) = {}".format((D * A3) / Tf))


def q62():
    Cb, Cg = 0.15, 0.85
    V, Vc = 0.8, 0.2

    print("P(CbnV) = {}".format(Cb * V))
    print("P(CbnVc) = {}".format(Cb * Vc))
    print("P(CgnV) = {}".format(Cg * V))
    print("P(CgnVc) = {}".format(Cg * Vc))


def q70():
    A, B, C = .6, .4, .2
    AnB = 0.3

    print("P(A|B) = {}".format(AnB / B))

    print("P(AnB) = {} != P(A) * P(B) = {}".format(AnB, A * B))


def q74():
    types = [0.4, 0.11, 0.04, 0.45]

    print("To random picks are O = {}".format(types[-1]**2))

    match = sum([t * t for t in types])
    print("To random picks match = {}".format(match))


if __name__ == "__main__":
    q74()
