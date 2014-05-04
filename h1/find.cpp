#include <iostream>
#include <utility>    // std::pair
#include <ctime>      // std::time()
#include <cstdlib>    // std::rand, std::srand
#include <vector>     // std::vector
#include <algorithm>  // std::iter_swap, std::suffle
#include <random>     // std::default_random_engine
#include <chrono>     // std::chrono::system_clock
#include <iterator>   // std::distance
#include <cmath>      // log()
#include <array>      // std::array

using namespace std;

/**
 * At the end of this method, l[a..b-1] will be partitioned, and the 
 * pivot will be at position l[b].
 * Returns a pointer to the first element greater than the pivot.
 */
vector<int>::iterator partition(vector<int> &l, const vector<int>::iterator a, const vector<int>::iterator b) {
    // Pick a random pivot and move it to the end
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

    return ptr;
}

pair<int, int> randQS(vector<int>& l, const vector<int>::iterator a, const vector<int>::iterator b, int d) {
    // Only one element, trivially sorted
    if (distance(a, b) <= 1) return pair<int, int>(d, 0);

    // Partition the array
    auto ptr = partition(l, a, b);
    iter_swap(ptr, b-1); // Move the pivot to its proper place

    // Call recursively
    auto p1 = randQS(l, a, ptr, d+1);
    auto p2 = randQS(l, ptr+1, b, d+1);

    return pair<int, int>(std::max(p1.first, p2.first), p1.second + p2.second + distance(a,b) - 1);
}

pair<int, int> find(vector<int>& l, const vector<int>::iterator a, const vector<int>::iterator b, int k, int d, int comp) {
    // Partition the array
    auto ptr = partition(l, a, b);
    comp += distance(a,b) - 1;

    // Are we finished?
    int l1_size = distance(a, ptr);
    if (l1_size == k - 1) return pair<int, int>(d, comp); // Finished

    // Recurse
    if (l1_size > k - 1) return find(l, a, ptr, k, d+1, comp);
    return find(l, ptr, b-1, k - l1_size - 1, d+1, comp);
}

void shuffle(vector<int> &v) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(v.begin(), v.end(), std::default_random_engine(seed));
}

// #define NO_OF_N_VALS 20
// int main() {
//     static const int ITERATIONS = 100000;

//     srand(time(nullptr));

//     std::array<double, NO_OF_N_VALS> mean_arr;
//     std::array<int, NO_OF_N_VALS> over1mu_arr;
//     std::array<int, NO_OF_N_VALS> over3mu_arr;

//     std::array<int, NO_OF_N_VALS> ns = {{
//         10, 
//         100, 200, 300, 400, 500, 600, 700, 800, 900, 
//         1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000
//     }};
//     for (int in = 0; in < ns.size(); ++in) {
//         int n = ns[in];

//         // Initialize vector of length n
//         vector<int> v;
//         for (int i = 1; i <= n; ++i) v.push_back(i);

//         // Calculate mu value
//         double mu = 2*n*log(n);

//         // Run a large number of iterations for this n
//         unsigned long acc = 0;
//         over1mu_arr[in] = 0;
//         over3mu_arr[in] = 0;
//         for (int i = 0; i < ITERATIONS; ++i) {
//             shuffle(v);
//             int z = randQS(v, v.begin(), v.end(), 0).second;
            
//             acc += z;
//             if (z >= mu) over1mu_arr[in] += 1;
//             if (z >= 3*mu) over3mu_arr[in] += 1;
//         }

//         mean_arr[in] = acc / (ITERATIONS * 1.0);

//         // printf(" & %.3f & %d & %d\n", mean_arr[in], over1mu_arr[in], over3mu_arr[in]);
//         printf("%d\t%.3f\t%d\t%d\n", n, mean_arr[in], over1mu_arr[in], over3mu_arr[in]);
//     }

//     // Print the output
//     cout << endl;
// }


// #define NO_OF_N_VALS 20
// int main() {
//     static const int ITERATIONS = 100000;

//     srand(time(nullptr));

//     std::array<int, NO_OF_N_VALS> ns = {{
//         500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000,
//         5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000
//     }};
//     for (int in = 0; in < ns.size(); ++in) {
//         int n = ns[in];

//         // Initialize vector of length n
//         vector<int> v;
//         for (int i = 1; i <= n; ++i) v.push_back(i);

//         // Calculate mu value
//         double mu = 2*log(n);

//         int k = n/4;

//         // Run a large number of iterations for this k,n value pair
//         unsigned long acc = 0;
//         int over1mu_arr = 0;
//         int over2mu_arr = 0;
//         for (int i = 0; i < ITERATIONS; ++i) {
//             shuffle(v);
//             int z = find(v, v.begin(), v.end(), k, 0, 0).first;
            
//             acc += z;
//             if (z >= mu) over1mu_arr += 1;
//             if (z >= 2*mu) over2mu_arr += 1;
//         }

//         double mean_arr = acc / (ITERATIONS * 1.0);

//         printf("%d\t%d\t%d\t%.3f\t%d\t%d\n", n, k, ITERATIONS, mean_arr, over1mu_arr, over2mu_arr);
//     }
// }


#define NO_OF_N_VALS 4
int main() {
    static const int ITERATIONS = 100000;

    srand(time(nullptr));

    std::array<std::array<double, 5>, NO_OF_N_VALS> mean_arr;
    std::array<std::array<int, 5>, NO_OF_N_VALS> over1mu_arr;
    std::array<std::array<int, 5>, NO_OF_N_VALS> over2mu_arr;

    std::array<int, NO_OF_N_VALS> ns = {{10, 100, 1000, 10000}};
    for (int in = 0; in < ns.size(); ++in) {
        int n = ns[in];

        // Initialize vector of length n
        vector<int> v;
        for (int i = 1; i <= n; ++i) v.push_back(i);

        // Calculate mu value
        double mu = 2*log(n);

        // Iterate over all k values
        std::array<int, 5> ks = {{1, n/4, n/2, 3*n/4, n}};
        for (int ik = 0; ik < ks.size(); ++ik) {
            int k = ks[ik];

            // Run a large number of iterations for this k,n value pair
            unsigned long acc = 0;
            over1mu_arr[in][ik] = 0;
            over2mu_arr[in][ik] = 0;
            for (int i = 0; i < ITERATIONS; ++i) {
                shuffle(v);
                int z = find(v, v.begin(), v.end(), k, 0, 0).first;
                
                acc += z;
                if (z >= mu) over1mu_arr[in][ik] += 1;
                if (z >= 2*mu) over2mu_arr[in][ik] += 1;
            }

            mean_arr[in][ik] = acc / (ITERATIONS * 1.0);
        }
    }

    // Print the output
    std::array<std::string, 5> ks = {{"1", "n/4", "n/2", "3n/4", "n"}};
    for (int k = 0; k < 5; k++) {
        printf("&$%s$", ks[k].c_str());
        
        for (int n = 0; n < ns.size(); n++) {
            printf(" & %.3f & %d & %d", mean_arr[n][k], over1mu_arr[n][k], over2mu_arr[n][k]);
        }

        if (k < 4) printf("\\\\ \\cline{2-14}\n");
        else printf("\\\\ \\hline\n");
    }
}
