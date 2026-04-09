#include <iostream>
#include <list>
#include <vector>

template <typename T>
void insert_to_list(std::list<T>& lst, unsigned int pos, const T& value) 
{
    auto ptr = lst.begin();
    for (int i = 0; i < pos; i++) ptr++;
    lst.insert(ptr, value);
}

int main(void)
{
    using namespace std;
    // здесь пишите программу
    list<int> d_lst;
    int x;
    std::vector<int> d_in;   // этот объект в программе не менять
    while (cin >> x) {d_in.push_back(x); d_lst.push_back(x);}

    insert_to_list(d_lst, 1, -3);
    insert_to_list(d_lst, 2, -5);

    return 0;
}