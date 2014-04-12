import random

def find(L, k):
    """Finds the number with rank k, and reports recursion depth"""

    a = 0
    b = len(L)-1
    depth = 0
    e = -1
    comp = 0

    while True:
        # Select pivot
        r = random.randint(a, b) # TODO use true randomness

        L[r], L[b] = L[b], L[r] # Swap e and last element
        e = L[b]

        ptr = a
        for i in xrange(a,b):
            comp += 1
            if L[i] < e:
                L[ptr], L[i] = L[i], L[ptr]
                ptr += 1

        # Swap e to its right place
        L[ptr], L[b] = L[b], L[ptr]

        # Are we finished? If not, iterate
        L1_size = ptr - a
        if L1_size == k: break

        if L1_size > k:
            b, depth = ptr-1, depth+1
        else:
            a, k, depth = ptr+1, k - L1_size - 1, depth+1

    return depth, comp, e

def test():
    # Build list of distinct numbers
    L = [i for i in range(1000)]

    # Run experiments
    for _ in xrange(10):
        random.shuffle(L)
        acc = 0
        print sum([find(L, 500)[0] for _ in xrange(1000)]) / 1000.0


test()