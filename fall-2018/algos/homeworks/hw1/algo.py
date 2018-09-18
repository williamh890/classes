from collections import deque


def main():
    vals = list(enumerate([35, 35, 35]))
    print(vals)
    sort = comparison_counting_sort(vals)

    print(sort)


def comparison_counting_sort(A):
    n = len(A)
    Count = [0] * n

    print("i, j, A[i], A[j], Count")
    for i in range(n):
        for j in range(i+1, n):
            if A[i][1] < A[j][1]:
                Count[j] += 1
            else:
                Count[i] += 1
            print(f"{i}, {j}, {A[i][1]}, {A[j][1]}, {csv(Count)}")

    S = [0] * n
    for i in range(n):
        S[Count[i]] = A[i]

    return S


def value_delta(A):
    n = len(A)
    minval = A[0]
    maxval = A[0]

    for i in range(1, n):
        if A[i] < minval:
            minval = A[i]
        if A[i] > maxval:
            maxval = A[i]

    return maxval − minval


def csv(l):
    return " ".join(map(str, l))


if __name__ == "__main__":
    main()
