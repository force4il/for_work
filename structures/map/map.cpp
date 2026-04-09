#include <iostream>
#include <map>
#include <vector>
#include <string>

int main(void)
{
    using namespace std;
    map<string, vector<string>> metro;

    metro.emplace("Китай-город 1", vector<string>{"Китай-город 2", "Кузнецкий мост"});
    metro.emplace("Китай-город 2", vector<string>{"Китай-город 1", "Тургеневская"});
    metro.emplace("Кузнецкий мост", vector<string>{"Китай-город 1", "Лубянка"});
    metro.emplace("Лубянка", vector<string>{"Кузнецкий мост", "Чистые пруды"});
    metro.emplace("Чистые пруды", vector<string>{"Лубянка"});
    metro.emplace("Тургеневская", vector<string>{"Китай-город 2"});
    metro.emplace("Сретенский бульвар", vector<string>{});

    return 0;
}