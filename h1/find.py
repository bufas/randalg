import random

def find(L, a, b, k, d):
    """Finds the number with rank k, and reports recursion depth"""
    # Select pivot
    r = random.randint(a, b) # TODO use true randomness
    L[r], L[b] = L[b], L[r] # Swap e and last element
    e = L[b]

    ptr = a
    for i in xrange(a,b):
        if L[i] < e:
            L[ptr], L[i] = L[i], L[ptr]
            ptr += 1

    # Swap e to its right place
    L[ptr], L[b] = L[b], L[ptr]

    # Are we finished? If not, recurse
    L1_size = ptr - a
    if L1_size == k: return d, L[ptr]
    return find(L, a, ptr-1, k, d+1) if L1_size > k else find(L, ptr+1, b, k - L1_size - 1, d+1)

def test():
    # Build list of distinct numbers
    L = [i for i in range(1000)]

    # Run experiments
    for _ in xrange(10):
        random.shuffle(L)
        print sum([find(L, 0, len(L)-1, 500, 0)[0] for _ in xrange(1000)]) / 1000.0


test()