import numpy as np


def q42():
    o = [1, 1, 2, 2, 3, 3]
    e = range(1,7)
    s = [29.7, 33.6, 30.2, 33.6, 25.8, 29.7]
    s_copy = s[:]

    unordered_pairs = set([])

    for s1 in s:
        for s2 in s_copy:
            if s1 == s2:
                continue

            unordered_pairs.add(frozenset([s1,s2]))

    averages = []
    for pair in unordered_pairs:
        total = 0
        for val in pair:
            total += val
        averages.append(total / len(pair))


    probs = [p / 30. for p in [4, 2, 6, 4, 8, 4, 2]]
    print(sum(s) / len(s))

if __name__ == "__main__":
    q42()
