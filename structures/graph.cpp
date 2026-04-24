#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <climits>
#include <iomanip>
#include <cstdio>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::stringstream;
using std::setw;

struct Elem {
    int Node;        
    int weight;        
    Elem* next;     
};

// Структура для вершины графа
struct Node {
    int index;         // номер вершины (1-based для вывода)
    Elem* list;  // указатель на начало списка смежности
};

// Класс графа с иерархическим списком
class Graph {
private:
    int count;           // количество вершин
    Node* nodes;          // массив вершин

public:
    // Конструктор
    Graph(int n) : count(n) {
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].index = i + 1;  // 1-based для пользователя
            nodes[i].list = nullptr;
        }
    }

    // Деструктор
    ~Graph() {
        for (int i = 0; i < count; i++) {
            Elem* current = nodes[i].list;
            while (current != nullptr) {
                Elem* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] nodes;
    }

    // Добавление ребра (неориентированного)
    void add(int from, int to, int weight) {
        if (weight == 0) return;  // нет ребра
        
        // Добавляем ребро from -> to
        Elem* elem = new Elem();
        elem->Node = to + 1;  // переводим в 1-based
        elem->weight = weight;
        elem->next = nodes[from].list;
        nodes[from].list = elem;
        
        // Добавляем ребро to -> from (для неориентированного графа)
        Elem* elem2 = new Elem();
        elem2->Node = from + 1;
        elem2->weight = weight;
        elem2->next = nodes[to].list;
        nodes[to].list = elem2;
    }

    // Чтение матрицы из файла и построение списка
    int read_file(const char* filename) {
        FILE* f = fopen(filename, "r");
        if (f == nullptr) {
            std::cout << "Error" << std::endl;
            return -1;
        }

        const int len = 500;
        int cnt = 0;
        char row[len];

        while (fgets(row, len, f)) {
            if (row[0] == '\n' || row[0] == '\0') {
                continue;
            }
            
            int col = 0;
            char* ptr = row;

            while (ptr != nullptr && col < count) {
                int x = 0;
                if (sscanf(ptr, "%d", &x)) {
                    add(cnt, col, x);
                }
                
                col++;
                ptr = strchr(ptr + 1, ' ');
            }

            cnt++;
            putchar('\n');
        }

        fclose(f);

        return 1;
    }

    // Вывод всех рёбер в виде трёх массивов
    void printEdges() {
        cout << "\n=== Все рёбра графа ===\n";
        cout << "Откуда | Куда | Метка\n";
        cout << "-------+------+------\n";
        
        // Для каждого ребра выводим его (избегаем дублей)
        vector<vector<bool>> printed(count, vector<bool>(count, false));
        
        for (int i = 0; i < count; i++) {
            Elem* current = nodes[i].list;
            while (current != nullptr) {
                int to = current->Node - 1;  // обратно в 0-based
                if (!printed[i][to] && i != to) {
                    cout << "  " << setw(2) << (i + 1) << "   | "
                         << setw(2) << current->Node << "   | "
                         << setw(3) << current->weight << endl;
                    printed[i][to] = true;
                    printed[to][i] = true;
                }
                current = current->next;
            }
        }
        
        // Подсчёт количества рёбер
        int edgeCount = 0;
        for (int i = 0; i < count; i++) {
            for (int j = i + 1; j < count; j++) {
                if (printed[i][j]) edgeCount++;
            }
        }
        cout << "\nВсего рёбер: " << edgeCount << endl;
    }
    
    // Алгоритм Дейкстры для поиска кратчайшего пути
    void shortestPath(int start, int end) {
        // Переводим в 0-based
        start--;
        end--;
        
        if (start < 0 || start >= count || end < 0 || end >= count) {
            cout << "Ошибка: неверные номера вершин!" << endl;
            return;
        }
        
        vector<int> dist(count, INT_MAX);
        vector<int> prev(count, -1);
        vector<bool> visited(count, false);
        
        dist[start] = 0;
        
        for (int count = 0; count < count - 1; count++) {
            // Находим непосещённую вершину с минимальным расстоянием
            int u = -1;
            int minDist = INT_MAX;
            for (int i = 0; i < count; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            
            if (u == -1) break;  // нет достижимых вершин
            visited[u] = true;
            
            // Обновляем расстояния до соседей
            Elem* neighbor = nodes[u].list;
            while (neighbor != nullptr) {
                int v = neighbor->Node - 1;
                int weight = neighbor->weight;
                
                if (!visited[v] && dist[u] != INT_MAX && 
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
                neighbor = neighbor->next;
            }
        }
        
        // Вывод результатов
        cout << "\n=== Кратчайший путь из " << (start + 1) 
             << " в " << (end + 1) << " ===\n";
        
        if (dist[end] == INT_MAX) {
            cout << "Путь не существует!" << endl;
            return;
        }
        
        // Восстановление пути
        vector<int> path;
        for (int v = end; v != -1; v = prev[v]) {
            path.push_back(v + 1);
        }
        
        cout << "Путь: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
        
        cout << "Длина пути: " << dist[end] << endl;
        
        // Вывод весов каждого шага
        cout << "\nДетали пути:\n";
        for (size_t i = path.size() - 1; i > 0; i--) {
            int from = path[i] - 1;
            int to = path[i-1] - 1;
            int weight = 0;
            
            // Находим вес ребра
            Elem* current = nodes[from].list;
            while (current != nullptr) {
                if (current->Node - 1 == to) {
                    weight = current->weight;
                    break;
                }
                current = current->next;
            }
            cout << "  " << path[i] << " -> " << path[i-1] 
                 << " : вес = " << weight << endl;
        }
    }
    
    // Отображение иерархической структуры списка
    void displayHierarchicalList() {
        cout << "\n=== Иерархический список смежности ===\n";
        for (int i = 0; i < count; i++) {
            cout << "Вершина " << (i + 1) << ": ";
            Elem* current = nodes[i].list;
            if (current == nullptr) {
                cout << "(нет связей)";
            } else {
                while (current != nullptr) {
                    cout << "-> [" << current->Node << ", " 
                         << current->weight << "] ";
                    current = current->next;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    Graph graph(10);  // 10 вершин
    
    // Чтение матрицы из файла
    const char* filename = "matrix.txt";
    
    if (graph.read_file(filename)) {
        cout << "Матрица успешно загружена из файла " << filename << endl;
        
        // 2.2 Вывод всех рёбер в виде трёх массивов
        graph.printEdges();
        
        // Дополнительно: отображение иерархической структуры
        graph.displayHierarchicalList();
        
        // 2.3 Поиск кратчайшего пути
        int start, end;
        cout << "\n=== Поиск кратчайшего пути ===\n";
        cout << "Введите начальную вершину (1-10): ";
        cin >> start;
        cout << "Введите конечную вершину (1-10): ";
        cin >> end;
        
        graph.shortestPath(start, end);
    } else {
        cout << "Ошибка при загрузке матрицы!" << endl;
    }
    
    return 0;
}