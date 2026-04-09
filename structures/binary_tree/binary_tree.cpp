#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <queue>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;
using std::queue;

//структура, описывающая узел в дереве выражений
struct Node
{
    char value;
    Node* left;
    Node* right;

    Node(char str) {value = str; left = right = nullptr; }
};  

//структура, описывающая узел в дереве поиска
struct Node_Sr
{
    int value;
    Node_Sr* left;
    Node_Sr* right;

    Node_Sr(int val) {value = val; left = right = nullptr; }
    Node_Sr() {value = 0; left = right = nullptr; }
};  

//дерево выражений
class ExpTree
{
public:
    Node* root; //корень

public:
    //создаёт представление дерева в виде стека
    Node* build_tree(const string& str)
    {
        stack<Node*> stack; //т.к. при постфиксной записи вершина добавляется в конце, то стек идеально подходит 
        
        for (char l : str)
        {
            if (l == ' ') continue; //если пробел

            //если это буква или число  
            if (isalnum(l)) stack.push(new Node(l));
            else // иначе это опреция: + - и т.д.
            {
                //достаем два последних значения, т.к. бинарное дерево
                Node* right = stack.top(); stack.pop();
                Node* left = stack.top(); stack.pop();
                //образуем новый узел
                Node* node = new Node(l);
                node->left = left;
                node->right = right;
                //добавляем узел в стек 
                stack.push(node);
            }
        }

        return stack.top(); //по сути указатель на вершину дерева
    }

    ExpTree(const string& str) {root = build_tree(str);} //конструктор
    ~ExpTree() {clear(root);} //диструктор

    //очистка памяти
    void clear(Node* node)
    {
        if (node == nullptr) return;
        clear(node -> left);
        clear(node -> right);
        delete node;
    }

    //постфиксный обход (лево, право, узел)
    void post(Node* node)
    {
        if (node == nullptr) return;
        post(node -> left);
        post(node -> right);
        cout << node -> value << " ";
    }

    //префиксный обход (узел, лево, право)
    void pred(Node* node)
    {
        if (node == nullptr) return;
        cout << node -> value << " ";
        pred(node -> left);
        pred(node -> right);
    }

    //симметричный обход (лево узел право)
    void symm(Node* node)
    {
        if (node == nullptr) return;
        symm(node -> left);
        cout << node -> value << " ";
        symm(node -> right);
    }

    //вывод дерева по уровням 
    void show_tree()
    {
        cout << "\nThe expression tree" << endl;
        if (root == nullptr) return;

        queue<Node*> q; //очередь для хранения узлов на текущем уровне
        q.push(root);
        
        int level = 0;
        
        while (!q.empty())
        {
            int size = q.size();  //сколько узлов на текущем уровне
            
            cout << "Level " << level << ": ";
            
            //обрабатываем все узлы текущего уровня
            for (int i = 0; i < size; i++)
            {
                Node* cur = q.front(); q.pop();
                cout << cur -> value << " ";
                
                if (cur -> left) q.push(cur -> left);
                if (cur -> right) q.push(cur -> right);
            }
            
            cout << endl;
            level++;
        }
        putchar('\n');
    }
};

//дерево поиска
class SearchTree
{
public:
    Node_Sr* root;

public:
    SearchTree() {root = nullptr;}
    ~SearchTree() {clear(root);}

    //очистка памяти
    void clear(Node_Sr* node)
    {
        if (node == nullptr) return;
        clear(node -> left);
        clear(node -> right);
        delete node;
    }

    //добавление элемента
    Node_Sr* append(Node_Sr* node, int val)
    {
        //если первый элемент
        if (node == nullptr) return new Node_Sr(val);

        //если дубль
        else if (node -> value == val) return nullptr;

        //если значение в текущей вершине больше, то идём влево
        else if (node -> value > val) node -> left = append(node -> left, val);

        //если значение в текущей вершине меньше, то идём вправо
        else if (node -> value < val) node -> right = append(node -> right, val);

        return node;
    }

    //поиск листа слева, т.е. мин значения
    Node_Sr* find_min(Node_Sr* node)
    {
        while (node && node -> left) node = node -> left;
        return node;
    }

    //удаление узла, ветки или листа
    Node_Sr* del_Node(Node_Sr* node, int key)
    {   
        if (node == nullptr) return node;

        //если ключ меньше ищем слева, иначе справа 
        if (key < node -> value) node -> left = del_Node(node -> left, key);
        else if (key > node -> value) node->right = del_Node(node -> right, key);
        
        //если нашли 
        else 
        {
            //если лист
            if (node -> left == nullptr && node -> right == nullptr)
            {
                delete node; return nullptr;
            }

            //если только 1 потомок
            else if (node -> left == nullptr || node -> right == nullptr)
            {
                Node_Sr* tmp;
                if (node -> left) tmp = node -> left;
                if (node -> right) tmp = node -> right;
                delete node;
                return tmp;
            }

            //2 потомка
            else
            {
                Node_Sr* t = find_min(node -> right); //находим минимальное значение в правой ветке
                node -> value = t -> value; //присваиваем удаляемой вершине мин значение
                node -> right = del_Node(node -> right, t -> value); //удаляем вершину с взятым мин значением
            }
        }

        return node;
    }

    //вывод дерева - постфиксный обход
    void show_tree(Node_Sr* node)
    {
        if (node == nullptr) return;
        show_tree(node -> left);
        show_tree(node -> right);
        cout << node -> value << " ";
    }

    //вывод дерева в ширину
    void show_width_tree(Node_Sr* node)
    {
        cout << "\nThe search tree" << endl;
        if (node == nullptr) return;

        queue<Node_Sr*> q;
        int level = 0;
        q.push(node);

        while (q.empty() == 0)
        {
            int size = q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < size; i++)
            {
                Node_Sr* cur = q.front(); q.pop();
                cout << cur -> value << " ";

                if (cur -> left) q.push(cur -> left);
                if (cur -> right) q.push(cur -> right);
            }

            putchar('\n');
            level++;
        }
    }
};

int main()
{
    ExpTree* tree = new ExpTree("ADE-BC-+F*G-H/-");
    tree -> show_tree();
    cout << "--------" << endl;
    cout << "\npost" << endl;
    tree -> post(tree -> root);
    cout << "\n--------" << endl;
    cout << "\npred" << endl;
    tree -> pred(tree -> root);
    cout << "\n--------" << endl;
    cout << "\nsymm" << endl;
    tree -> symm(tree -> root);
    cout << "\n--------" << endl;

    SearchTree* sr_tree = new SearchTree();
    const int size = 13;
    int nums[size] = {5, 16, 26, 3, 20, 29, 54, 37, 34, 48, 40, 10, 43};

    for (int i = 0; i < size; i++ )sr_tree -> root = sr_tree -> append(sr_tree -> root, nums[i]);
    sr_tree -> show_tree(sr_tree -> root);
    cout << "\n------" << endl;
    sr_tree -> show_width_tree(sr_tree -> root);
    cout << "\n------" << endl;
    sr_tree -> del_Node(sr_tree -> root, 5);
    cout << "Delete elem with number 5" << endl;
    sr_tree -> show_width_tree(sr_tree -> root);
    cout << "\n------" << endl;
    sr_tree -> show_tree(sr_tree -> root);
    cout << "\n------" << endl;


    return 0;
}