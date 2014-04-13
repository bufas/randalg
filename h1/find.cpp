#include <iostream>
#include <utility>    // std::pair, std::swap
#include <ctime>      // std::time()
#include <cstdlib>    // std::rand, std::srand
#include <vector>     // std::vector
#include <algorithm>  // std::iter_swap, stdd::suffle
#include <random>     // std::default_random_engine
#include <chrono>     // std::chrono::system_clock

using namespace std;

pair<int, int> find(vector<int>& l, int a, int b, int k, int d) {
    // Pick the pivot and move it to the end
    int r = a + (rand() % (b - a + 1));
    swap(l[r], l[b]);
    int e = l[b];

    int ptr = a;
    for (int i = a; i < b; ++i) {
        if (l[i] < e) {
            swap(l[ptr], l[i]);
            ptr++;
        }
    }

    // Swap e to its right place
    swap(l[ptr], l[b]);

    // Are we finished? If not, recurse
    int l1_size = ptr - a;
    if (l1_size == k) {
        return pair<int, int>(e, d);
    }

    return (l1_size > k) ? find(l, a, ptr-1, k, d+1) : find(l, ptr+1, b, k - l1_size - 1, d+1);
}

void shuffle(vector<int> &v) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (v.begin(), v.end(), std::default_random_engine(seed));
}

int main() {
    srand(time(nullptr));

    vector<int> v;
    for (int i = 0; i < 1000; ++i) v.push_back(i);

    unsigned long acc = 0;
    for (int i = 0; i < 1000; ++i) {
        shuffle(v);
        acc += find(v, 0, v.size() - 1, 500, 0).second;
    }
    cout << "Mean: " << (acc / 1000.0) << endl;
}
