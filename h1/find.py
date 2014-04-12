import random

def find(L, k, d):
    """Finds the number with rank k, and reports recursion depth"""
    # Select pivot
    e = L[random.randint(0, len(L) - 1)] # TODO use true randomness

    # Partition the list
    L1 = []
    L2 = []
    for x in L:
        if x < e: L1.append(x)
        if x > e: L2.append(x)

    # Are we finished? If not, recurse
    if len(L1) == k: return d, e
    return find(L1, k, d+1) if len(L1) > k else find(L2, k - len(L1) - 1, d+1)


def test():
    # Build list of distinct numbers
    L = [i for i in range(1000)]

    # Run experiments
    for _ in xrange(10):
        random.shuffle(L)
        print sum([find(L, 500, 0)[0] for _ in xrange(1000)]) / 1000.0


test()