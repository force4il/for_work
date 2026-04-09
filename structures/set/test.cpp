#include <iostream>
#include <set>
#include <algorithm>

using std::set;
using std::cout;
using std::endl;
using std::cin;
using std::set_difference;
using std::inserter;

int main() {
    set<int> a, b;
    set<int> c;
    int x, y;

    while (cin >> x && cin >> y) {
        a.insert(x);
        b.insert(y);
    }

    std::set_intersection(a.begin(), a.end(),
             b.begin(), b.end(),
             inserter(c, c.begin()));

    for (auto k : c) {
        cout << k << " ";
    }

    return 0;
}