#include <iostream>

// Итак, каждый объект (элемент) двусвязного списка будет определять классом с именем Node, а работу со всем списком 
// целиком – с помощью класса LinkedList. Начнем с класса Node. Каждый объект должен содержать данные data и ссылки на 
// предыдущий и следующий элементы prev и next. В этом классе определен один конструктор, в который передаются хранимые 
// данные в виде вещественного числа, и сохраняются в переменной data объекта класса Node. А указатели prev и next по 
// умолчанию принимают значение NULL.
class Node {
public:
    double data;
    Node* prev, * next;
 
public:
    Node(double data) 
    {
        this->data = data;
        this->prev = this->next = NULL;
    }
};

// В следующем классе LinkedList реализуем все основные операции для работы с элементами двусвязного списка. Вначале определим этот класс с двумя 
// указателями head и tail. Далее, по порядку, определим методы для базовых операций со списком. И первыми пропишем методы push_front() и 
// push_back() для добавления элементов в начало и конец двусвязного списка.
class LinkedList {
public:
    Node* head, * tail;
 
public:
    LinkedList() {this->head = this->tail = NULL;}
    ~LinkedList() { while (head != NULL) pop_front(); }

    Node* push_front(double data) {
        Node* ptr = new Node(data);
                   
        ptr->next = head;
        if (head != NULL) head->prev = ptr;
        if (tail == NULL) tail = ptr;
        head = ptr;
 
        return ptr;
    }

    Node* push_back(double data) {
        Node* ptr = new Node(data);
 
        ptr->prev = tail;
        if (tail != NULL) tail->next = ptr;
        if (head == NULL) head = ptr;
        tail = ptr;
 
        return ptr;
    }
    // Логика работы обоих методов одинакова. Сначала создается новый объект класса Node в памяти устройства. Затем, настраиваются связи либо с 
    // первым объектом списка (при добавлении в начало), либо с последним (при добавлении в конец). И меняются значения указателей head и ptr. В 
    // конце мы возвращаем указатель на новый добавленный элемент.

    // По аналогии реализуются операции удаления элементов в начале и конце двусвязного списка:
    void pop_front() {
        if (head == NULL) return;
                   
        Node* ptr = head->next;
        if (ptr != NULL) ptr->prev = NULL;
        else tail = NULL;
 
        delete head;
        head = ptr;
    }
 
    void pop_back() {
        if (tail == NULL) return;
 
        Node* ptr = tail->prev;
        if (ptr != NULL) ptr->next = NULL;
        else head = NULL;
 
        delete tail;
        tail = ptr;
    }

    // Далее, мы реализуем метод getAt() и оператор [] для доступа к произвольному элементу двусвязного списка:
    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;
 
        while (n != index) {
                if (ptr == NULL) return ptr;
                ptr = ptr->next;
                n++;
        }
 
        return ptr;
    }
 
    Node* operator [] (int index) { return getAt(index); }

    // Воспользуемся методом getAt() в реализации метода insert() для вставки нового элемента в позицию с индексом index (индексы отсчитываются от нуля):
    Node* insert(int index, double data) {
        Node* right = getAt(index);
        if (right == NULL) return push_back(data);
 
        Node* left = right->prev;
        if (left == NULL) return push_front(data);
 
        Node* ptr = new Node(data);
                   
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
 
        return ptr;
    }

    // Наконец, последний метод erase(), который удаляет произвольный элемент с индексом index из связного списка:
    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == NULL) return;
 
        if (ptr->prev == NULL) {
            pop_front();
            return;
        }
 
        if (ptr->next == NULL) {
            pop_back();
            return;
        }
 
        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;
 
        delete ptr;
    }
    // В целом, у нас получилась реализация двусвязного списка с базовым набором операций. Осталось только выполнить очистку памяти (удаление всех 
    // объектов) при удалении объекта класса LinkedList. Делается это, обычно, в деструкторе класса. 
};

int main(void)
{
    LinkedList lst;
    lst.push_back(1.0);
    lst.push_back(2.0);
    lst.push_back(3.0);
    lst.push_back(4.0);

    for (Node* ptr = lst.head; ptr != NULL; ptr = ptr->next) std::cout << ptr->data << " ";
    std::cout << std::endl;

    for (Node* ptr = lst.tail; ptr != NULL; ptr = ptr->prev) std::cout << ptr->data << " ";
    std::cout << std::endl;

    std::cout << lst[1]->data << std::endl;
    std::cout << lst[0]->data << std::endl;
    std::cout << lst[3]->data << std::endl;

    lst.insert(2, -5.0);
    lst.insert(20, -10.0);
    lst.erase(3);
    lst.erase(30);

    return 0;
}