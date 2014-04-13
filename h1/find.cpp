#include <iostream>
#include <utility>    // std::pair
#include <ctime>      // std::time()
#include <cstdlib>    // std::rand, std::srand
#include <vector>     // std::vector
#include <algorithm>  // std::iter_swap, std::suffle
#include <random>     // std::default_random_engine
#include <chrono>     // std::chrono::system_clock
#include <iterator>   // std::distance

using namespace std;

pair<int, int> find(vector<int>& l, const vector<int>::iterator a, const vector<int>::iterator b, int k, int d) {
    // Pick the pivot and move it to the end
    int size = distance(a, b);
    auto r = (size == 1) ? 0 : rand() % (size - 1);
    iter_swap(a + r, b-1);
    int e = *(b-1);

    // Partition the array
    auto ptr = a;
    for (auto i = a; i != b-1; ++i) {
        if (*i < e) {
            iter_swap(ptr, i);
            ++ptr;
        }
    }

    // Are we finished? If not, recurse
    int l1_size = distance(a, ptr);
    if (l1_size == k - 1) {
        return pair<int, int>(e, d);
    }

    if (l1_size > k - 1) return find(l, a, ptr, k, d+1);
    else return find(l, ptr, b-1, k - l1_size - 1, d+1);
}

void shuffle(vector<int> &v) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(v.begin(), v.end(), std::default_random_engine(seed));
}

int main() {
    srand(time(nullptr));

    vector<int> v;
    for (int i = 1; i <= 10000; ++i) v.push_back(i);

    unsigned long acc = 0;
    for (int i = 0; i < 10000; ++i) {
        shuffle(v);
        acc += find(v, v.begin(), v.end(), 500, 0).first;
    }
    cout << "Mean: " << (acc / 10000.0) << endl;
}
