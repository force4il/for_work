#include <iostream>
#include <unordered_set>
#include <string>

int main(void)
{
    using namespace std;
    unordered_set<int> unique;
    int arr[] = {1, 2, 3, 5, 7, 11, 2, 3, 5, 7};
    for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
        unique.insert(arr[i]);
    }

    return 0;
}