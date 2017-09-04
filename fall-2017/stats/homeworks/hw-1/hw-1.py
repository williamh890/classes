# hw-1.py
# William Horn
# Homework 1

import numpy as np
import matplotlib.pyplot as plt


def question12():
    partical_freqs = [5, 15, 27, 34, 22, 14, 7, 2, 4, 1]

    partical_samples = []

    for num, freq in zip(np.arange(3.25, 8.0, 0.5), partical_freqs):
        print("{}: {}".format(num, freq))
        partical_samples += [num for _ in range(freq)]

    print(partical_samples)

    plt.hist(partical_samples, histtype="bar")

    plt.xlabel("ceo2 partical size (nm)")
    plt.ylabel("freqency")
    plt.title("partical size histogram")
    plt.savefig('question12c.png')


def group_stems(_list):
    stems = set(s for s, l in _list)
    stems_leafs = {s: [] for s in stems}

    for s, l in _list:
        stems_leafs[s].append(l)

    sorted_leafs = sorted(stems_leafs.items(), key=lambda x: x[0])
    return sorted_leafs


def steam_leaf(_list):
    _list.sort()
    _list = [(t / 10, t % 10) for t in _list]

    return group_stems(_list)


def print_stem_and_leaf(sal_plot, label=""):
    print(label)
    for stem, leafs in sal_plot:
        row = "{} |  ".format(stem)

        for leaf in leafs:
            row += "{} ".format(leaf)
        print(row)
    print("")


def question15():
    american_runtimes = [94, 90, 95, 93, 128, 95, 125, 91, 104, 116, 162,
                         102, 90, 110, 92, 113, 116, 90, 97, 103, 95, 120, 109, 91, 138]
    french_runtimes = [123, 116, 90, 158, 122, 119, 125, 90, 96, 94, 137,
                       102, 105, 106, 95, 125, 122, 103, 96, 111, 81, 113, 128, 93, 92]

    french, american = steam_leaf(
        french_runtimes), steam_leaf(american_runtimes)

    print_stem_and_leaf(american, "America Runtimes")
    print_stem_and_leaf(french, "French Runtimes")


if __name__ == "__main__":
    question15()
